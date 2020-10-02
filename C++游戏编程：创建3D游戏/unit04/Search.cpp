#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>

//  无向图点
struct GraphNode
{
	//  相邻点集合
	std::vector<GraphNode*> mAdjacent;
};

//  无向图
struct Graph
{
	//  图中点的集合
	std::vector<GraphNode*> mNodes;
};

//  加权有向图边
struct WeightedEdge
{
	//  出发点
	struct WeightedGraphNode* mFrom;
	//  射入点
	struct WeightedGraphNode* mTo;
	//  权值
	float mWeight;
};

//  加权有向图点
struct WeightedGraphNode
{
	//  出边
	std::vector<WeightedEdge*> mEdges;
};

//  加权有向图
struct WeightedGraph
{
	//  图中点的集合
	std::vector<WeightedGraphNode*> mNodes;
};

//  贪婪最佳优先搜索节点临时数据
struct GBFSScratch
{
	//  父节点
	const WeightedEdge* mParentEdge = nullptr;
	//  heuristic距离
	float mHeuristic = 0.0f;
	//  是否在开集中
	bool mInOpenSet = false;
	//  是否在闭集中
	bool mInClosedSet = false;
};

//  点到临时数据的映射
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

//  A*搜索节点临时数据
struct AStarScratch
{
	//  父节点
	const WeightedEdge* mParentEdge = nullptr;
	//  heuristic距离
	float mHeuristic = 0.0f;
	//  实际路径成本
	float mActualFromStart = 0.0f;
	//  是否在开集
	bool mInOpenSet = false;
	//  是否在闭集
	bool mInClosedSet = false;
};

//  点到临时数据的映射
using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

//  计算heuristic距离
float ComputeHeuristic(const WeightedGraphNode* a, const WeightedGraphNode* b)
{
	return 0.0f;
}

//  A*搜索
bool AStar(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, AStarMap& outMap)
{
	//  定义开集
	std::vector<const WeightedGraphNode*> openSet;
	//  当前节点
	const WeightedGraphNode* current = start;
	//  进入闭集
	outMap[current].mInClosedSet = true;
	//  主循环
	do
	{
		//  加入节点到开集
		for (const WeightedEdge* edge : current->mEdges)
		{
			//  得到额外数据
			const WeightedGraphNode* neighbor = edge->mTo;
			AStarScratch& data = outMap[neighbor];
			//  不在闭集时开始考虑
			if (!data.mInClosedSet)
			{
				//  节点采用
				if (!data.mInOpenSet)
				{
					//  不在开集中，则当前节点为父节点
					data.mParentEdge = edge;
					//  计算heuristic距离
					data.mHeuristic = ComputeHeuristic(neighbor, goal);
					//  实际路径成本为父节点实际路径成本加遍历边的成本
					data.mActualFromStart = outMap[current].mActualFromStart + edge->mWeight;
					//  进入开集
					data.mInOpenSet = true;
					openSet.emplace_back(neighbor);
				}
				else
				{
					//  如果当前节点变成父节点，计算新的成本
					float newG = outMap[current].mActualFromStart + edge->mWeight;
					if (newG < data.mActualFromStart)
					{
						//  邻节点属性变化
						data.mParentEdge = edge;
						data.mActualFromStart = newG;
					}
				}
			}
		}
		//  开集为空，结束循环
		if (openSet.empty())
		{
			break;
		}
		//  寻找开集中最低成本的
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
				//  计算f(x)
				float fOfA = outMap[a].mHeuristic + outMap[a].mActualFromStart;
				float fOfB = outMap[b].mHeuristic + outMap[b].mActualFromStart;
				return fOfA < fOfB;
			});
		//  当前位置移动
		current = *iter;
		//  入闭集
		openSet.erase(iter);
		outMap[current].mInOpenSet = false;
		outMap[current].mInClosedSet = true;
	} while (current != goal);
	return (current == goal) ? true : false;
}

//  贪婪最佳优先搜索
bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, GBFSMap& outMap)
{
	//  定义开集
	std::vector<const WeightedGraphNode*> openSet;
	//  当前节点
	const WeightedGraphNode* current = start;
	//  进入闭集
	outMap[current].mInClosedSet = true;
	//  主循环
	do
	{
		//  加入节点到开集
		for (const WeightedEdge* edge : current->mEdges)
		{
			//  得到额外数据
			GBFSScratch& data = outMap[edge->mTo];
			//  不在闭集时开始考虑
			if (!data.mInClosedSet)
			{
				//  设置父节点
				data.mParentEdge = edge;
				if (!data.mInOpenSet)
				{
					//  计算距离加入开集
					data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
					//  进入开集
					data.mInOpenSet = true;
					openSet.emplace_back(edge->mTo);
				}
			}
		}
		//  开集为空，结束循环
		if (openSet.empty())
		{
			break;
		}
		//  寻找开集中最低成本的
		auto iter = std::min_element(openSet.begin(), openSet.end(), [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
			{
				return outMap[a].mHeuristic < outMap[b].mHeuristic;
			});
		//  当前位置移动
		current = *iter;
		//  出开集入闭集
		openSet.erase(iter);
		outMap[current].mInOpenSet = false;
		outMap[current].mInClosedSet = true;
	} while (current != goal);
	//  判断是否找到
	return (current == goal) ? true : false;
}

//  点到临时数据的映射
using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

//  广度优先搜索
bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap)
{
	//  是否找到一条路
	bool pathFound = false;
	//  点的队列
	std::queue<const GraphNode*> q;
	//  第一个点进队
	q.emplace(start);
	while (!q.empty())
	{
		//  一个元素出队
		const GraphNode* current = q.front();
		q.pop();
		if (current == goal)
		{
			pathFound = true;
			break;
		}
		//  相邻且未入队结点入队
		for (const GraphNode* node : current->mAdjacent)
		{
			//  访问父结点
			const GraphNode* parent = outMap[node];
			if (parent == nullptr && node != start)
			{
				//  入队并设定父结点
				outMap[node] = current;
				q.emplace(node);
			}
		}
	}
	return pathFound;
}

//  BFS测试
void testBFS()
{
	//  定义无向图
	Graph g;
	//  定义5*5个节点并入图
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			GraphNode* node = new GraphNode;
			g.mNodes.emplace_back(node);
		}
	}
	//  矩阵内相邻点建立图内相邻关系
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
	//  寻路
	NodeToParentMap map;
	bool found = BFS(g, g.mNodes[0], g.mNodes[9], map);
	std::cout << found << '\n';
}

//A*与贪婪最佳优先搜索测试
void testHeuristic(bool useAStar)
{
	//  定义加权有向图
	WeightedGraph g;
	//  定义5*5个节点并入图
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			WeightedGraphNode* node = new WeightedGraphNode;
			g.mNodes.emplace_back(node);
		}
	}
	//  矩阵内相邻点建立图内相邻关系并互相建泉值为1的边
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
	//  寻路
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

//  游戏树
//  棋盘游戏状态
struct GameState
{
	//  每个的状态
	enum SquareState
	{
		Empty, X, O
	};
	//  棋盘方格状态二维数组
	SquareState mBoard[3][3];
};

//  游戏树节点
struct GTNode
{
	//  子节点
	std::vector<GTNode*> mChildren;
	//  该点游戏状态
	GameState mState;
};

//  生成游戏树
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

//  计算分数
float GetScore(const GameState& state)
{
	//  是否有同行方格相同
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
		//  判断得分
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
	//  是否有同列元素相同
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
		//  判断得分
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
	//  对角线是否有相同元素
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
	//  平局
	return 0.0f;
}

//  极大极小算法
float MinPlayer(const GTNode* node);

//  极大算法
float MaxPlayer(const GTNode* node)
{
	//  叶节点返回分数
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  寻找分数最大的游戏树
	float maxValue = -std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren)
	{
		maxValue = std::max(maxValue, MinPlayer(child));
	}
	return maxValue;
}

//  极小算法
float MinPlayer(const GTNode* node)
{
	//  叶节点返回分数
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  寻找分数最大的游戏树
	float minValue = -std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren)
	{
		minValue = std::min(minValue, MinPlayer(child));
	}
	return minValue;
}

//  跟踪产生最佳值的子节点
const GTNode* MinimaxDecide(const GTNode* root)
{
	//  寻找分数最大的游戏树，并保存子树
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

//  剪枝算法

float AlphaBetaMin(const GTNode* node, float alpha, float beta);

//  极大算法
float AlphaBetaMax(const GTNode* node, float alpha, float beta)
{
	//  叶节点返回分数
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  寻找分数最大的游戏树
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

//  最小算法
float AlphaBetaMin(const GTNode* node, float alpha, float beta)
{
	//  叶节点返回分数
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	//  寻找分数最大的游戏树
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

//  跟踪产生最佳值的子节点
const GTNode* AlphaBetaDecide(const GTNode* root)
{
	//  寻找分数最大的游戏树，并保存子树
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

//  测试游戏树
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
