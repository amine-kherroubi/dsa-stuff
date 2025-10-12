#include "../../include/graph.hpp"
#include <algorithm>

template <typename VertexT>
class AdjListDirectedWeightedGraph : public DirectedUnweightedGraph<VertexT> {
private:
  std::map<VertexID, std::vector<VertexID>> adjList;

public:
  AdjListDirectedWeightedGraph() = default;
  ~AdjListDirectedWeightedGraph() override = default;

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
    }
  }

  void removeVertex(VertexID id) override {
    auto it = adjList.find(id);
    if (it != adjList.end()) {
      adjList.erase(it);
    }
    this->vertices.erase(id);

    for (auto &[_, neighbors] : adjList) {
      neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), id),
                      neighbors.end());
    }
  }

  void removeEdge(VertexID from, VertexID to) override {
    auto it = adjList.find(from);
    if (it == adjList.end())
      return;

    auto &neighbors = it->second;
    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), to),
                    neighbors.end());
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
    return count;
  }

  std::vector<VertexID> getNeighbors(VertexID id) const {
    auto it = adjList.find(id);
    if (it == adjList.end())
      return {};
    return it->second;
  }
};