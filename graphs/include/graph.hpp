#pragma once
#include "types.hpp"
#include <cstddef>
#include <functional>
#include <map>
#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>

template <typename VertexT> class Graph {
protected:
  std::map<VertexID, VertexT> vertices_;

public:
  Graph() = default;
  virtual ~Graph() = default;
  virtual void addVertex(VertexID id, const VertexT &value = VertexT{}) = 0;
  virtual void removeVertex(VertexID id) = 0;
  virtual void removeEdge(VertexID from, VertexID to) = 0;
  virtual bool hasEdge(VertexID from, VertexID to) const = 0;
  virtual std::size_t getVertexCount() const = 0;
  virtual std::size_t getEdgeCount() const = 0;
  virtual void bfs(VertexID root_id,
                   std::function<void(std::optional<VertexID>)> callback =
                       nullptr) const = 0;

  void setVertexValue(VertexID id, const VertexT &value) {
    if (!hasVertex(id))
      throw std::invalid_argument("Cannot set value for non-existent vertex");
    vertices_[id] = value;
  }

  VertexT getVertexValue(VertexID id) const {
    auto it = vertices_.find(id);
    if (it == vertices_.end())
      throw std::out_of_range("Vertex ID not found");
    return it->second;
  }

  bool hasVertex(VertexID id) const {
    return vertices_.find(id) != vertices_.end();
  }

  std::vector<VertexID> getVertices() const {
    std::vector<VertexID> result;
    result.reserve(vertices_.size());
    for (const auto &[id, _] : vertices_) {
      result.push_back(id);
    }
    return result;
  }
};

template <typename VertexT, typename WeightT = int>
class DirectedWeightedGraph : public Graph<VertexT> {
public:
  DirectedWeightedGraph() = default;
  virtual ~DirectedWeightedGraph() = default;
  virtual void addEdge(VertexID from, VertexID to, WeightT weight) = 0;
  virtual WeightT getEdgeWeight(VertexID from, VertexID to) const = 0;
};

template <typename VertexT>
class DirectedUnweightedGraph : public Graph<VertexT> {
public:
  DirectedUnweightedGraph() = default;
  virtual ~DirectedUnweightedGraph() = default;
  virtual void addEdge(VertexID from, VertexID to) = 0;
};

template <typename VertexT, typename WeightT = int>
class UndirectedWeightedGraph : public Graph<VertexT> {
public:
  UndirectedWeightedGraph() = default;
  virtual ~UndirectedWeightedGraph() = default;
  virtual void addEdge(VertexID from, VertexID to, WeightT weight) = 0;
  virtual WeightT getEdgeWeight(VertexID from, VertexID to) const = 0;
};

template <typename VertexT>
class UndirectedUnweightedGraph : public Graph<VertexT> {
public:
  UndirectedUnweightedGraph() = default;
  virtual ~UndirectedUnweightedGraph() = default;
  virtual void addEdge(VertexID from, VertexID to) = 0;
};

template <typename AdjListElement> class AdjList {
protected:
  std::map<VertexID, std::vector<AdjListElement>> adj_list_;

private:
  static constexpr VertexID extractVertexID(const AdjListElement &element) {
    if constexpr (std::is_same_v<AdjListElement, VertexID>) {
      return element;
    } else {
      return element.first;
    }
  }

public:
  virtual std::vector<AdjListElement> getNeighbors(VertexID id) const = 0;
  void
  bfs(VertexID root_id,
      std::function<void(std::optional<VertexID>)> callback = nullptr) const {
    std::map<VertexID, VisitingState> visiting_state{};
    for (const auto &[vertex_id, _] : adj_list_) {
      visiting_state[vertex_id] = VisitingState::Undiscovered;
    }

    std::queue<VertexID> visiting_queue;
    visiting_state[root_id] = VisitingState::Discovered;
    visiting_queue.push(root_id);

    while (!visiting_queue.empty()) {
      VertexID current_vertex_id = visiting_queue.front();
      visiting_queue.pop();

      if (callback) {
        callback(std::optional<VertexID>(current_vertex_id));
      }

      for (const AdjListElement &list_element :
           adj_list_.at(current_vertex_id)) {
        VertexID neighbor_id = extractVertexID(list_element);
        if (visiting_state[neighbor_id] == VisitingState::Undiscovered) {
          visiting_state[neighbor_id] = VisitingState::Discovered;
          visiting_queue.push(neighbor_id);
        }
      }
      visiting_state[current_vertex_id] = VisitingState::Processed;
    }
  }
};