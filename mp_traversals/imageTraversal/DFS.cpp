#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png_ = png;
  tolerance_ = tolerance;
  points_ = std::list<Point>(1, start);
  startPixel_ = png.getPixel(start.x, start.y);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  std::stack<Point> pointStack;
  pointStack.push(points_.front());
  points_.pop_front();
  while (!pointStack.empty()) {
    Point curr = pointStack.top();
    pointStack.pop();
    if (std::find(points_.begin(), points_.end(), curr) == points_.end() && calculateDelta(startPixel_, png_.getPixel(curr.x, curr.y)) < tolerance_) {

      points_.push_back(curr);

      
      if (curr.x < png_.width() - 1) {
        Point right(curr.x + 1, curr.y);
        pointStack.push(right);
      }
      
      if (curr.y < png_.height() - 1) {
        Point below(curr.x, curr.y + 1);
        pointStack.push(below);
      }
      
      if (curr.x > 0) {
        Point left(curr.x - 1, curr.y);
        pointStack.push(left);
      }
      
      if (curr.y > 0) {
        Point above(curr.x, curr.y - 1);
        pointStack.push(above);
      }
    }
  }
  return ImageTraversal::Iterator(points_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(empty_);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  points_.push_front(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point ret = points_.front();
  points_.pop_front();
  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return points_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return points_.empty();
}
