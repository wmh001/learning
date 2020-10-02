#pragma once
#include "Actor.h"

class BallActor :
    public Actor
{
public:
	BallActor(class Game* game);
	//  ���½�ɫ
	void UpdateActor(float deltaTime) override;
	//  �޸����
	void SetPlayer(Actor* player);
	//  �а�
	void HitTarget();
private:
	//  �������
	class AudioComponent* mAudioComp;
	//  ���ƶ����
	class BallMove* mMyMove;
	//  ����ʱ��
	float mLifeSpan;
};

