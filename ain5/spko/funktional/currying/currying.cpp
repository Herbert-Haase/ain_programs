#include <iostream>

using namespace std;

auto uncurried_add = [](int x, int y) { return x + y; };
auto curried_add = [](int x) { return [x](int y) { return x + y; }; };
auto curried_add3 = [](int x) {
  return [x](int y) { return [x, y](int z) { return x + y + z; }; };
};

int main() {
  cout << uncurried_add(3, 5) << endl;                            // 8
  cout << curried_add(3)(5) << endl;                              // 8
  cout << "curry 3 equals 10: " << curried_add3(3)(5)(2) << endl; // 10

  auto add_three = curried_add(3);
  cout << add_three(5) << endl;  // 8
  cout << add_three(12) << endl; // 15

  return 0;
}
