/* Your code here! */
#include "dsets.h"
#include "cs225/PNG.h"
#include <bitset>

class SquareMaze {
  public:
  SquareMaze() : width_(10), height_(10), tiles_(100), dset_() {}
  bool canTravel(int x, int y, int dir) const;
  cs225::PNG * drawMaze() const;
  cs225::PNG * drawMazeWithSolution();
  void makeMaze(int width, int height);
  void setWall(int x, int y, int dir, bool exists);
  std::vector<int> solveMaze();
  private:
  int width_, height_;
  std::vector<std::bitset<2>> tiles_;
  DisjointSets dset_;
};