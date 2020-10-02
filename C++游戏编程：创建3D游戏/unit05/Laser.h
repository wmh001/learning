#pragma once
#include "Actor.h"
class Laser :
    public Actor
{
public:
	Laser(class Game* game);
	//  ����
	void UpdateActor(float deltaTime) override;
private:
	//  ��Χ
	class CircleComponent* mCircle;
	//  ���ʱ��
	float mDeathTimer;
};

