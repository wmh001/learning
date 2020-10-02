#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class CameraActor :
    public Actor
{
public:
	CameraActor(class Game* game);
	//  ���½�ɫ
	void UpdateActor(float deltaTime) override;
	//  ��ɫ��������
	void ActorInput(const uint8_t* keys) override;
	//
	void SetFootstepSurface(float value);
private:
	//  �ƶ����
	class MoveComponent* mMoveComp;
	//  �������
	class AudioComponent* mAudioComp;
	//  �Ų���
	SoundEvent mFootstep;
	//  ��һ��ʱ��
	float mLastFootstep;
};

