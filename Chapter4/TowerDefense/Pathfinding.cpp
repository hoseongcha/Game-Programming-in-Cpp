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

		// ���� �湮�� ��尡 �������� ����!
		if (current == goal)
		{
			pathFound = true;
			break;
		}

		// ���� �湮�� ��尡 ù �湮���� �˻��ϰ�
		// ù �湮�̸� ���� ����� ���� ��带 ť�� �ִ´�.
		for (const GraphNode* node : current->adjacent)
		{
			const GraphNode* parent = outMap[node];

			// outMap�� nodeŰ�� �����ϸ� ������ �̹� �湮�ߴٴ� ���̴�.
			// (�ڽ��� �湮�ϱ� ���� ��带 parent�� �����ϱ� ������)
			// �Ǵ� ��� ����� ��� ������ �湮�� ��尡 ���� ������
			// parent�� nullptr �̱� ������ ���� ��尡 ��� ��������� �˻��Ѵ�.
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
	// �湮�� ����� ��� ����
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

				// ���� ����� ���� ������ �ĺ� ��尡 �ƴ϶��
				// �ĺ� ���� ����Ѵ�. (�޸���ƽ ����ؼ� open set�� ����)
				if (!data.inOpenSet)
				{
					data.heuristic = ComputeHeuristic(edge->to, goal);
					data.inOpenSet = true;
					openSet.emplace_back(edge->to);
				}
			}
		}

		// ���� �ĺ� ��尡 ���ٸ� �˰����� �����Ѵ�.
		if (openSet.empty())
			break;

		// �ĺ� ��� �߿� �޸���ƽ�� ���� �ּ��� ��带 ã�´�. (�켱������ ���� ���� ���)
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
		{
			return outMap[a].heuristic < outMap[b].heuristic;
		});

		// ���õ� ���� �湮�Ѵ�.
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

