#pragma once

#include <cstddef>

using VertexID = std::size_t;

enum class VisitingState {
  Undiscovered,
  Discovered,
  Processed,
};