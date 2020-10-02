#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class FPSActor :
    public Actor
{
public:
	FPSActor(class Game* game);
	//  更新角色
	void UpdateActor(float deltaTime) override;
	//  角色特殊输入
	void ActorInput(const uint8_t* keys) override;
	//  反射
	void Shoot();
	//  设置路面材质
	void SetFootstepSurface(float value);
	//  是否可见
	void SetVisible(bool visible);
	//  人墙碰撞
	void FixCollisions();
private:
	//  移动组件
	class MoveComponent* mMoveComp;
	//  声音组件
	class AudioComponent* mAudioComp;
	//  网格组件
	class MeshComponent* mMeshComp;
	//  FPS相机组件
	class FPSCamera* mCameraComp;
	//  方盒组件
	class BoxComponent* mBoxComp;
	//  步枪
	class Actor* mFPSModel;
	//  脚步声
	SoundEvent mFootstep;
	//  上一步时间
	float mLastFootstep;
};

