#pragma once
#include "Actor.h"

class SplineActor :
    public Actor
{
public:
	SplineActor(class Game* game);
	//  计算特殊输入
	void ActorInput(const uint8_t* keys) override;
	//  重置曲线
	void RestartSpline();
private:
	//  相机组件
	class SplineCamera* mCameraComp;
};

