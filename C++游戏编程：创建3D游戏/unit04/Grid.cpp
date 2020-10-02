#include "Grid.h"
#include "Tile.h"
#include "Tower.h"
#include "Enemy.h"
#include "Game.h"
#include <algorithm>

Grid::Grid(class Game* game)
	:Actor(game)
	, mSelectedTile(nullptr)
{
	//  7行16列
	//  分配空间
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}
	//  创建方格
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
		}
	}
	//  设定起始方格状态
	GetStartTile()->SetTileState(Tile::EStart);
	//  设定结束方格状态
	GetEndTile()->SetTileState(Tile::EBase);
	//  方格互联
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			if (i > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i - 1][j]);
			}
			if (i < NumRows - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i + 1][j]);
			}
			if (j > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j - 1]);
			}
			if (j < NumCols - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j + 1]);
			}
		}
	}
	//  寻找初始路径
	FindPath(GetEndTile(), GetStartTile());
	//  更新路径方格
	UpdatePathTiles(GetStartTile());
	//  初始化敌人到来时间
	mNextEnemy = EnemyTime;
}

void Grid::SelectTile(size_t row, size_t col)
{
	//  确保选择合法
	Tile::TileState tstate = mTiles[row][col]->GetTileState();
	if (tstate != Tile::EStart && tstate != Tile::EBase)
	{
		//  取消上一个选择
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}
		//  设定新的被选方格
		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();
	}
}

void Grid::ProcessClick(int x, int y)
{
	y -= static_cast<int>(StartY - TileSize / 2);
	if (y >= 0)
	{
		//  计算行列
		x /= static_cast<int>(TileSize);
		y /= static_cast<int>(TileSize);
		if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
		{
			SelectTile(y, x);
		}
	}
}

//  实现A*寻路
bool Grid::FindPath(Tile* start, Tile* goal)
{
	//  初始化每格
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j]->g = 0.0f;
			mTiles[i][j]->mInOpenSet = false;
			mTiles[i][j]->mInClosedSet = false;
		}
	}
	//  定义开集
	std::vector<Tile*> openSet;
	//  当前节点
	Tile* current = start;
	//  进入闭集
	current->mInClosedSet = true;
	//  主循环
	do
	{
		//  加入节点到开集
		for (Tile* neighbor : current->mAdjacent)
		{
			//  是否为障碍
			if (neighbor->mBlocked)
			{
				continue;
			}
			//  不在闭集时开始考虑
			if (!neighbor->mInClosedSet)
			{
				//  节点采用
				if (!neighbor->mInOpenSet)
				{
					//  不在开集中，则当前节点为父节点
					neighbor->mParent = current;
					//  计算heuristic距离
					neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
					//  实际路径成本为父节点实际路径成本加过边的成本
					neighbor->g = current->g + TileSize;
					//  计算f(x)
					neighbor->f = neighbor->g + neighbor->h;
                    //  加入开集
					openSet.emplace_back(neighbor);
					neighbor->mInOpenSet = true;
				}
				else
				{
					//  如果当前节点变成父节点，计算新的成本
					float newG = current->g + TileSize;
					if (newG < neighbor->g)
					{
						//  邻节点属性变化
						neighbor->mParent = current;
						neighbor->g = newG;
						//  计算f(x)
						neighbor->f = neighbor->g + neighbor->h;
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
		auto iter = std::min_element(openSet.begin(), openSet.end(),[](Tile* a, Tile* b)
			{
				return a->f < b->f;
			});
		//  当前位置移动
		current = *iter;
		//  出开集入闭集
		openSet.erase(iter);
		current->mInOpenSet = false;
		current->mInClosedSet = true;
	} while (current != goal);
	return (current == goal) ? true : false;
}

void Grid::UpdatePathTiles(class Tile* start)
{
	//  除起始方格和结束方格外的其他方格设定状态
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
			{
				mTiles[i][j]->SetTileState(Tile::EDefault);
			}
		}
	}
	//  初始化
	Tile* t = start->mParent;
	//  路径上每一个方格状态改变
	while (t != GetEndTile())
	{
		t->SetTileState(Tile::EPath);
		t = t->mParent;
	}
}

void Grid::BuildTower()
{
	//  排除障碍方格
	if (mSelectedTile && !mSelectedTile->mBlocked)
	{
		mSelectedTile->mBlocked = true;
		if (FindPath(GetEndTile(), GetStartTile()))
		{
			Tower* t = new Tower(GetGame());
			t->SetPosition(mSelectedTile->GetPosition());
		}
		else
		{
			//  不能建塔
			mSelectedTile->mBlocked = false;
			FindPath(GetEndTile(), GetStartTile());
		}
		//  更新路径方格
		UpdatePathTiles(GetStartTile());
	}
}

void Grid::DestroyTower()
{
	//  排除障碍方格
	if (mSelectedTile && mSelectedTile->mBlocked)
	{
		mSelectedTile->mBlocked = false;
		if (FindPath(GetEndTile(), GetStartTile()))
		{
			for (auto tower : GetGame()->GetTowers())
			{
				if ((tower->GetPosition().x == mSelectedTile->GetPosition().x) && 
					(tower->GetPosition().y == mSelectedTile->GetPosition().y))
				{
					tower->SetState(State::EDead);
				}
			}
		}
		else
		{
			//  不能拆塔
			mSelectedTile->mBlocked = true;
			FindPath(GetEndTile(), GetStartTile());
		}
		//  更新路径方格
		UpdatePathTiles(GetStartTile());
	}
}

Tile* Grid::GetStartTile()
{
	//  设定开始方格
	return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
	//  设定结束方格
	return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  是否产生一个新敌人
	mNextEnemy -= deltaTime;
	if (mNextEnemy <= 0.0f)
	{
		new Enemy(GetGame());
		mNextEnemy += EnemyTime;
	}
}
