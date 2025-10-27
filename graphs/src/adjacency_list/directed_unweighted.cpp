#include "../../include/adjacency_list.hpp"
#include "../../include/graph.hpp"
#include <algorithm>

template <typename VertexT>
class AdjListDirectedUnweightedGraph : public DirectedUnweightedGraph<VertexT>,
                                       public AdjList<VertexID> {
public:
  AdjListDirectedUnweightedGraph() = default;
  ~AdjListDirectedUnweightedGraph() override = default;

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
    }
  }

  void removeVertex(VertexID id) override {
    auto it = this->adj_list_.find(id);
    if (it != this->adj_list_.end()) {
      this->adj_list_.erase(it);
    }
    this->vertices_.erase(id);

    for (auto &[_, neighbors] : this->adj_list_) {
      neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), id),
                      neighbors.end());
    }
  }

  void removeEdge(VertexID from, VertexID to) override {
    auto it = this->adj_list_.find(from);
    if (it == this->adj_list_.end())
      return;

    auto &neighbors = it->second;
    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), to),
                    neighbors.end());
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
    return count;
  }
};