#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class FPSActor :
    public Actor
{
public:
	FPSActor(class Game* game);
	//  ���½�ɫ
	void UpdateActor(float deltaTime) override;
	//  ��ɫ��������
	void ActorInput(const uint8_t* keys) override;
	//  ����
	void Shoot();
	//  ����·�����
	void SetFootstepSurface(float value);
	//  �Ƿ�ɼ�
	void SetVisible(bool visible);
	//  ��ǽ��ײ
	void FixCollisions();
private:
	//  �ƶ����
	class MoveComponent* mMoveComp;
	//  �������
	class AudioComponent* mAudioComp;
	//  �������
	class MeshComponent* mMeshComp;
	//  FPS������
	class FPSCamera* mCameraComp;
	//  �������
	class BoxComponent* mBoxComp;
	//  ��ǹ
	class Actor* mFPSModel;
	//  �Ų���
	SoundEvent mFootstep;
	//  ��һ��ʱ��
	float mLastFootstep;
};

