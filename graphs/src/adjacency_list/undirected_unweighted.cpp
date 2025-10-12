#include "../../include/graph.hpp"
#include <algorithm>

template <typename VertexT>
class AdjListUndirectedUnweightedGraph
    : public UndirectedUnweightedGraph<VertexT> {
private:
  std::map<VertexID, std::vector<VertexID>> adjList;

public:
  AdjListUndirectedUnweightedGraph() = default;
  ~AdjListUndirectedUnweightedGraph() override = default;

  void addVertex(VertexID id, const VertexT &value = VertexT{}) override {
    if (adjList.find(id) == adjList.end()) {
      adjList[id] = {};
      this->vertices[id] = value;
    }
  }

  void addEdge(VertexID from, VertexID to) override {
    if (!this->hasVertex(from)) {
      addVertex(from);
    }
    if (!this->hasVertex(to)) {
      addVertex(to);
    }

    if (!hasEdge(from, to)) {
      adjList[from].push_back(to);
      adjList[to].push_back(from);
    }
  }

  void removeVertex(VertexID id) override {
    adjList.erase(id);
    this->vertices.erase(id);

    for (auto &[_, neighbors] : adjList) {
      neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), id),
                      neighbors.end());
    }
  }

  void removeEdge(VertexID from, VertexID to) override {
    auto it1 = adjList.find(from);
    if (it1 != adjList.end()) {
      auto &neighbors1 = it1->second;
      neighbors1.erase(std::remove(neighbors1.begin(), neighbors1.end(), to),
                       neighbors1.end());
    }

    auto it2 = adjList.find(to);
    if (it2 != adjList.end()) {
      auto &neighbors2 = it2->second;
      neighbors2.erase(std::remove(neighbors2.begin(), neighbors2.end(), from),
                       neighbors2.end());
    }
  }

  bool hasEdge(VertexID from, VertexID to) const override {
    auto it = adjList.find(from);
    if (it == adjList.end())
      return false;

    const auto &neighbors = it->second;
    return std::find(neighbors.begin(), neighbors.end(), to) != neighbors.end();
  }

  std::size_t getVertexCount() const override { return adjList.size(); }

  std::size_t getEdgeCount() const override {
    std::size_t count = 0;
    for (const auto &[_, neighbors] : adjList) {
      count += neighbors.size();
    }
    return count / 2;
  }

  std::vector<VertexID> getNeighbors(VertexID id) const {
    auto it = adjList.find(id);
    if (it == adjList.end())
      return {};
    return it->second;
  }
};