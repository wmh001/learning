#pragma once
#include "Actor.h"

class Asteroid :
    public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();
	//  访问圆组件
	class CircleComponent* GetCircle() { return mCircle; }
private:
	//  圆组件
	class CircleComponent* mCircle;
};

