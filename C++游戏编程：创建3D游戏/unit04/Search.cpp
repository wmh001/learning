#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>

//  ����ͼ��
struct GraphNode
{
	//  ���ڵ㼯��
	std::vector<GraphNode*> mAdjacent;
};

//  ����ͼ
struct Graph
{
	//  ͼ�е�ļ���
	std::vector<GraphNode*> mNodes;
};

//  ��Ȩ����ͼ��
struct WeightedEdge
{
	//  ������
	struct WeightedGraphNode* mFrom;
	//  �����
	struct WeightedGraphNode* mTo;
	//  Ȩֵ
	float mWeight;
};

//  ��Ȩ����ͼ��
struct WeightedGraphNode
{
	//  ����
	std::vector<WeightedEdge*> mEdges;
};

//  ��Ȩ����ͼ
struct WeightedGraph
{
	//  ͼ�е�ļ���
	std::vector<WeightedGraphNode*> mNodes;
};

//  ̰��������������ڵ���ʱ����
struct GBFSScratch
{
	//  ���ڵ�
	const WeightedEdge* mParentEdge = nullptr;
	//  heuristic����
	float mHeuristic = 0.0f;
	//  �Ƿ��ڿ�����
	bool mInOpenSet = false;
	//  �Ƿ��ڱռ���
	bool mInClosedSet = false;
};

//  �㵽��ʱ���ݵ�ӳ��
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

//  A*�����ڵ���ʱ����
struct AStarScratch
{
	//  ���ڵ�
	const WeightedEdge* mParentEdge = nullptr;
	//  heuristic����
	float mHeuristic = 0.0f;
	//  ʵ��·���ɱ�
	float mActualFromStart = 0.0f;
	//  �Ƿ��ڿ���
	bool mInOpenSet = false;
	//  �Ƿ��ڱռ�
	bool mInClosedSet = false;
};

//  �㵽��ʱ���ݵ�ӳ��
using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

//  ����heuristic����
float ComputeHeuristic(const WeightedGraphNode* a, const WeightedGraphNode* b)
{
	return 0.0f;
}

//  A*����
bool AStar(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, AStarMap& outMap)
{
	//  ���忪��
	std::vector<const WeightedGraphNode*> openSet;
	//  ��ǰ�ڵ�
	const WeightedGraphNode* current = start;
	//  ����ռ�
	outMap[current].mInClosedSet = true;
	//  ��ѭ��
	do
	{
		//  ����ڵ㵽����
		for (const WeightedEdge* edge : current->mEdges)
		{
			//  �õ���������
			const WeightedGraphNode* neighbor = edge->mTo;
			AStarScratch& data = outMap[neighbor];
			//  ���ڱռ�ʱ��ʼ����
			if (!data.mInClosedSet)
			{
				//  �ڵ����
				if (!data.mInOpenSet)
				{
					//  ���ڿ����У���ǰ�ڵ�Ϊ���ڵ�
					data.mParentEdge = edge;
					//  ����heuristic����
					data.mHeuristic = ComputeHeuristic(neighbor, goal);
					//  ʵ��·���ɱ�Ϊ���ڵ�ʵ��·���ɱ��ӱ����ߵĳɱ�
					data.mActualFromStart = outMap[current].mActualFromStart + edge->mWeight;
					//  ���뿪��
					data.mInOpenSet = true;
					openSet.emplace_back(neighbor);
				}
				else
				{
					//  �����ǰ�ڵ��ɸ��ڵ㣬�����µĳɱ�
					float newG = outMap[current].mActualFromStart + edge->mWeight;
					if (newG < data.mActualFromStart)
					{
						//  �ڽڵ����Ա仯
						data.mParentEdge = edge;
						data.mActualFromStart = newG;
					}
				}
			}
		}
		//  ����Ϊ�գ�����ѭ��
		if (openSet.empty())
		{
			break;
		}
		//  Ѱ�ҿ�������ͳɱ���
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
				//  ����f(x)
				float fOfA = outMap[a].mHeuristic + outMap[a].mActualFromStart;
				float fOfB = outMap[b].mHeuristic + outMap[b].mActualFromStart;
				return fOfA < fOfB;
			});
		//  ��ǰλ���ƶ�
		current = *iter;
		//  ��ռ�
		openSet.erase(iter);
		outMap[current].mInOpenSet = false;
		outMap[current].mInClosedSet = true;
	} while (current != goal);
	return (current == goal) ? true : false;
}

//  ̰�������������
bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, GBFSMap& outMap)
{
	//  ���忪��
	std::vector<const WeightedGraphNode*> openSet;
	//  ��ǰ�ڵ�
	const WeightedGraphNode* current = start;
	//  ����ռ�
	outMap[current].mInClosedSet = true;
	//  ��ѭ��
	do
	{
		//  ����ڵ㵽����
		for (const WeightedEdge* edge : current->mEdges)
		{
			//  �õ���������
			GBFSScratch& data = outMap[edge->mTo];
			//  ���ڱռ�ʱ��ʼ����
			if (!data.mInClosedSet)
			{
				//  ���ø��ڵ�
				data.mParentEdge = edge;
				if (!data.mInOpenSet)
				{
					//  ���������뿪��
					data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
					//  ���뿪��
					data.mInOpenSet = true;
					openSet.emplace_back(edge->mTo);
				}
			}
		}
		//  ����Ϊ�գ�����ѭ��
		if (openSet.empty())
		{
			break;
		}
		//  Ѱ�ҿ�������ͳɱ���
		auto iter = std::min_element(openSet.begin(), openSet.end(), [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
			{
				return outMap[a].mHeuristic < outMap[b].mHeuristic;
			});
		//  ��ǰλ���ƶ�
		current = *iter;
		//  ��������ռ�
		openSet.erase(iter);
		outMap[current].mInOpenSet = false;
		outMap[current].mInClosedSet = true;
	} while (current != goal);
	//  �ж��Ƿ��ҵ�
	return (current == goal) ? true : false;
}

//  �㵽��ʱ���ݵ�ӳ��
using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

//  �����������
bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap)
{
	//  �Ƿ��ҵ�һ��·
	bool pathFound = false;
	//  ��Ķ���
	std::queue<const GraphNode*> q;
	//  ��һ�������
	q.emplace(start);
	while (!q.empty())
	{
		//  һ��Ԫ�س���
		const GraphNode* current = q.front();
		q.pop();
		if (current == goal)
		{
			pathFound = true;
			break;
		}
		//  ������δ��ӽ�����
		for (const GraphNode* node : current->mAdjacent)
		{
			//  ���ʸ����
			const GraphNode* parent = outMap[node];
			if (parent == nullptr && node != start)
			{
				//  ��Ӳ��趨�����
				outMap[node] = current;
				q.emplace(node);
			}
		}
	}
	return pathFound;
}

//  BFS����
void testBFS()
{
	//  ��������ͼ
	Graph g;
	//  ����5*5���ڵ㲢��ͼ
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			GraphNode* node = new GraphNode;
			g.mNodes.emplace_back(node);
		}
	}
	//  ���������ڵ㽨��ͼ�����ڹ�ϵ
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			GraphNode* node = g.mNodes[i * 5 + j];
			if (i > 0)
			{
				node->mAdjacent.emplace_back(g.mNodes[(i - 1) * 5 + j]);
			}
			if (i < 4)
			{
				node->mAdjacent.emplace_back(g.mNodes[(i + 1) * 5 + j]);
			}
			if (j > 0)
			{
				node->mAdjacent.emplace_back(g.mNodes[i * 5 + j - 1]);
			}
			if (j < 4)
			{
				node->mAdjacent.emplace_back(g.mNodes[i * 5 + j + 1]);
			}
		}
	}
	//  Ѱ·
	NodeToParentMap map;
	bool found = BFS(g, g.mNodes[0], g.mNodes[9], map);
	std::cout << found << '\n';
}

//A*��̰�����������������
void testHeuristic(bool useAStar)
{
	//  �����Ȩ����ͼ
	WeightedGraph g;
	//  ����5*5���ڵ㲢��ͼ
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			WeightedGraphNode* node = new WeightedGraphNode;
			g.mNodes.emplace_back(node);
		}
	}
	//  ���������ڵ㽨��ͼ�����ڹ�ϵ�����ཨȪֵΪ1�ı�
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			WeightedGraphNode* node = g.mNodes[i * 5 + j];
			if (i > 0)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[(i - 1) * 5 + j];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
			if (i < 4)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[(i + 1) * 5 + j];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
			if (j > 0)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[i * 5 + j - 1];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
			if (j < 4)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[i * 5 + j + 1];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
		}
	}
	//  Ѱ·
	bool found = false;
	if (useAStar)
	{
		AStarMap map;
		found = AStar(g, g.mNodes[0], g.mNodes[9], map);
	}
	else
	{
		GBFSMap map;
		found = GBFS(g, g.mNodes[0], g.mNodes[9], map);
	}
	std::cout << found << '\n';
}

//  ��Ϸ��
//  ������Ϸ״̬
struct GameState
{
	//  ÿ����״̬
	enum SquareState
	{
		Empty, X, O
	};
	//  ���̷���״̬��ά����
	SquareState mBoard[3][3];
};

//  ��Ϸ���ڵ�
struct GTNode
{
	//  �ӽڵ�
	std::vector<GTNode*> mChildren;
	//  �õ���Ϸ״̬
	GameState mState;
};

//  ������Ϸ��
void GenStates(GTNode* root, bool xPlayer)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (root->mState.mBoard[i][j] == GameState::Empty)
			{
				GTNode* node = new GTNode;
				root->mChildren.emplace_back(node);
				node->mState = root->mState;
				node->mState.mBoard[i][j] = xPlayer ? GameState::X : GameState::O;
				GenStates(node, !xPlayer);
			}
		}
	}
}

//  �������
float GetScore(const GameState& state)
{
	//  �Ƿ���ͬ�з�����ͬ
	for (int i = 0; i < 3; i++)
	{
		bool same = true;
		GameState::SquareState v = state.mBoard[i][0];
		for (int j = 1; j < 3; j++)
		{
			if (state.mBoard[i][j] != v)
			{
				same = false;
			}
		}
		//  �жϵ÷�
		if (same)
		{
			if (v == GameState::X)
			{
				return 1.0f;
			}
			else
			{
				return -1.0f;
			}
		}
	}
	//  �Ƿ���ͬ��Ԫ����ͬ
	for (int j = 0; j < 3; j++)
	{
		bool same = true;
		GameState::SquareState v = state.mBoard[0][j];
		for (int i = 1; i < 3; i++)
		{
			if (state.mBoard[i][j] != v)
			{
				same = false;
			}
		}
		//  �жϵ÷�
		if (same)
		{
			if (v == GameState::X)
			{
				return 1.0f;
			}
			else
			{
				return -1.0f;
			}
		}
	}
	//  �Խ����Ƿ�����ͬԪ��
	if (((state.mBoard[0][0] == state.mBoard[1][1]) && (state.mBoard[1][1] == state.mBoard[2][2])) ||
		((state.mBoard[2][0] == state.mBoard[1][1]) && (state.mBoard[1][1] == state.mBoard[0][2])))
	{
		if (state.mBoard[1][1] == GameState::X)
		{
			return 1.0f;
		}
		else
		{
			return -1.0f;
		}
	}
	//  ƽ��
	return 0.0f;
}

//  ����С�㷨
float MinPlayer(const GTNode* node);

//  �����㷨
float MaxPlayer(const GTNode* node)
{
	//  Ҷ�ڵ㷵�ط���
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  Ѱ�ҷ���������Ϸ��
	float maxValue = -std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren)
	{
		maxValue = std::max(maxValue, MinPlayer(child));
	}
	return maxValue;
}

//  ��С�㷨
float MinPlayer(const GTNode* node)
{
	//  Ҷ�ڵ㷵�ط���
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  Ѱ�ҷ���������Ϸ��
	float minValue = -std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren)
	{
		minValue = std::min(minValue, MinPlayer(child));
	}
	return minValue;
}

//  ���ٲ������ֵ���ӽڵ�
const GTNode* MinimaxDecide(const GTNode* root)
{
	//  Ѱ�ҷ���������Ϸ��������������
	const GTNode* choice = nullptr;
	float maxValue = -std::numeric_limits<float>::infinity();
	for (const GTNode* child : root->mChildren)
	{
		float v = MinPlayer(child);
		if (v > maxValue)
		{
			maxValue = v;
			choice = child;
		}
	}
	return choice;
}

//  ��֦�㷨

float AlphaBetaMin(const GTNode* node, float alpha, float beta);

//  �����㷨
float AlphaBetaMax(const GTNode* node, float alpha, float beta)
{
	//  Ҷ�ڵ㷵�ط���
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  Ѱ�ҷ���������Ϸ��
	float maxValue = -std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren)
	{
		maxValue = std::max(maxValue, AlphaBetaMin(child, alpha, beta));
		if (maxValue >= beta)
		{
			return maxValue;
		}
		alpha = std::max(maxValue, alpha);
	}
	return maxValue;
}

//  ��С�㷨
float AlphaBetaMin(const GTNode* node, float alpha, float beta)
{
	//  Ҷ�ڵ㷵�ط���
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  Ѱ�ҷ���������Ϸ��
	float minValue = std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren)
	{
		minValue = std::min(minValue, AlphaBetaMax(child, alpha, beta));
		if (minValue <= alpha)
		{
			return minValue;
		}
		beta = std::min(minValue, beta);
	}
	return minValue;
}

//  ���ٲ������ֵ���ӽڵ�
const GTNode* AlphaBetaDecide(const GTNode* root)
{
	//  Ѱ�ҷ���������Ϸ��������������
	const GTNode* choice = nullptr;
	float maxValue = -std::numeric_limits<float>::infinity();
	float beta = std::numeric_limits<float>::infinity();
	for (const GTNode* child : root->mChildren)
	{
		float v = AlphaBetaMin(child, maxValue, beta);
		if (v > maxValue)
		{
			maxValue = v;
			choice = child;
		}
	}
	return choice;
}

//  ������Ϸ��
void testTicTac()
{
	GTNode* root = new GTNode;
	root->mState.mBoard[0][0] = GameState::O;
	root->mState.mBoard[0][1] = GameState::Empty;
	root->mState.mBoard[0][2] = GameState::X;
	root->mState.mBoard[1][0] = GameState::X;
	root->mState.mBoard[1][1] = GameState::O;
	root->mState.mBoard[1][2] = GameState::O;
	root->mState.mBoard[2][0] = GameState::X;
	root->mState.mBoard[2][1] = GameState::Empty;
	root->mState.mBoard[2][2] = GameState::Empty;

	GenStates(root, true);
	const GTNode* choice = AlphaBetaDecide(root);
	std::cout << choice->mChildren.size();
}
