#include <iostream>

class SimpleRange
{
private:
  int start_;
  int end_;

public:
  SimpleRange(int start, int end) : start_(start), end_(end) {}

  class Iterator
  {
  private:
    int current_;

  public:
    Iterator(int start) : current_(start) {}

    // Minimum required operations
    int operator*() const { return current_; }

    Iterator &operator++()
    {
      ++current_;
      return *this;
    }

    bool operator!=(const Iterator &other) const
    {
      return current_ != other.current_;
    }
  };

  Iterator begin() { return Iterator(start_); }
  Iterator end() { return Iterator(end_); }
};

int main()
{
  SimpleRange range(1, 6);

  for (int num : range)
  {
    std::cout << num << ' ';
  }
  std::cout << '\n';
  // Output: 1 2 3 4 5
}
