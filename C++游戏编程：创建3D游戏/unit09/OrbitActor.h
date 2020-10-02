#pragma once
#include "Actor.h"

class OrbitActor :
    public Actor
{
public:
	OrbitActor(class Game* game);
	//  角色特殊输入
	void ActorInput(const uint8_t* keys) override;
	//  是否可见
	void SetVisible(bool visible);
private:
	//  相机组件
	class OrbitCamera* mCameraComp;
	//  网格组件
	class MeshComponent* mMeshComp;
};

