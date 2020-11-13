/* Your code here! */
#include <vector>

class DisjointSets {
  std::vector<int> _arena;
  public:
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
  int size(int elem);
};