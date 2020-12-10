/* Your code here! */
#include "dsets.h"
#include "cs225/PNG.h"
#include <bitset>
#include <numeric>
#include <random>
#include <utility>
#include <queue>
#include <array>

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
  bool findPath(int x, int y, std::vector<int> &path);
  std::vector<int> findPath(const int x, const int y);
  int width_, height_;
  std::vector<std::array<bool, 2>> tiles_;
  DisjointSets dset_;
  struct BFSNode {
    bool visited;
    bool isPath;
    int dir;
  };
  std::vector<BFSNode> nodes_;
};