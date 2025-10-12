#include "src/adjacency_list/directed_unweighted.cpp"
#include <iostream>

int main() {
  AdjListDirectedUnweightedGraph<std::string> graph;

  graph.addVertex(1, "Node A");
  graph.addVertex(2, "Node B");
  graph.addVertex(3, "Node C");
  graph.addVertex(4, "Node D");
  graph.addVertex(5, "Node E");
  graph.addVertex(6, "Node F");
  graph.addVertex(7, "Node G");
  graph.addVertex(8, "Node H");
  graph.addVertex(9, "Node I");
  graph.addVertex(10, "Node J");

  graph.addEdge(1, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 4);
  graph.addEdge(2, 5);
  graph.addEdge(3, 6);
  graph.addEdge(3, 7);
  graph.addEdge(4, 8);
  graph.addEdge(5, 9);
  graph.addEdge(6, 10);
  graph.addEdge(7, 10);
  graph.addEdge(8, 9);

  std::cout << "BFS Traversal:\n";

  graph.bfs(5, [&graph](std::optional<VertexID> vertex_opt) {
    if (vertex_opt.has_value()) {
      VertexID id = vertex_opt.value();
      std::string value = graph.getVertexValue(id);
      std::cout << "Visiting vertex " << id << ": " << value << "\n";
    }
  });

  return 0;
}