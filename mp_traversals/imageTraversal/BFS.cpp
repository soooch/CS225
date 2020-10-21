#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  tolerance_ = tolerance;
  points_ = std::list<Point>(1, start);
  startPixel_ = png.getPixel(start.x, start.y);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  std::queue<Point> pointQueue;
  pointQueue.push(points_.front());
  points_.pop_front();
  while (!pointQueue.empty()) {
    Point curr = pointQueue.front();
    pointQueue.pop();
    if (std::find(points_.begin(), points_.end(), curr) == points_.end()) {
      
      points_.push_back(curr);
      
      if (curr.x < png_.width() - 1) {
        Point right(curr.x + 1, curr.y);
        pointQueue.push(right);
      }
      
      if (curr.y < png_.height() - 1) {
        Point below(curr.x, curr.y + 1);
        pointQueue.push(below);
      }
      
      if (curr.x > 0) {
        Point left(curr.x - 1, curr.y);
        pointQueue.push(left);
      }
      
      if (curr.y > 0) {
        Point above(curr.x, curr.y - 1);
        pointQueue.push(above);
      }
    }
  }
  points_.remove_if([this](Point point) {return calculateDelta(startPixel_, png_.getPixel(point.x, point.y)) >= tolerance_;});
  return ImageTraversal::Iterator(points_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(empty_);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  points_.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point ret = points_.front();
  points_.pop_front();
  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return points_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return points_.empty();
}
