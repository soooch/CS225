#include "List.h"
#include <iostream>

int main() {
  List<int> list;
  for (int i = 0; i < 100; i++) { list.insertBack(i); }
  list.reverseNth(10);
  for (auto iter = list.begin(); iter != list.end(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
  std::cout << "hello" << std::endl;
  return 0;
}
