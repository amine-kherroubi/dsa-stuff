#include "src/adjacency_list/directed_unweighted.cpp"

int main() {
  AdjListDirectedUnweightedGraph<int> intGraph;

  intGraph.addVertex(1, 100);
  intGraph.addVertex(2, 200);
  intGraph.addVertex(3, 300);

  intGraph.addEdge(1, 2);
  intGraph.addEdge(2, 3);
  intGraph.addEdge(1, 3);

  intGraph.bfs(1);

  return 0;
}