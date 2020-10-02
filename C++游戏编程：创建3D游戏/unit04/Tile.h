#pragma once
#include "Actor.h"

class Tile :
    public Actor
{
public:
	//  棋盘
	friend class Grid;
	//  方格状态
	enum TileState
	{
		//  默认
		EDefault,
		//  路径
		EPath,
		//  起始
		EStart,
		//  结束
		EBase
	};
	//  构造
	Tile(class Game* game);
	//  修改与访问
	void SetTileState(TileState state);
	TileState GetTileState() const { return mTileState; }
	//  鼠标改选
	void ToggleSelect();
	//  得到下一个节点
	const Tile* GetParent() const { return mParent; }
private:
	//  相邻点
	std::vector<Tile*> mAdjacent;
	//  父节点
	Tile* mParent;
	//  f(x)
	float f;
	//  实际路径成本
	float g;
	//  heuristic距离
	float h;
	//  是否在开集中
	bool mInOpenSet;
	//  是否在闭集中
	bool mInClosedSet;
	//  是否为障碍
	bool mBlocked;
	//  更新图像
	void UpdateTexture();
	//  精灵组件
	class SpriteComponent* mSprite;
	//  状态
	TileState mTileState;
	//  是否被选择
	bool mSelected;
};

