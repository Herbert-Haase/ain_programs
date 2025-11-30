/**
 * Monad + POSIX Threads (pthread) Example
 *
 * Compilation: g++ monad_pthread.cpp -o app -lpthread
 *
 * Concepts:
 * 1. Monad: A 'Maybe' struct that encapsulates a value or failure state,
 * allowing function chaining via 'bind'.
 * 2. Multithreading: Using low-level <pthread.h> instead of <thread>.
 */

#include <cmath>
#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h> // For sleep simulation if needed
#include <vector>

// ==========================================
// 1. The Monad Definition (Maybe)
// ==========================================

// A rudimentary implementation of the Maybe Monad
template <typename T> struct Maybe
{
  T value;
  bool hasValue;

  // Constructors
  Maybe(T v) : value(v), hasValue(true) {}
  Maybe() : value(T()), hasValue(false) {} // Represents "Nothing" or Failure

  // The 'Bind' operator (>>= in Haskell).
  // It takes a function 'func' that accepts T and returns Maybe<U>.
  template <typename Func> auto bind(Func func) -> decltype(func(value))
  {
    if (!hasValue)
    {
      // If current state is Failure, propagate Failure of the return type
      return decltype(func(value))();
    }
    // Otherwise, apply the function to the contained value
    return func(value);
  }

  bool valid() const { return hasValue; }
};

// ==========================================
// 2. Monadic Operations
// ==========================================

// Operation 1: Safe Division. Returns Nothing if dividing by zero.
Maybe<double> safeDivide(double numerator, double denominator)
{
  if (denominator == 0.0)
  {
    return Maybe<double>(); // Failure
  }
  return Maybe<double>(numerator / denominator);
}

// Operation 2: Safe Square Root. Returns Nothing if negative.
Maybe<double> safeSqrt(double number)
{
  if (number < 0.0)
  {
    return Maybe<double>(); // Failure
  }
  return Maybe<double>(std::sqrt(number));
}

// Operation 3: Add overhead (simulate work) and multiply
Maybe<double> heavyMultiply(double number)
{
  // Simulate complex calculation
  return Maybe<double>(number * 10.0);
}

// ==========================================
// 3. Threading Infrastructure
// ==========================================

// Shared mutex for console output synchronization
pthread_mutex_t printMutex;

struct ThreadArgs
{
  int threadId;
  double numerator;
  double denominator;
};

// The worker function for pthreads
void *worker_routine(void *arg)
{
  // Cast argument back to struct
  ThreadArgs *data = static_cast<ThreadArgs *>(arg);

  // ---------------------------------------------------------
  // The Monadic Chain
  // Notice no "if" statements checking for errors between steps.
  // The 'bind' method handles the control flow.
  // ---------------------------------------------------------

  // Step 1: Wrap initial value (numerator)
  Maybe<double> initial = Maybe<double>(data->numerator);

  // Chain: (numerator / denominator) -> sqrt(result) -> (result * 10)
  auto result =
      initial.bind([&](double n) { return safeDivide(n, data->denominator); })
          .bind(safeSqrt)
          .bind(heavyMultiply);

  // ---------------------------------------------------------
  // Output Section (Critical Section)
  // ---------------------------------------------------------
  pthread_mutex_lock(&printMutex);

  std::cout << "[Thread " << data->threadId << "] Input: " << data->numerator
            << " / " << data->denominator;

  if (result.valid())
  {
    std::cout << " | Result: " << result.value << std::endl;
  }
  else
  {
    std::cout << " | Result: Calculation Failed (Monadic Nothing)" << std::endl;
  }

  pthread_mutex_unlock(&printMutex);

  pthread_exit(NULL);
  return NULL;
}

// ==========================================
// 4. Main Execution
// ==========================================

int main()
{
  // Initialize Mutex
  if (pthread_mutex_init(&printMutex, NULL) != 0)
  {
    std::cerr << "Mutex init failed" << std::endl;
    return 1;
  }

  const int NUM_THREADS = 5;
  pthread_t threads[NUM_THREADS];
  ThreadArgs args[NUM_THREADS];

  // Define different inputs to test success and failure cases
  std::vector<std::pair<double, double>> inputs = {
      {100.0, 4.0},  // 100/4 = 25 -> sqrt(25)=5 -> 5*10 = 50 (Success)
      {10.0, 0.0},   // Div by Zero (Fail at step 1)
      {-100.0, 1.0}, // -100/1 = -100 -> sqrt(-100) (Fail at step 2)
      {36.0, 1.0},   // 36/1 = 36 -> sqrt(36)=6 -> 6*10 = 60 (Success)
      {0.0, 5.0}     // 0/5 = 0 -> sqrt(0)=0 -> 0*10 = 0 (Success)
  };

  std::cout << "--- Starting POSIX Threads with Monadic Logic ---" << std::endl;

  // Create Threads
  for (int i = 0; i < NUM_THREADS; ++i)
  {
    args[i].threadId = i;
    args[i].numerator = inputs[i].first;
    args[i].denominator = inputs[i].second;

    int rc =
        pthread_create(&threads[i], NULL, worker_routine, (void *)&args[i]);

    if (rc)
    {
      std::cerr << "Error: unable to create thread, " << rc << std::endl;
      return -1;
    }
  }

  // Join Threads (Wait for them to finish)
  for (int i = 0; i < NUM_THREADS; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  std::cout << "--- All Threads Completed ---" << std::endl;

  // Clean up
  pthread_mutex_destroy(&printMutex);

  return 0;
}


// g++ monad_pthread.cpp -o app -lpthread
// ./app
//
// ### Key Components Explained
//
// 1.  **The `Maybe` Monad:**
//     * This struct acts as a wrapper. It holds either a valid value or a "Nothing" state (`hasValue = false`).
//     * **`bind`**: This is the magic function. It takes a function `f`. If the current `Maybe` is empty, `bind` immediately returns an empty `Maybe` of the next type, skipping `f`. If it's valid, it executes `f`.
//
// 2.  **`worker_routine`:**
//     * This is the entry point for `pthread_create`. It accepts a `void*` which we cast back to our specific data structure.
//     * Inside, you see the "railway oriented programming" style:
//         ```cpp
//         initial.bind(...).bind(...).bind(...)
//             * We don't need `if (denom == 0)` or `if (result < 0)` checks in the main logic flow; the Monad definitions handle that internally.
//
// 3.  **POSIX Threads (`pthread`):**
//     * **`pthread_create`**: Spawns a new thread executing the worker function.
//     * **`pthread_join`**: Blocks the main thread until the specified thread finishes, ensuring the program doesn't exit before work is done.
//     * **`pthread_mutex`**: Crucial for C++ `std::cout`. Without this lock, multiple threads writing to the console simultaneously would result in garbled text.
