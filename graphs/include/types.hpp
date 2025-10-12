#pragma once

#include <map>
#include <vector>

using VertexID = int;
using Weight = int;

using AdjList = std::map<VertexID, std::vector<VertexID>>;
using Vertices = std::map<VertexID, int>;