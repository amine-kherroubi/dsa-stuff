#pragma once

#include "types.hpp"
#include <map>
#include <stdexcept>
#include <vector>

template <typename VertexT> class Graph {
protected:
  std::map<VertexID, VertexT> vertices;

public:
  Graph() = default;
  virtual ~Graph() = default;

  virtual void addVertex(VertexID id, const VertexT &value = VertexT{}) = 0;
  virtual void removeVertex(VertexID id) = 0;
  virtual void removeEdge(VertexID from, VertexID to) = 0;
  virtual bool hasEdge(VertexID from, VertexID to) const = 0;
  virtual std::size_t getVertexCount() const = 0;
  virtual std::size_t getEdgeCount() const = 0;

  void setVertexValue(VertexID id, const VertexT &value) {
    if (!hasVertex(id))
      throw std::invalid_argument("Cannot set value for non-existent vertex");
    vertices[id] = value;
  }

  VertexT getVertexValue(VertexID id) const {
    auto it = vertices.find(id);
    if (it == vertices.end())
      throw std::out_of_range("Vertex ID not found");
    return it->second;
  }

  bool hasVertex(VertexID id) const {
    return vertices.find(id) != vertices.end();
  }

  std::vector<VertexID> getVertices() const {
    std::vector<VertexID> result;
    result.reserve(vertices.size());
    for (const auto &[id, _] : vertices) {
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