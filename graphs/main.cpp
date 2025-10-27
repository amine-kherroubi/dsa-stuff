#include "include/types.hpp"
#include "src/adjacency_list/undirected_unweighted.cpp"
#include <iostream>

int main() {
  AdjListUndirectedUnweightedGraph<int> graph;

  graph.addVertex(0, 0);
  graph.addVertex(1, 10);
  graph.addVertex(2, 20);
  graph.addVertex(3, 30);
  graph.addVertex(4, 40);
  graph.addVertex(5, 50);
  graph.addVertex(6, 60);
  graph.addVertex(7, 70);
  graph.addVertex(8, 80);
  graph.addVertex(9, 90);
  graph.addVertex(10, 100);
  graph.addVertex(11, 110);
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 3);
  graph.addEdge(3, 4);
  graph.addEdge(4, 5);
  graph.addEdge(5, 6);
  graph.addEdge(6, 7);
  graph.addEdge(7, 0);
  graph.addEdge(2, 8);
  graph.addEdge(8, 9);
  graph.addEdge(9, 10);
  graph.addEdge(10, 11);

  std::cout << "Graph Statistics:\n";
  std::cout << "Vertices: " << graph.getVertexCount() << "\n";
  std::cout << "Edges: " << graph.getEdgeCount() << "\n\n";

  std::vector<VertexID> cycle_path = graph.shortestCycle();

  std::cout << "Shortest Cycle Length: " << cycle_path.size() << "\n";
  std::cout << "Shortest Cycle Path: ";
  for (size_t i = 0; i < cycle_path.size(); ++i) {
    std::cout << cycle_path[i];
    if (i < cycle_path.size() - 1)
      std::cout << " -> ";
  }
  std::cout << "\n";

  return 0;
}
