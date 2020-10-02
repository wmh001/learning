#pragma once
#include "Actor.h"

//  敌人
class Enemy :
    public Actor
{
public:
	Enemy(class Game* game);
	~Enemy();
	void UpdateActor(float deltaTime) override;
	//  访问圆组件
	class CircleComponent* GetCircle() { return mCircle; }
private:
	//  创建圆组件
	class CircleComponent* mCircle;
};

