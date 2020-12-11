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
  return posDirs[dir] && !tiles_[coord + offset][dir & 1];
}
/*
bool SquareMaze::canTravel(int x, int y, int dir) const {
  int coord = x+y*width_;
  switch (dir) {
    case 0:
      if (width_ - 1 - x) {
        return !tiles_[coord][0];
      }
      return false;
    
    case 1:
      if (height_ - 1 - y) {
        return !tiles_[coord][1];
      }
      return false;
    
    case 2:
      if (x) {
        return !tiles_[coord - 1][0];
      }
      return false;

    case 3:
      if (y) {
        return !tiles_[coord - width_][1];
      }
      return false;

    default:
     return false;
  }
}
*/

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
  tiles_ = std::vector<std::array<bool, 2>>(size, {true, true});
  nodes_ = std::vector<BFSNode>(size, BFSNode {false, -1});
  visited_ = std::vector<bool>(size, false);
  pathSize = height_ * 2;
  nodes_[0].isPath = true;
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
      std::vector<int> path = findPath(i, height_ - 1);
      if (path.size() > bestPath.size()) {
        bestPath = std::move(path);
      }
    }
  }
  std::fill(nodes_.begin(), nodes_.end(), BFSNode {false, -1});
  nodes_[0].isPath = true;
  return bestPath;
}

std::vector<int> SquareMaze::findPath(const int x, const int y) {
  std::queue<std::array<int, 2>> BFSQueue;
  
  BFSQueue.push({x, y});

  while (!BFSQueue.empty()) {
    auto coord = BFSQueue.front();
    BFSQueue.pop();
    if (nodes_[coord[0] + coord[1] * width_].isPath) {
      break;
    }
    for (int dir = 3; dir >= 0; dir--) {
      if (canTravel(coord[0], coord[1], dir)) {
        std::array<int, 2> newCoord = {coord[0] + ((1 - (dir&2))*!(dir&1)), coord[1] + ((1 - (dir&2))*(dir&1))};
        if (!visited_[newCoord[0] + newCoord[1] * width_]) {
          visited_[newCoord[0] + newCoord[1] * width_] = true;
          nodes_[newCoord[0] + newCoord[1] * width_].dir = dir ^ 2;
          BFSQueue.push(newCoord);
        }
      }
    }
  }

  std::fill(visited_.begin(), visited_.end(), false);

  std::vector<int> ret;
  ret.reserve(pathSize);
  for (int i = 0, j = 0; i != x || j != y;) {
    nodes_[i + j * width_].isPath = true;
    const int dir = nodes_[i + j * width_].dir;
    ret.push_back(dir);
    i += ((1 - (dir&2))*!(dir&1));
    j += ((1 - (dir&2))*(dir&1));
  }
  pathSize = ret.size();

  return ret;
}
/*
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
*/
/*
std::vector<int> SquareMaze::findPath(int x, int y) {
  std::vector<bool> discovered(tiles_.size(), false);
  std::queue<std::pair<std::array<int, 2>, std::vector<int>>> BFSQueue;
  
  BFSQueue.push(std::make_pair(std::array<int, 2>{x, y}, std::vector<int>()));

  std::vector<int> path;

  while (!BFSQueue.empty()) {
    auto node = BFSQueue.front();
    BFSQueue.pop();
    if (node.first[0] == 0 && node.first[1] == 0) {
      return node.second;
    }
    for (int dir = 3; dir >= 0; dir--) {
      if (canTravel(node.first[0], node.first[1], dir)) {
        std::array<int, 2> newCoord = {node.first[0] + ((1 - (dir&2))*!(dir&1)), node.first[1] + ((1 - (dir&2))*(dir&1))};
        if (!discovered[newCoord[0] + newCoord[1] * width_]) {
          discovered[newCoord[0] + newCoord[1] * width_] = true;
          auto newPath(node.second);
          newPath.push_back(dir);
          BFSQueue.push(std::make_pair(newCoord, newPath));
        }
      }
    }
  }
  return std::vector<int>();
}
*/
