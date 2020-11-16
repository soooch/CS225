/* Your code here! */
#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num) {
  arena_.insert(arena_.end(), num, -1);
}

int DisjointSets::find(int elem) {
  std::vector<int> pathNodes;
  while (arena_[elem] >=0) {
    pathNodes.push_back(elem);
    elem = arena_[elem];
  }
  for (auto node : pathNodes) {
    arena_[node] = elem;
  }
  std::cout << "find" << std::endl;
  for (int elem : arena_) {
    std::cout << elem << " ";
  }
  std::cout << std::endl << std::endl;
  return elem;
}

void DisjointSets::setunion(int a, int b) {
  std::cout << "setunion" << std::endl;
  a = find(a);
  b = find(b);
  if (a == b) return;
  if (arena_[b] < arena_[a]) {
    arena_[b] += arena_[a];
    arena_[a] = b;
  }
  else {
    arena_[a] += arena_[b];
    arena_[b] = a;
  }
  for (int elem : arena_) {
    std::cout << elem << " ";
  }
  std::cout << std::endl << std::endl;
}

int DisjointSets::size(int elem) {
  return -arena_[find(elem)];
}

//int findCircleNum(std::vector<std::vector<int>>& M) {
//    // your code
//    std::vector<int> disjoint(M.size(), -1);
//    for (int i = 0; i < M.size(); i++) {
//        for (int i : disjoint) {
//            std::cout << i << " ";
//        }
//        std::cout << std::endl;
//        int childCount = 0;
//        for (int j = i + 1; j < M[i].size(); j++) {
//            if (M[i][j]) {
//                int x = i;
//                while (disjoint[x] >= 0) {
//                    x = disjoint[x];
//                }
//                int y = j;
//                while (disjoint[y] >= 0) {
//                    y = disjoint[y];
//                }
//                if (x==y) {
//                    continue;
//                }
//                std::vector<int> fliplist(1, j);
//                int curr = disjoint[j];
//                for (; curr >= 0; curr = disjoint[curr]) {
//                    fliplist.push_back(curr);
//                }
//                for (auto it = fliplist.rbegin(); it != fliplist.rend() - 1; ++it) {
//                    disjoint[*it] = *(it + 1);
//                }
//                childCount += curr;
//                disjoint[j] = i;
//            }
//        }
//        int curr = i;
//        while (disjoint[curr] >= 0) {
//            curr = disjoint[curr];
//        }
//        disjoint[curr] += childCount;
//    }
//    for (int i : disjoint) {
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
//    return std::count_if(disjoint.begin(), disjoint.end(), [](int elem){return elem < 0;});
//}