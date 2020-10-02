#pragma once
#include "Actor.h"

//  子弹
class Bullet :
    public Actor
{
public:
	Bullet(class Game* game);
	//  更新
	void UpdateActor(float deltaTime) override;
private:
	//  圆组件
	class CircleComponent* mCircle;
	//  存活时间
	float mLiveTime;
};

