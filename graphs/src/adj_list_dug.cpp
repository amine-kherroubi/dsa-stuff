#include "../include/graph.hpp"
#include <algorithm>

class AdjListDUG : public DUG {
private:
  AdjList adjList;

public:
  AdjListDUG() = default;
  ~AdjListDUG() override = default;

  void addVertex(VertexID id) override {
    if (adjList.find(id) == adjList.end()) {
      adjList[id] = {};
      vertices[id] = 0;
    }
  }

  void addEdge(VertexID from, VertexID to) override {
    adjList[from].push_back(to);
  }

  void removeVertex(VertexID id) override {
    auto it = adjList.find(id);
    if (it != adjList.end()) {
      adjList.erase(it);
    }

    for (auto &entry : adjList) {
      auto &neighbors = entry.second;
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

  int getVertexCount() const override {
    return static_cast<int>(adjList.size());
  }

  int getEdgeCount() const override {
    int count = 0;
    for (const auto &entry : adjList)
      count += static_cast<int>(entry.second.size());
    return count;
  }
};
