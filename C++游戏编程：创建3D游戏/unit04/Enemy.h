#pragma once
#include "Actor.h"

//  ����
class Enemy :
    public Actor
{
public:
	Enemy(class Game* game);
	~Enemy();
	void UpdateActor(float deltaTime) override;
	//  ����Բ���
	class CircleComponent* GetCircle() { return mCircle; }
private:
	//  ����Բ���
	class CircleComponent* mCircle;
};

