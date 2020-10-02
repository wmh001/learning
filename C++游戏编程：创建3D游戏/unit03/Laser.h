#pragma once
#include "Actor.h"
class Laser :
    public Actor
{
public:
	Laser(class Game* game);
	//  更新
	void UpdateActor(float deltaTime) override;
private:
	//  范围
	class CircleComponent* mCircle;
	//  存活时间
	float mDeathTimer;
};

