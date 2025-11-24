#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm>

template <typename T> class MyVector
{
private:
  std::unique_ptr<T[]> data_;
  size_t size_;
  size_t capacity_;

public:
  // Constructor
  MyVector() : data_(nullptr), size_(0), capacity_(0) {}

  explicit MyVector(size_t size)
      : data_(std::make_unique<T[]>(size)), size_(size), capacity_(size)
  {
  }

  void push_back(const T &value)
  {
    if (size_ >= capacity_)
    {
      resize(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
  }

  T &operator[](size_t index) { return data_[index]; }
  const T &operator[](size_t index) const { return data_[index]; }

  size_t size() const { return size_; }

private:
  void resize(size_t new_capacity)
  {
    auto new_data = std::make_unique<T[]>(new_capacity);
    for (size_t i = 0; i < size_; ++i)
    {
      new_data[i] = std::move(data_[i]);
    }
    data_ = std::move(new_data);
    capacity_ = new_capacity;
  }

public:
  // ============================================================
  // ITERATOR IMPLEMENTATION
  // ============================================================

  class Iterator
  {
  private:
    T *ptr_; // Pointer to current element

  public:
    // Iterator traits (required for std algorithms)
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    // Constructor
    explicit Iterator(T *ptr) : ptr_(ptr) {}

    // Dereference operator (required)
    reference operator*() const { return *ptr_; }

    // Arrow operator (required)
    pointer operator->() const { return ptr_; }

    // Pre-increment (required)
    Iterator &operator++()
    {
      ++ptr_;
      return *this;
    }

    // Post-increment
    Iterator operator++(int)
    {
      Iterator tmp = *this;
      ++ptr_;
      return tmp;
    }

    // Pre-decrement
    Iterator &operator--()
    {
      --ptr_;
      return *this;
    }

    // Post-decrement
    Iterator operator--(int)
    {
      Iterator tmp = *this;
      --ptr_;
      return tmp;
    }

    // Equality comparison (required)
    bool operator==(const Iterator &other) const { return ptr_ == other.ptr_; }

    // Inequality comparison (required)
    bool operator!=(const Iterator &other) const { return ptr_ != other.ptr_; }

    // Random access operators
    Iterator operator+(difference_type n) const { return Iterator(ptr_ + n); }

    Iterator operator-(difference_type n) const { return Iterator(ptr_ - n); }

    difference_type operator-(const Iterator &other) const
    {
      return ptr_ - other.ptr_;
    }

    Iterator &operator+=(difference_type n)
    {
      ptr_ += n;
      return *this;
    }

    Iterator &operator-=(difference_type n)
    {
      ptr_ -= n;
      return *this;
    }

    reference operator[](difference_type n) const { return ptr_[n]; }

    bool operator<(const Iterator &other) const { return ptr_ < other.ptr_; }

    bool operator>(const Iterator &other) const { return ptr_ > other.ptr_; }

    bool operator<=(const Iterator &other) const { return ptr_ <= other.ptr_; }

    bool operator>=(const Iterator &other) const { return ptr_ >= other.ptr_; }
  };

  // ============================================================
  // BEGIN/END METHODS (required for range-based for loop)
  // ============================================================

  Iterator begin() { return Iterator(data_.get()); }
  Iterator end() { return Iterator(data_.get() + size_); }

  // Const versions
  Iterator begin() const { return Iterator(data_.get()); }
  Iterator end() const { return Iterator(data_.get() + size_); }
};

// Usage
int main()
{
  MyVector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);
  vec.push_back(40);

  // Range-based for loop (uses begin() and end())
  std::cout << "Range-based for loop:\n";
  for (const auto &value : vec)
  {
    std::cout << value << ' ';
  }
  std::cout << '\n';

  // Traditional iterator loop
  std::cout << "Traditional iterator loop:\n";
  for (auto it = vec.begin(); it != vec.end(); ++it)
  {
    std::cout << *it << ' ';
  }
  std::cout << '\n';

  // Using std algorithms
  std::cout << "Using std::find:\n";
  auto it = std::find(vec.begin(), vec.end(), 30);
  if (it != vec.end())
  {
    std::cout << "Found: " << *it << '\n';
  }

  return 0;
}

// **Output:**
// Range-based for loop:
// 10 20 30 40
// Traditional iterator loop:
// 10 20 30 40
// Using std::find:
// Found: 30
