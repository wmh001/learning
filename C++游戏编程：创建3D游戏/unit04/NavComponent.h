#pragma once
#include "MoveComponent.h"
#include "Math.h"

class NavComponent :
    public MoveComponent
{
public:
	//  ��С�ĸ���˳��ʹ���ڴ�������֮ǰ����
	NavComponent(class Actor* owner, int updateOrder = 10);
	//  ����
	void Update(float deltaTime) override;
	//  ��ת
	void StartPath(const class Tile* start);
	void TurnTo(const Vector2& pos);
private:
	//  ��һ����
	const class Tile* mNextNode;
};

