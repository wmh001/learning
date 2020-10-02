#pragma once
#include "Actor.h"

//  棋盘
class Grid :
    public Actor
{
public:
	Grid(class Game* game);
	//  处理鼠标点击
	void ProcessClick(int x, int y);
	//  使用A*搜索寻路
	bool FindPath(class Tile* start, class Tile* goal);
	//  创建塔
	void BuildTower();
	//  拆塔
	void DestroyTower();
	//  访问开始方格
	class Tile* GetStartTile();
	//  访问结束方格
	class Tile* GetEndTile();
	//  更新角色
	void UpdateActor(float deltaTime) override;
private:
	//  选择方格
	void SelectTile(size_t row, size_t col);
	//  更新路径方格
	void UpdatePathTiles(class Tile* start);
	//  当前选择的方格
	class Tile* mSelectedTile;
	//  每个方格的位置
	std::vector<std::vector<class Tile*>> mTiles;
	//  下一个敌人产生的时间
	float mNextEnemy;
	//  棋盘的行数列数
	const size_t NumRows = 7;
	const size_t NumCols = 16;
	//  右上角的起始位置
	const float StartY = 192.0f;
	//  方格的边长
	const float TileSize = 64.0f;
	//  产生敌人的时间间隔
	const float EnemyTime = 1.5f;
};

