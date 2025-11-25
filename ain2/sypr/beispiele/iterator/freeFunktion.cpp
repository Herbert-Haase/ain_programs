#include <iostream>

class MyContainer
{
  int data_[5] = {1, 2, 3, 4, 5};

public:
  int *data() { return data_; }
  size_t size() const { return 5; }
};

// Free functions (found via ADL)
int *begin(MyContainer &c) { return c.data(); }
int *end(MyContainer &c) { return c.data() + c.size(); }

int main()
{
  MyContainer container;

  for (int value : container)
  {
    std::cout << value << ' ';
  }
}
