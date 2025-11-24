#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <utility>

struct SimpleString
{
private:
  size_t max_size;
  char *buffer;
  size_t length;

public:
  // 1. Regular Constructor
  SimpleString(size_t max_size)
      : max_size{max_size}, buffer{new char[max_size]}, length{}
  {
    if (max_size == 0)
      throw std::runtime_error{"Max size > 0"};
    buffer[0] = 0;
  }

  // 2. Destructor
  ~SimpleString() { delete[] buffer; }

  // 3. Copy Constructor (Deep Copy)
  SimpleString(const SimpleString &other)
      : max_size{other.max_size}, buffer{new char[other.max_size]},
        length{other.length}
  {
    std::memcpy(buffer, other.buffer, max_size); // efficient copy
  }

  // 4. Move Constructor (The Fix)
  // We initialize to a "Zero State" and then Swap.
  // This involves NO allocation (new).
  SimpleString(SimpleString &&other) noexcept
      : max_size{0}, buffer{nullptr}, length{0}
  {
    swap(*this, other);
  }

  // 5. Unified Assignment Operator (Handles Copy AND Move)
  SimpleString &operator=(SimpleString other)
  {
    swap(*this, other);
    return *this;
  }

  // 6. Friend Swap (Idiomatic)
  friend void swap(SimpleString &a, SimpleString &b) noexcept
  {
    using std::swap;
    swap(a.max_size, b.max_size);
    swap(a.length, b.length);
    swap(a.buffer, b.buffer);
  }

  void print(const char *tag) const { printf("%s: %s", tag, buffer); }
  bool append_line(const char *x)
  {
    const auto x_len = strlen(x);
    if (x_len + length + 2 > max_size)
      return false;
    std::strncpy(buffer + length, x, max_size - length);
    length += x_len;
    buffer[length++] = '\n';
    buffer[length] = 0;
    return true;
  }
};
int main()
{
  SimpleString a{50};
  a.append_line("1");
  a.print("a");
  SimpleString b{50};
  b.append_line("2");
  a = b;
  a.print("a");
  SimpleString c{50};
  c.append_line("3");
  a = std::move(c);
  a.print("a");
  SimpleString d{50};
  d.append_line("4");
  SimpleString str = std::move(d);
  str.print("a");
  SimpleString e{50};
  e.append_line("5");
  SimpleString str1 = e;
  str1.print("a");
}
