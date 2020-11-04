/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    return (first[curDim] != second[curDim]) ? first[curDim] < second[curDim] : first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
  double distPotential = 0.0;
  double distBest = 0.0;
  for (int i = 0; i < Dim; i++) {
    distPotential += std::pow(potential[i] - target[i], 2);
    distBest += std::pow(currentBest[i] - target[i], 2);
  }

  return (distPotential != distBest) ? distPotential < distBest : potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> points = newPoints;
    size = newPoints.size();
    root = buildKDTree(points, 0, points.size() - 1, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildKDTree(vector<Point<Dim>>& points, 
                                                   int first, 
                                                   int last, 
                                                   int curDim)
{
  if (first > last) return NULL;
  int median = first + (last - first) / 2;
  select(points, first, last, median, curDim);
  KDTreeNode * newNode = new KDTreeNode(points[median]);
  newNode->left = buildKDTree(points, first, median - 1, (curDim + 1) % Dim);
  newNode->right = buildKDTree(points, median + 1, last, (curDim + 1) % Dim);
  return newNode;
}

template <int Dim>
void KDTree<Dim>::select(vector<Point<Dim>>& points,
                int first,
                int last, 
                int k,
                int curDim)
{
  if (first == last) {
    return;
  }
  int pivotIndex = first + (last - first) / 2;
  pivotIndex = partition(points, first, last, pivotIndex, curDim);
  if (k == pivotIndex) {
    return;
  }
  else if (k < pivotIndex) {
    return select(points, first, pivotIndex - 1, k, curDim);
  }
  else {
    return select(points, pivotIndex + 1, last, k, curDim);
  }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, 
              int first, 
              int last, 
              int pivotIndex, 
              int curDim)
{
  auto pivotValue = points[pivotIndex];
  std::swap(points[pivotIndex], points[last]);
  int storeIndex = first;
  for (int i = first; i < last; i++) {
    if (smallerDimVal(points[i], pivotValue, curDim)) {
      std::swap(points[storeIndex], points[i]);
      storeIndex++;
    }
  }
  std::swap(points[last], points[storeIndex]);
  return storeIndex;
}




template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  root = copyKDTree(other.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copyKDTree(KDTreeNode * other) {
  if (other == NULL) return NULL;
  KDTreeNode * tmp = new KDTreeNode(other->point);
  tmp->left = copyKDTree(other->left);
  tmp->right = copyKDTree(other->right);
  return tmp;
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (*this != rhs) {
    *this = KDTree(rhs);
  }

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::deleteKDTree() {
  if (other == NULL) return NULL;
  KDTreeNode * tmp = new KDTreeNode(other->point);
  deleteKDTree(other->left);
  deleteKDTree(other->right);
  delete tmp;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

