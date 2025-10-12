#include "../../include/graph.hpp"
#include <algorithm>

template <typename VertexT, typename WeightT>
class AdjListDirectedWeightedGraph
    : public DirectedWeightedGraph<VertexT, WeightT>,
      public AdjList<std::pair<VertexID, WeightT>> {
public:
  AdjListDirectedWeightedGraph() = default;
  ~AdjListDirectedWeightedGraph() override = default;

  void addVertex(VertexID id, const VertexT &value = VertexT{}) override {
    if (this->adj_list_.find(id) == this->adj_list_.end()) {
      this->adj_list_[id] = {};
      this->vertices_[id] = value;
    }
  }

  void addEdge(VertexID from, VertexID to, WeightT weight) override {
    if (!this->hasVertex(from)) {
      addVertex(from);
    }
    if (!this->hasVertex(to)) {
      addVertex(to);
    }

    if (!hasEdge(from, to)) {
      this->adj_list_[from].push_back({to, weight});
    }
  }

  void removeVertex(VertexID id) override {
    auto it = this->adj_list_.find(id);
    if (it != this->adj_list_.end()) {
      this->adj_list_.erase(it);
    }
    this->vertices_.erase(id);

    for (auto &[_, neighbors] : this->adj_list_) {
      neighbors.erase(
          std::remove_if(neighbors.begin(), neighbors.end(),
                         [id](const auto &pair) { return pair.first == id; }),
          neighbors.end());
    }
  }

  void removeEdge(VertexID from, VertexID to) override {
    auto it = this->adj_list_.find(from);
    if (it == this->adj_list_.end())
      return;

    auto &neighbors = it->second;
    neighbors.erase(
        std::remove_if(neighbors.begin(), neighbors.end(),
                       [to](const auto &pair) { return pair.first == to; }),
        neighbors.end());
  }

  bool hasEdge(VertexID from, VertexID to) const override {
    auto it = this->adj_list_.find(from);
    if (it == this->adj_list_.end())
      return false;

    const auto &neighbors = it->second;
    return std::find_if(neighbors.begin(), neighbors.end(),
                        [to](const auto &pair) { return pair.first == to; }) !=
           neighbors.end();
  }

  WeightT getEdgeWeight(VertexID from, VertexID to) const override {
    auto it = this->adj_list_.find(from);
    if (it == this->adj_list_.end())
      throw std::invalid_argument("Source vertex not found");

    const auto &neighbors = it->second;
    auto edge =
        std::find_if(neighbors.begin(), neighbors.end(),
                     [to](const auto &pair) { return pair.first == to; });

    if (edge == neighbors.end())
      throw std::invalid_argument("Edge not found");

    return edge->second;
  }

  std::size_t getVertexCount() const override { return this->adj_list_.size(); }

  std::size_t getEdgeCount() const override {
    std::size_t count = 0;
    for (const auto &[_, neighbors] : this->adj_list_) {
      count += neighbors.size();
    }
    return count;
  }

  std::vector<std::pair<VertexID, WeightT>>
  getNeighbors(VertexID id) const override {
    auto it = this->adj_list_.find(id);
    if (it == this->adj_list_.end())
      return {};
    return it->second;
  }

  void bfs(VertexID root_id,
           std::function<void(std::optional<VertexID>)> callback =
               nullptr) const override {
    AdjList<std::pair<VertexID, WeightT>>::bfs(root_id, callback);
  }
};
