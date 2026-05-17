#include <functional>
#include <iostream>
#include <string>

using Continuation = std::function<void(int)>;

void fakultaet(int n, Continuation c) {
  if (n == 0) {
    c(1);
    return;
  }

  fakultaet(n - 1, [c, n](int f) { c(n * f); });
}

int main(int argc, char *argv[]) {
  int n = (argc > 1) ? std::stoi(argv[1]) : 5;

  fakultaet(n, [](int f) { std::cout << "Ergebnis: " << f << std::endl; });

  return 0;
}
