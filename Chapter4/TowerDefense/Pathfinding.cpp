#include "Pathfinding.h"
#include <queue>

bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap)
{
	bool pathFound = false;

	std::queue<const GraphNode*> q;
	q.emplace(start);

	while (!q.empty())
	{
		const GraphNode* current = q.front();
		q.pop();

		// 현재 방문할 노드가 목적지면 도착!
		if (current == goal)
		{
			pathFound = true;
			break;
		}

		// 현재 방문할 노드가 첫 방문인지 검사하고
		// 첫 방문이면 현재 노드의 인접 노드를 큐에 넣는다.
		for (const GraphNode* node : current->adjacent)
		{
			const GraphNode* parent = outMap[node];

			// outMap에 node키가 존재하면 예전에 이미 방문했다는 뜻이다.
			// (자신을 방문하기 전에 노드를 parent로 저장하기 때문에)
			// 또는 출발 노드의 경우 이전에 방문한 노드가 없기 때문에
			// parent는 nullptr 이기 때문에 현재 노드가 출발 노드인지도 검사한다.
			if (parent == nullptr && node != start)
			{
				outMap[node] = current;
				q.emplace(node);
			}
		}
	}

	return pathFound;
}

float ComputeHeuristic(const WeightedGraphNode* start, const WeightedGraphNode* goal)
{
	return 0.0f;
}

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, GBFSMap& outMap)
{
	// 방문을 고려할 노드 집합
	std::vector<const WeightedGraphNode*> openSet;
	
	const WeightedGraphNode* current = start;
	outMap[current].inClosedSet = true;

	do
	{
		for (const WeightedEdge* edge : current->edges)
		{
			GBFSScratch& data = outMap[edge->to];

			if (!data.inClosedSet)
			{
				data.parentEdge = edge;

				// 현재 노드의 인접 노드들이 후보 노드가 아니라면
				// 후보 노드로 등록한다. (휴리스틱 계산해서 open set에 넣음)
				if (!data.inOpenSet)
				{
					data.heuristic = ComputeHeuristic(edge->to, goal);
					data.inOpenSet = true;
					openSet.emplace_back(edge->to);
				}
			}
		}

		// 평가할 후보 노드가 없다면 알고리즘을 종료한다.
		if (openSet.empty())
			break;

		// 후보 노드 중에 휴리스틱이 가장 최소인 노드를 찾는다. (우선순위가 가장 높은 노드)
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
		{
			return outMap[a].heuristic < outMap[b].heuristic;
		});

		// 선택된 노드로 방문한다.
		current = *iter;
		openSet.erase(iter);
		outMap[current].inOpenSet = false;
		outMap[current].inClosedSet = true;
	} while (current != goal);

	return (current == goal) ? true : false;
}

bool AStar(const WeightedGraph & graph, const WeightedGraphNode * start, const WeightedGraphNode * goal, AStarMap & outMap)
{
	std::vector<const WeightedGraphNode*> openSet;

	const WeightedGraphNode* current = start;
	outMap[current].inCloseSet = true;

	do
	{
		for (const WeightedEdge* edge : current->edges)
		{
			AStarScratch& data = outMap[edge->to];

			if (!data.inCloseSet)
			{
				if (!data.inOpenSet)
				{
					data.parentEdge = edge;
					data.heuristic = ComputeHeuristic(edge->to, goal);
					data.actualFromStart = outMap[current].actualFromStart + edge->weight;
					data.inOpenSet = true;
					openSet.emplace_back(edge->to);
				}
				else
				{
					float newActualFromStart = outMap[current].actualFromStart + edge->weight;
					if (newActualFromStart < data.actualFromStart)
					{
						data.parentEdge = edge;
						data.actualFromStart = newActualFromStart;
					}
				}
			}
		}
		
		if (openSet.empty())
			break;

		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
		{
			return outMap[a].actualFromStart + outMap[a].heuristic
				< outMap[b].actualFromStart + outMap[b].heuristic;
		});

		current = *iter;
		openSet.erase(iter);
		outMap[current].inOpenSet = false;
		outMap[current].inCloseSet = true;

	} while (current != goal);

	return (current == goal) ? true : false;
}

