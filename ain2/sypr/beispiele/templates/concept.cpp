#include <algorithm>
#include <concepts>
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Sortable
template <typename T>
concept Sortable = requires(T container) {
  // Must have begin() and end()
  { container.begin() } -> std::input_or_output_iterator;
  { container.end() } -> std::input_or_output_iterator;

  // Element type must be comparable
  requires std::totally_ordered<typename T::value_type>;
};

template <Sortable Container> void sortAndPrint(Container &container)
{
  std::sort(container.begin(), container.end());

  for (const auto &elem : container)
  {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

// advanced requires
template <typename T>
concept Container = requires(T container) {
  typename T::value_type; // Must have value_type typedef
  typename T::iterator;   // Must have iterator typedef

  { container.begin() } -> std::same_as<typename T::iterator>;
  { container.end() } -> std::same_as<typename T::iterator>;
  { container.size() } -> std::convertible_to<size_t>;

  requires std::copyable<T>; // Nested requirement
};

template <Container C> void processContainer(const C &container)
{
  std::cout << "Container size: " << container.size() << '\n';
}

// Printable
template <typename T>
concept Printable = requires(T obj, std::ostream &os) {
  { os << obj } -> std::convertible_to<std::ostream &>;
};

template <Printable T> class Logger
{
  T data;

public:
  Logger(T d) : data(std::move(d)) {}

  void log() { std::cout << "Log: " << data << '\n'; }
};

// Overload for integral types
template <std::integral T> void process(T value)
{
  std::cout << "Processing integer: " << value << '\n';
}

// Overload for floating-point types
template <std::floating_point T> void process(T value)
{
  std::cout << "Processing float: " << value << '\n';
}

int main()
{
  std::vector<int> vec = {5, 2, 8, 1, 9};
  sortAndPrint(vec); // ✅ OK

  std::vector<std::string> words = {"cat", "ant", "bat"};
  sortAndPrint(words); // ✅ OK

  // int arr[5] = {5, 2, 8, 1, 9};
  // sortAndPrint(arr);  // ❌ Error: arrays don't have begin()/end() methods

  Logger<int> logger1(42);           // ✅ OK
  Logger<std::string> logger2("hi"); // ✅ OK

  // struct NonPrintable {};
  // Logger<NonPrintable> logger3{};  // ❌ Error: no operator
  process(42);   // Calls integral version
  process(3.14); // Calls floating_point version
}
