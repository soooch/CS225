/* Your code here! */
#include "maze.h"

bool SquareMaze::canTravel(int x, int y, int dir) const {
  int coord = x + y * width_;
  // no branches!!!
  bool posDirs[4];
  posDirs[0] = true;
  posDirs[1] = true;
  posDirs[2] = x;
  posDirs[3] = y;
  int offset = ((dir & 1) * (1 - width_) - 1) * (dir >> 1) * posDirs[dir];
  return posDirs[dir] & tiles_[coord + offset][dir & 1];
}

cs225::PNG * SquareMaze::drawMaze() const {
  return NULL;
}

cs225::PNG * SquareMaze::drawMazeWithSolution() {
  return NULL;
}

void SquareMaze::makeMaze(int width, int height) {
  width_ = width;
  height_ = height;
  int size = width * height;
  tiles_ = std::vector<std::bitset<2>>(size, 0b11);
  dset_.addelements(size);
  int rejections = 0;
  while (rejections < size) {
    int randy = rand() % height;
    int randx = rand() % width;
    bool posDirs[4];
    posDirs[0] = width - randx - 1;
    posDirs[1] = height - randy - 1;
    posDirs[2] = randx;
    posDirs[3] = randy;

    int randTile = randy * width + randx;
    int dir = rand() % 4;
    dir ^= !posDirs[dir] << 1;
    int offset = (1 - (dir & 2)) * ((dir & 1) * (width - 1) + 1);
    if (dset_.find(randTile) != dset_.find(randTile + offset)) {
      dset_.setunion(randTile, randTile + offset);
      offset *= dir >> 1;
      tiles_[randTile + offset][dir & 1] = false;
      rejections = 0;
    }
    else {
      // TODO: actually figure out the end case
      std::cout << "rip" << std::endl;
      rejections++;
    }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << tiles_[i * width + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << tiles_[i * width + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  tiles_[x + y * width_][dir] = exists;
}

std::vector<int> SquareMaze::solveMaze() {
  return std::vector<int>();
}

