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
	//  7��16��
	//  ����ռ�
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}
	//  ��������
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
		}
	}
	//  �趨��ʼ����״̬
	GetStartTile()->SetTileState(Tile::EStart);
	//  �趨��������״̬
	GetEndTile()->SetTileState(Tile::EBase);
	//  ������
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
	//  Ѱ�ҳ�ʼ·��
	FindPath(GetEndTile(), GetStartTile());
	//  ����·������
	UpdatePathTiles(GetStartTile());
	//  ��ʼ�����˵���ʱ��
	mNextEnemy = EnemyTime;
}

void Grid::SelectTile(size_t row, size_t col)
{
	//  ȷ��ѡ��Ϸ�
	Tile::TileState tstate = mTiles[row][col]->GetTileState();
	if (tstate != Tile::EStart && tstate != Tile::EBase)
	{
		//  ȡ����һ��ѡ��
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}
		//  �趨�µı�ѡ����
		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();
	}
}

void Grid::ProcessClick(int x, int y)
{
	y -= static_cast<int>(StartY - TileSize / 2);
	if (y >= 0)
	{
		//  ��������
		x /= static_cast<int>(TileSize);
		y /= static_cast<int>(TileSize);
		if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
		{
			SelectTile(y, x);
		}
	}
}

//  ʵ��A*Ѱ·
bool Grid::FindPath(Tile* start, Tile* goal)
{
	//  ��ʼ��ÿ��
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j]->g = 0.0f;
			mTiles[i][j]->mInOpenSet = false;
			mTiles[i][j]->mInClosedSet = false;
		}
	}
	//  ���忪��
	std::vector<Tile*> openSet;
	//  ��ǰ�ڵ�
	Tile* current = start;
	//  ����ռ�
	current->mInClosedSet = true;
	//  ��ѭ��
	do
	{
		//  ����ڵ㵽����
		for (Tile* neighbor : current->mAdjacent)
		{
			//  �Ƿ�Ϊ�ϰ�
			if (neighbor->mBlocked)
			{
				continue;
			}
			//  ���ڱռ�ʱ��ʼ����
			if (!neighbor->mInClosedSet)
			{
				//  �ڵ����
				if (!neighbor->mInOpenSet)
				{
					//  ���ڿ����У���ǰ�ڵ�Ϊ���ڵ�
					neighbor->mParent = current;
					//  ����heuristic����
					neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
					//  ʵ��·���ɱ�Ϊ���ڵ�ʵ��·���ɱ��ӹ��ߵĳɱ�
					neighbor->g = current->g + TileSize;
					//  ����f(x)
					neighbor->f = neighbor->g + neighbor->h;
                    //  ���뿪��
					openSet.emplace_back(neighbor);
					neighbor->mInOpenSet = true;
				}
				else
				{
					//  �����ǰ�ڵ��ɸ��ڵ㣬�����µĳɱ�
					float newG = current->g + TileSize;
					if (newG < neighbor->g)
					{
						//  �ڽڵ����Ա仯
						neighbor->mParent = current;
						neighbor->g = newG;
						//  ����f(x)
						neighbor->f = neighbor->g + neighbor->h;
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
		auto iter = std::min_element(openSet.begin(), openSet.end(),[](Tile* a, Tile* b)
			{
				return a->f < b->f;
			});
		//  ��ǰλ���ƶ�
		current = *iter;
		//  ��������ռ�
		openSet.erase(iter);
		current->mInOpenSet = false;
		current->mInClosedSet = true;
	} while (current != goal);
	return (current == goal) ? true : false;
}

void Grid::UpdatePathTiles(class Tile* start)
{
	//  ����ʼ����ͽ�������������������趨״̬
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
	//  ��ʼ��
	Tile* t = start->mParent;
	//  ·����ÿһ������״̬�ı�
	while (t != GetEndTile())
	{
		t->SetTileState(Tile::EPath);
		t = t->mParent;
	}
}

void Grid::BuildTower()
{
	//  �ų��ϰ�����
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
			//  ���ܽ���
			mSelectedTile->mBlocked = false;
			FindPath(GetEndTile(), GetStartTile());
		}
		//  ����·������
		UpdatePathTiles(GetStartTile());
	}
}

void Grid::DestroyTower()
{
	//  �ų��ϰ�����
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
			//  ���ܲ���
			mSelectedTile->mBlocked = true;
			FindPath(GetEndTile(), GetStartTile());
		}
		//  ����·������
		UpdatePathTiles(GetStartTile());
	}
}

Tile* Grid::GetStartTile()
{
	//  �趨��ʼ����
	return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
	//  �趨��������
	return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  �Ƿ����һ���µ���
	mNextEnemy -= deltaTime;
	if (mNextEnemy <= 0.0f)
	{
		new Enemy(GetGame());
		mNextEnemy += EnemyTime;
	}
}
