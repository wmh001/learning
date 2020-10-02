#pragma once
#include "Actor.h"

class Ship :
    public Actor
{
public:
	Ship(class Game* game);
	//  更新
	void UpdateActor(float deltaTime) override;
	void ActorInput(const struct InputState& state) override;
private:
	//  速度方向
	Vector2 mVelocityDir;
	//  角速度方向
	Vector2 mRotationDir;
	//  速度
	float mSpeed;
	//  上一次激光时间
	float mLaserCooldown;
};

