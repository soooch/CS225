#include "List.h"
#include <iostream>

int main() {
  List<int> list;
  List<int> listb;
  for (int i = 0; i < 100; i++) {
    if (i > 30 || i < 3) {
      list.insertBack(i); 
    }
    if ((i > 5 && i < 28) || (i > 67 && i < 98)) {
      listb.insertBack(i);
    }
  }
  for (auto iter = list.begin(); iter != list.end(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
  for (auto iter = listb.begin(); iter != listb.end(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
  list.mergeWith(listb);
  for (auto iter = list.begin(); iter != list.end(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
  return 0;
}
