#pragma once
#include "Actor.h"
class Tower :
    public Actor
{
public:
	Tower(class Game* game);
	void UpdateActor(float deltaTime) override;
private:
	//  移动组件
	class MoveComponent* mMove;
	//  下一次进攻时间
	float mNextAttack;
	//  冷却时间
	const float AttackTime = 2.0f;
	//  进攻范围
	const float AttackRange = 100.0f;
};

