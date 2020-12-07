/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  /*
  residual_ = startingGraph;
  flow_ = startingGraph;
  for (Edge edge : flow_.getEdges()) {
    flow_.setEdgeWeight(edge.source, edge.dest, 0);
  }
  */
  for(Edge temp : g_.getEdges()){
   	 flow_.insertEdge(temp.source, temp.dest);
   	 flow_.setEdgeWeight(temp.source, temp.dest, 0);
   	 residual_.insertEdge(temp.source, temp.dest);
   	 residual_.setEdgeWeight(temp.source, temp.dest, temp.getWeight());
   	 residual_.insertEdge(temp.dest, temp.source);
   	 residual_.setEdgeWeight(temp.dest, temp.source, 0);
    }

    maxFlow_ = 0;

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  /*
  int min_weight = INT_MAX;
  for (auto it = path.begin(); it < path.end() - 1; it++) {
    min_weight = std::min(min_weight, residual_.getEdge(*it, *(it + 1)).getWeight());
  }
  return min_weight;
  */
 int FCAP;  
    for(unsigned long i = 0; i < path.size()-1; i++){
   	 if(i == 0){FCAP = residual_.getEdgeWeight(path[i], path[i+1]);}
   	 else{
   		 if(FCAP > residual_.getEdgeWeight(path[i], path[i+1])){
   			 FCAP = residual_.getEdgeWeight(path[i], path[i+1]);
   		 }
   	 }
    }
  return FCAP;

}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  /*
  vector<Vertex> path;
  while (findAugmentingPath(source_, sink_, path)) {
    int cap = pathCapacity(path);
    for (auto it = path.begin(); it < path.end() - 1; it++) {
      std::cout << *it << std::endl;
      if (flow_.edgeExists(*it, *(it + 1))) {
        flow_.setEdgeWeight(*it, *(it + 1), flow_.getEdge(*it, *(it + 1)).getWeight() + cap);
        residual_.setEdgeWeight(*it, *(it + 1), residual_.getEdgeWeight(*it, *(it + 1)) - cap);
      }
      else {
        flow_.setEdgeWeight(*(it + 1), *it, flow_.getEdge(*(it + 1), *it).getWeight() - cap);
        residual_.setEdgeWeight(*(it + 1), *it, residual_.getEdgeWeight(*(it + 1), *it) + cap);
      }
    }
  }
  */
 vector <Vertex> path;
    while(findAugmentingPath(source_, sink_, path)){ //1
   	 int PCAP = pathCapacity(path); //2
   	 for(unsigned long i = 0; i < path.size()-1; i++){  //3.1
   		 if(flow_.edgeExists(path[i], path[i+1])){  // Add to corresponding path
   			 flow_.setEdgeWeight(path[i], path[i+1], flow_.getEdgeWeight(path[i], path[i+1]) + PCAP);
   		 }
   		 else{ //In case of opposite direction
   			 flow_.setEdgeWeight(path[i+1], path[i], flow_.getEdgeWeight(path[i+1], path[i]) - PCAP);
   		 }
   		 residual_.setEdgeWeight(path[i], path[i+1], residual_.getEdgeWeight(path[i], path[i+1]) - PCAP); //3.2
   		 residual_.setEdgeWeight(path[i+1], path[i], residual_.getEdgeWeight(path[i+1], path[i]) + PCAP); //3.3
   	 }
   	 maxFlow_ += PCAP;
    }


  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

