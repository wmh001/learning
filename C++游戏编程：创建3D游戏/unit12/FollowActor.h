#pragma once
#include "Actor.h"

class FollowActor :
    public Actor
{
public:
	FollowActor(class Game* game);
	//  角色特殊输入
	void ActorInput(const uint8_t* keys) override;
	//  是否可见
	void SetVisible(bool visible);
private:
	//  移动组件
	class MoveComponent* mMoveComp;
	//  跟拍相机组件
	class FollowCamera* mCameraComp;
	//  蒙皮网格组件
	class SkeletalMeshComponent* mMeshComp;
	//  是否移动
	bool mMoving;
};

