#include "../../include/adjacency_list.hpp"
#include "../../include/graph.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

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

  std::vector<VertexID> shortestCycle() const {
    std::size_t shortest_cycle_length = SIZE_MAX;
    std::vector<VertexID> shortest_cycle_path;

    for (const auto &[start_vertex, _] : adj_list_) {
      std::map<VertexID, std::pair<VisitingState, std::size_t>>
          visiting_information;
      std::map<VertexID, VertexID> parent;

      for (const auto &[vertex_id, _] : adj_list_) {
        visiting_information[vertex_id] = {VisitingState::Undiscovered,
                                           SIZE_MAX};
      }

      std::queue<VertexID> visiting_queue;
      visiting_information[start_vertex] = {VisitingState::Discovered, 0};
      parent[start_vertex] = start_vertex;
      visiting_queue.push(start_vertex);

      while (!visiting_queue.empty()) {
        VertexID current_vertex_id = visiting_queue.front();
        visiting_queue.pop();

        for (const VertexID &neighbor_id : adj_list_.at(current_vertex_id)) {
          if (visiting_information[neighbor_id].first ==
              VisitingState::Undiscovered) {
            visiting_information[neighbor_id] = {
                VisitingState::Discovered,
                visiting_information[current_vertex_id].second + 1};
            parent[neighbor_id] = current_vertex_id;
            visiting_queue.push(neighbor_id);

          } else if (parent[current_vertex_id] != neighbor_id) {
            std::size_t cycle_length =
                visiting_information[current_vertex_id].second +
                visiting_information[neighbor_id].second + 1;

            if (cycle_length < shortest_cycle_length) {
              shortest_cycle_length = cycle_length;

              std::vector<VertexID> path1, path2;
              VertexID v = current_vertex_id;
              while (v != start_vertex) {
                path1.push_back(v);
                v = parent[v];
              }
              path1.push_back(start_vertex);

              v = neighbor_id;
              while (v != start_vertex) {
                path2.push_back(v);
                v = parent[v];
              }

              shortest_cycle_path.clear();
              shortest_cycle_path.insert(shortest_cycle_path.end(),
                                         path1.rbegin(), path1.rend());
              shortest_cycle_path.insert(shortest_cycle_path.end(),
                                         path2.begin(), path2.end());
            }
          }
        }
        visiting_information[current_vertex_id].first =
            VisitingState::Processed;
      }
    }

    return shortest_cycle_path;
  }
};