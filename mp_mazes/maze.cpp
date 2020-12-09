/* Your code here! */
#include "maze.h"

bool SquareMaze::canTravel(int x, int y, int dir) const {
  int coord = x + y * width_;
  // no branches!!!
  bool posDirs[4];
  posDirs[0] = (width_ - 1) - x;
  posDirs[1] = (height_ - 1) - y;
  posDirs[2] = x;
  posDirs[3] = y;
  int offset = ((dir & 1) * (1 - width_) - 1) * (dir >> 1) * posDirs[dir];
  bool canTravel = posDirs[dir] && !tiles_[coord + offset][dir & 1];
  return posDirs[dir] && !tiles_[coord + offset][dir & 1];
}

cs225::PNG * SquareMaze::drawMaze() const {
  cs225::PNG * mazePNG = new cs225::PNG(width_*10+1, height_*10+1);
  for (unsigned int x = 10; x < mazePNG->width(); x++) {
    mazePNG->getPixel(x, 0).l = 0;
  }
  for (unsigned int y = 0; y < mazePNG->height(); y++) {
    mazePNG->getPixel(0, y).l = 0;
  }

  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      if (!canTravel(x, y, 0)) {
        for (int k = 0; k <= 10; k++) {
          mazePNG->getPixel((x+1)*10, y*10+k).l = 0;
        }
      }
      if (!canTravel(x, y, 1)) {
        for (int k = 0; k <= 10; k++) {
          mazePNG->getPixel(x*10+k, (y+1)*10).l = 0;
        }
      }
    }
  }

  return mazePNG;
}

cs225::PNG * SquareMaze::drawMazeWithSolution() {
  cs225::PNG * mazePNG = drawMaze();
  std::vector<int> solution = solveMaze();
  unsigned x = 5;
  unsigned y = 5;
  for (int step : solution) {
    switch (step)
    {
    case 0:
      for (int k = 0; k <= 10; k++) {
        mazePNG->getPixel(x + k, y).l = 0.5;
        mazePNG->getPixel(x + k, y).s = 1.0;
      }
      x += 10;
      break;
    
    case 1:
      for (int k = 0; k <= 10; k++) {
        mazePNG->getPixel(x, y + k).l = 0.5;
        mazePNG->getPixel(x, y + k).s = 1.0;
      }
      y += 10;
      break;
    
    case 2:
      for (int k = 0; k <= 10; k++) {
        mazePNG->getPixel(x - k, y).l = 0.5;
        mazePNG->getPixel(x - k, y).s = 1.0;
      }
      x -= 10;
      break;

    case 3:
      for (int k = 0; k <= 10; k++) {
        mazePNG->getPixel(x, y - k).l = 0.5;
        mazePNG->getPixel(x, y - k).s = 1.0;
      }
      y -= 10;
      break;

    default:
      break;
    }
  }
  for (int k = 0; k < 9; k++) {
    mazePNG->getPixel(x - 4 + k, y + 5).l = 1.0;
  }
  return mazePNG;
}

void SquareMaze::makeMaze(int width, int height) {
  width_ = width;
  height_ = height;
  int size = width * height;
  tiles_ = std::vector<std::bitset<2>>(size, 0b11);
  auto rng = std::mt19937(rand());
  std::vector<std::pair<int, int>> coords(size);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      coords[x + y * width] = std::make_pair(x, y);
    }
  }
  std::shuffle(coords.begin(), coords.end(), rng);
  dset_.addelements(size);
  for (auto coord : coords) {
    int x = coord.first; int y = coord.second;
    int tile = y * width + x;
    if (rand() % 2) {
      if (x < width - 1) {
        if (dset_.find(tile) != dset_.find(tile + 1)) {
          dset_.setunion(tile, tile + 1);
          tiles_[tile][0] = false;
        }
      }
      if (y < height - 1) {
        if (dset_.find(tile) != dset_.find(tile + width)) {
          dset_.setunion(tile, tile + width);
          tiles_[tile][1] = false;
        }
      }
    }
    else {
      if (y < height - 1) {
        if (dset_.find(tile) != dset_.find(tile + width)) {
          dset_.setunion(tile, tile + width);
          tiles_[tile][1] = false;
        }
      }
      if (x < width - 1) {
        if (dset_.find(tile) != dset_.find(tile + 1)) {
          dset_.setunion(tile, tile + 1);
          tiles_[tile][0] = false;
        }
      }
    }
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  tiles_[x + y * width_][dir] = exists;
}

std::vector<int> SquareMaze::solveMaze() {
  std::vector<int> bestPath;
  for (int i = 0; i < width_; i++) {
    int end = i + (height_ - 1) * width_;
    if (dset_.find(end) == dset_.find(0)) {
      std::vector<int> path(1, 3);
      findPath(i, height_ - 1, path);
      if (path.size() > bestPath.size()) {
        bestPath = std::move(path);
      }
    }
  }
  std::vector<int> ret(bestPath.size() - 1);
  std::transform(bestPath.rbegin(), bestPath.rend() - 1, ret.begin(), [](int dir){return dir ^ 2;});
  return ret;
}

bool SquareMaze::findPath(int x, int y, std::vector<int> &path) { 
  if (x == 0 && y == 0) return true;
  for (int dir = 3; dir >=0; dir--) {
    if (dir != (path.back() ^ 2) && canTravel(x, y, dir)) {
      path.push_back(dir);
      int offset_sign = 1 - (dir & 2);
      if (findPath(x + !(dir & 1) * offset_sign, y + (dir & 1) * offset_sign, path)) {
        return true;
      };
      path.pop_back();
    }
  }
  return false;
}