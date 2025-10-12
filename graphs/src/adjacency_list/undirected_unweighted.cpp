#include "../../include/graph.hpp"
#include <algorithm>

template <typename VertexT>
class AdjListUndirectedUnweightedGraph
    : public UndirectedUnweightedGraph<VertexT>,
      public AdjList<VertexID> {
public:
  AdjListUndirectedUnweightedGraph() = default;
  ~AdjListUndirectedUnweightedGraph() override = default;

  void addVertex(VertexID id, const VertexT &value = VertexT{}) override {
    if (this->adj_list_.find(id) == this->adj_list_.end()) {
      this->adj_list_[id] = {};
      this->vertices_[id] = value;
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
      this->adj_list_[from].push_back(to);
      this->adj_list_[to].push_back(from);
    }
  }

  void removeVertex(VertexID id) override {
    this->adj_list_.erase(id);
    this->vertices_.erase(id);

    for (auto &[_, neighbors] : this->adj_list_) {
      neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), id),
                      neighbors.end());
    }
  }

  void removeEdge(VertexID from, VertexID to) override {
    auto it1 = this->adj_list_.find(from);
    if (it1 != this->adj_list_.end()) {
      auto &neighbors1 = it1->second;
      neighbors1.erase(std::remove(neighbors1.begin(), neighbors1.end(), to),
                       neighbors1.end());
    }

    auto it2 = this->adj_list_.find(to);
    if (it2 != this->adj_list_.end()) {
      auto &neighbors2 = it2->second;
      neighbors2.erase(std::remove(neighbors2.begin(), neighbors2.end(), from),
                       neighbors2.end());
    }
  }

  bool hasEdge(VertexID from, VertexID to) const override {
    auto it = this->adj_list_.find(from);
    if (it == this->adj_list_.end())
      return false;

    const auto &neighbors = it->second;
    return std::find(neighbors.begin(), neighbors.end(), to) != neighbors.end();
  }

  std::size_t getVertexCount() const override { return this->adj_list_.size(); }

  std::size_t getEdgeCount() const override {
    std::size_t count = 0;
    for (const auto &[_, neighbors] : this->adj_list_) {
      count += neighbors.size();
    }
    return count / 2;
  }

  std::vector<VertexID> getNeighbors(VertexID id) const override {
    auto it = this->adj_list_.find(id);
    if (it == this->adj_list_.end())
      return {};
    return it->second;
  }

  void bfs(VertexID start) const override { AdjList<VertexID>::bfs(start); }
};