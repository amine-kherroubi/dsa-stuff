#include "../../include/graph.hpp"
#include <algorithm>

template <typename VertexT>
class AdjListUndirectedUnweightedGraph
    : public UndirectedUnweightedGraph<VertexT> {
private:
  std::map<VertexID, std::vector<VertexID>> adj_list;

public:
  AdjListUndirectedUnweightedGraph() = default;
  ~AdjListUndirectedUnweightedGraph() override = default;

  void addVertex(VertexID id, const VertexT &value = VertexT{}) override {
    if (adj_list.find(id) == adj_list.end()) {
      adj_list[id] = {};
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
      adj_list[from].push_back(to);
      adj_list[to].push_back(from);
    }
  }

  void removeVertex(VertexID id) override {
    adj_list.erase(id);
    this->vertices.erase(id);

    for (auto &[_, neighbors] : adj_list) {
      neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), id),
                      neighbors.end());
    }
  }

  void removeEdge(VertexID from, VertexID to) override {
    auto it1 = adj_list.find(from);
    if (it1 != adj_list.end()) {
      auto &neighbors1 = it1->second;
      neighbors1.erase(std::remove(neighbors1.begin(), neighbors1.end(), to),
                       neighbors1.end());
    }

    auto it2 = adj_list.find(to);
    if (it2 != adj_list.end()) {
      auto &neighbors2 = it2->second;
      neighbors2.erase(std::remove(neighbors2.begin(), neighbors2.end(), from),
                       neighbors2.end());
    }
  }

  bool hasEdge(VertexID from, VertexID to) const override {
    auto it = adj_list.find(from);
    if (it == adj_list.end())
      return false;

    const auto &neighbors = it->second;
    return std::find(neighbors.begin(), neighbors.end(), to) != neighbors.end();
  }

  std::size_t getVertexCount() const override { return adj_list.size(); }

  std::size_t getEdgeCount() const override {
    std::size_t count = 0;
    for (const auto &[_, neighbors] : adj_list) {
      count += neighbors.size();
    }
    return count / 2;
  }

  std::vector<VertexID> getNeighbors(VertexID id) const {
    auto it = adj_list.find(id);
    if (it == adj_list.end())
      return {};
    return it->second;
  }
};