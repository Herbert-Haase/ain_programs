#include <chrono>
#include <iostream>

// 1. The Wrapper Class
struct Distance
{
  long double meters;

  // Helper to print nicely
  friend std::ostream &operator<<(std::ostream &os, const Distance &d)
  {
    return os << d.meters << " meters";
  }
  // Allow adding two distances
  Distance operator+(const Distance &other) const
  {
    return Distance{meters + other.meters};
  }
};

// 2. Define the Literals
// The argument must be 'long double' for floating point literals
// or 'unsigned long long' for integer literals.

// Literal for Kilometers (_km)
Distance operator""_km(long double val) { return Distance{val * 1000.0}; }

// Literal for Miles (_mi)
Distance operator""_mi(long double val) { return Distance{val * 1609.34}; }

// Literal for Meters (_m)
Distance operator""_m(long double val) { return Distance{val}; }

int main()
{
  // 3. Usage
  // The compiler sees "1.5_km", looks for operator""_km(1.5),
  // and returns a Distance object containing 1500.0.

  Distance d1 = 1.5_km;
  Distance d2 = 2.0_mi; // 2 miles
  Distance d3 = 500.0_m;

  // We can mix units seamlessly because they are all 'Distance' objects
  Distance total = d1 + d2 + d3;

  std::cout << "1.5 km is: " << d1 << "\n";
  std::cout << "2.0 mi is: " << d2 << "\n";
  std::cout << "Total is:  " << total << "\n";

  // ### Standard Library Examples
  // You might have already used these without knowing they were literals:

  // 1.  **Time (C++14):**
  using namespace std::chrono_literals;
  auto sec = 10s;       // Creates std::chrono::seconds(10)
  auto millisec = 50ms; // Creates std::chrono::milliseconds(50)
  std::cout << (sec + millisec).count() << "\n";

  return 0;
}
// ```
