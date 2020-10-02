#pragma once
#include "Actor.h"

//  �ӵ�
class Bullet :
    public Actor
{
public:
	Bullet(class Game* game);
	//  ����
	void UpdateActor(float deltaTime) override;
private:
	//  Բ���
	class CircleComponent* mCircle;
	//  ���ʱ��
	float mLiveTime;
};

