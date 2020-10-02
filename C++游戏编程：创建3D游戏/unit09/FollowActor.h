#pragma once
#include "Actor.h"

class FollowActor :
    public Actor
{
public:
	FollowActor(class Game* game);
	//  ��ɫ��������
	void ActorInput(const uint8_t* keys) override;
	//  �Ƿ�ɼ�
	void SetVisible(bool visible);
private:
	//  �ƶ����
	class MoveComponent* mMoveComp;
	//  ����������
	class FollowCamera* mCameraComp;
	//  �������
	class MeshComponent* mMeshComp;
};

