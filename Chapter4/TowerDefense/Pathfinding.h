#pragma once

#include "Graph.h"
#include <unordered_map>

//
// Breadth First Search (BFS)
//

using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

bool BFS(const Graph& graph, const GraphNode* start,
	const GraphNode* goal, NodeToParentMap& outMap);

//
// Greedy Best First Search
//

struct GBFSScratch
{
	const WeightedEdge* parentEdge = nullptr;
	float heuristic = 0.0f;
	bool inOpenSet = false;
	bool inClosedSet = false;
};

using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start,
	const WeightedGraphNode* goal, GBFSMap& outMap);

//
// AStar Search
//
struct AStarScratch
{
	const WeightedEdge* parentEdge = nullptr;
	float heuristic = 0.0f;
	float actualFromStart = 0.0f;
	bool inOpenSet = false;
	bool inCloseSet = false;
};

using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

bool AStar(const WeightedGraph& graph, const WeightedGraphNode* start,
	const WeightedGraphNode* goal, AStarMap& outMap);