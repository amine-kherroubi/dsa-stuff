#pragma once
#include "types.hpp"
#include <stdexcept>

class Graph {
protected:
  Vertices vertices;

public:
  Graph() = default;
  virtual ~Graph() = default;
  
  virtual void addVertex(VertexID) = 0;
  virtual void addEdge(const VertexID, const VertexID) = 0;
  virtual void removeVertex(VertexID) = 0;
  virtual void removeEdge(const VertexID, const VertexID) = 0;
  virtual bool hasEdge(const VertexID, const VertexID) const = 0;
  virtual int getVertexCount() const = 0;
  virtual int getEdgeCount() const = 0;

  void setVertexValue(VertexID id, int value) { vertices[id] = value; }

  int getVertexValue(VertexID id) const {
    auto it = vertices.find(id);
    if (it == vertices.end()) {
      throw std::out_of_range("Vertex ID not found in graph");
    }
    return it->second;
  }

  bool hasVertex(VertexID id) const {
    return vertices.find(id) != vertices.end();
  }
};

class DWG : public Graph {
public:
  DWG() = default;
  virtual ~DWG() = default;

  virtual int getEdgeWeight(const VertexID, const VertexID) const = 0;
};

class DUG : public Graph {
public:
  DUG() = default;
  virtual ~DUG() = default;
};

class UWG : public Graph {
public:
  UWG() = default;
  virtual ~UWG() = default;

  virtual int getEdgeWeight(const VertexID, const VertexID) const = 0;
};

class UUG : public Graph {
public:
  UUG() = default;
  virtual ~UUG() = default;
};