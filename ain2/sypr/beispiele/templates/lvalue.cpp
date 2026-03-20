#include <iostream>

template <char *s> void outs() { std::cout << s; }
template <int &s> void outs() { std::cout << s; }

char arr[] = "Weird workaround!";
int i = 10;

void use()
{
  // outs<"straightforward use">(); //** _error (for now)_
  outs<arr>(); //** _writes: Weird workaround!_
}

int main()
{
  outs<arr>();
  outs<i>();
}
