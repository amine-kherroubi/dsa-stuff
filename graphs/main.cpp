#include "src/adjacency_list/directed_unweighted.cpp"
#include <iostream>

int main() {
  AdjListDirectedWeightedGraph<int> intGraph;

  intGraph.addVertex(1, 100);
  intGraph.addVertex(2, 200);
  intGraph.addVertex(3, 300);

  intGraph.addEdge(1, 2);
  intGraph.addEdge(2, 3);
  intGraph.addEdge(1, 3);

  std::cout << "Integer Graph:\n";
  std::cout << "Vertices: " << intGraph.getVertexCount() << "\n";
  std::cout << "Edges: " << intGraph.getEdgeCount() << "\n";
  std::cout << "Vertex 1 value: " << intGraph.getVertexValue(1) << "\n";
  std::cout << "Has edge 1->2: " << intGraph.hasEdge(1, 2) << "\n\n";

  return 0;
}