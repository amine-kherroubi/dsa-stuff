#pragma once

#include "types.hpp"
#include <map>
#include <queue>
#include <stack>

template <typename AdjListElement> class AdjList {
protected:
  std::map<VertexID, std::vector<AdjListElement>> adj_list_;

  static constexpr VertexID extractVertexID(const AdjListElement &element) {
    if constexpr (std::is_same_v<AdjListElement, VertexID>) {
      return element;
    } else {
      return element.first;
    }
  }

public:
  virtual std::vector<AdjListElement> getNeighbors(VertexID) const = 0;

  void bfs(VertexID root_id) const {
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

  void dfs(VertexID root_id) const {
    std::map<VertexID, VisitingState> visiting_state{};
    for (const auto &[vertex_id, _] : adj_list_) {
      visiting_state[vertex_id] = VisitingState::Undiscovered;
    }

    std::stack<VertexID> visiting_stack;
    visiting_state[root_id] = VisitingState::Discovered;
    visiting_stack.push(root_id);

    while (!visiting_stack.empty()) {
      VertexID current_vertex_id = visiting_stack.top();
      visiting_stack.pop();

      if (visiting_state[current_vertex_id] == VisitingState::Processed) {
        continue;
      }

      visiting_state[current_vertex_id] = VisitingState::Processed;

      for (const AdjListElement &list_element :
           adj_list_.at(current_vertex_id)) {
        VertexID neighbor_id = extractVertexID(list_element);
        if (visiting_state[neighbor_id] == VisitingState::Undiscovered) {
          visiting_state[neighbor_id] = VisitingState::Discovered;
          visiting_stack.push(neighbor_id);
        }
      }
    }
  }
};