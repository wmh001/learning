#pragma once
#include "MoveComponent.h"
#include "Math.h"

class NavComponent :
    public MoveComponent
{
public:
	//  更小的更新顺序使其在大多数组件之前更新
	NavComponent(class Actor* owner, int updateOrder = 10);
	//  更新
	void Update(float deltaTime) override;
	//  旋转
	void StartPath(const class Tile* start);
	void TurnTo(const Vector2& pos);
private:
	//  下一个点
	const class Tile* mNextNode;
};

