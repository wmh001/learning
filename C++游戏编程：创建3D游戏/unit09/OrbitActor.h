#pragma once
#include "Actor.h"

class OrbitActor :
    public Actor
{
public:
	OrbitActor(class Game* game);
	//  ��ɫ��������
	void ActorInput(const uint8_t* keys) override;
	//  �Ƿ�ɼ�
	void SetVisible(bool visible);
private:
	//  ������
	class OrbitCamera* mCameraComp;
	//  �������
	class MeshComponent* mMeshComp;
};

