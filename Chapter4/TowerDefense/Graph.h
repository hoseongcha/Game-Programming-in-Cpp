#pragma once

#include <vector>

struct GraphNode
{
	std::vector<GraphNode*> adjacent;
};

struct Graph
{
	std::vector<GraphNode*> nodes;
};

struct WeightedEdge
{
	struct WeightedGraphNode* from;
	struct WeightedGraphNode* to;
	float weight;
};

struct WeightedGraphNode
{
	std::vector<WeightedEdge*> edges;
};

struct WeightedGraph
{
	std::vector<WeightedGraphNode*> nodes;
};