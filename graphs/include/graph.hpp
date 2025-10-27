#pragma once

#include "types.hpp"
#include <cstddef>
#include <map>
#include <stdexcept>
#include <vector>

template <typename VertexT> class Graph {
protected:
  std::map<VertexID, VertexT> vertices_;

public:
  Graph() = default;
  virtual ~Graph() = default;
  virtual void addVertex(VertexID, const VertexT & = VertexT{}) = 0;
  virtual void removeVertex(VertexID) = 0;
  virtual void removeEdge(VertexID, VertexID) = 0;
  virtual bool hasEdge(VertexID, VertexID) const = 0;
  virtual std::size_t getVertexCount() const = 0;
  virtual std::size_t getEdgeCount() const = 0;

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

template <typename VertexT> class UnWeightedGraph : public Graph<VertexT> {
public:
  virtual void addEdge(VertexID, VertexID) = 0;
};

template <typename VertexT, typename WeightT>
class WeightedGraph : public Graph<VertexT> {
public:
  virtual void addEdge(VertexID, VertexID, WeightT) = 0;
  virtual WeightT getEdgeWeight(VertexID, VertexID) const = 0;
};

template <typename VertexT>
class UndirectedUnweightedGraph : public UnWeightedGraph<VertexT> {
public:
  UndirectedUnweightedGraph() = default;
  virtual ~UndirectedUnweightedGraph() = default;
};

template <typename VertexT>
class DirectedUnweightedGraph : public UnWeightedGraph<VertexT> {
public:
  DirectedUnweightedGraph() = default;
  virtual ~DirectedUnweightedGraph() = default;
};

template <typename VertexT, typename WeightT = int>
class UndirectedWeightedGraph : public WeightedGraph<VertexT, WeightT> {
public:
  UndirectedWeightedGraph() = default;
  virtual ~UndirectedWeightedGraph() = default;
};

template <typename VertexT, typename WeightT = int>
class DirectedWeightedGraph : public WeightedGraph<VertexT, WeightT> {
public:
  DirectedWeightedGraph() = default;
  virtual ~DirectedWeightedGraph() = default;
};