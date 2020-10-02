#pragma once
#include "Actor.h"
class Tower :
    public Actor
{
public:
	Tower(class Game* game);
	void UpdateActor(float deltaTime) override;
private:
	//  �ƶ����
	class MoveComponent* mMove;
	//  ��һ�ν���ʱ��
	float mNextAttack;
	//  ��ȴʱ��
	const float AttackTime = 2.0f;
	//  ������Χ
	const float AttackRange = 100.0f;
};

