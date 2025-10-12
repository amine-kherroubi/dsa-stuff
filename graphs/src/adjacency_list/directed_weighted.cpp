#include "../../include/graph.hpp"
#include <algorithm>

template <typename VertexT, typename WeightT>
class AdjListDirectedWeightedGraph
    : public DirectedWeightedGraph<VertexT, WeightT> {
private:
  std::map<VertexID, std::vector<std::pair<VertexID, WeightT>>> adj_list;

public:
  AdjListDirectedWeightedGraph() = default;
  ~AdjListDirectedWeightedGraph() override = default;

  void addVertex(VertexID id, const VertexT &value = VertexT{}) override {
    if (adj_list.find(id) == adj_list.end()) {
      adj_list[id] = {};
      this->vertices[id] = value;
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
      adj_list[from].push_back({to, weight});
    }
  }

  void removeVertex(VertexID id) override {
    auto it = adj_list.find(id);
    if (it != adj_list.end()) {
      adj_list.erase(it);
    }
    this->vertices.erase(id);

    for (auto &[_, neighbors] : adj_list) {
      neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(),
                                     [id](const auto &pair) {
                                       return pair.first == id;
                                     }), // FIXED
                      neighbors.end());
    }
  }

  void removeEdge(VertexID from, VertexID to) override {
    auto it = adj_list.find(from);
    if (it == adj_list.end())
      return;

    auto &neighbors = it->second;
    neighbors.erase(
        std::remove_if(neighbors.begin(), neighbors.end(),
                       [to](const auto &pair) { return pair.first == to; }),
        neighbors.end());
  }

  bool hasEdge(VertexID from, VertexID to) const override {
    auto it = adj_list.find(from);
    if (it == adj_list.end())
      return false;

    const auto &neighbors = it->second;
    return std::find_if(neighbors.begin(), neighbors.end(),
                        [to](const auto &pair) { return pair.first == to; }) !=
           neighbors.end();
  }

  WeightT getEdgeWeight(VertexID from, VertexID to) const override {
    auto it = adj_list.find(from);
    if (it == adj_list.end())
      throw std::invalid_argument("Source vertex not found");

    const auto &neighbors = it->second;
    auto edge =
        std::find_if(neighbors.begin(), neighbors.end(),
                     [to](const auto &pair) { return pair.first == to; });

    if (edge == neighbors.end())
      throw std::invalid_argument("Edge not found");

    return edge->second;
  }

  std::size_t getVertexCount() const override { return adj_list.size(); }

  std::size_t getEdgeCount() const override {
    std::size_t count = 0;
    for (const auto &[_, neighbors] : adj_list) {
      count += neighbors.size();
    }
    return count;
  }

  std::vector<std::pair<VertexID, WeightT>> getNeighbors(VertexID id) const {
    auto it = adj_list.find(id);
    if (it == adj_list.end())
      return {};
    return it->second;
  }
};