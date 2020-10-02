#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class CameraActor :
    public Actor
{
public:
	CameraActor(class Game* game);
	//  更新角色
	void UpdateActor(float deltaTime) override;
	//  角色特殊输入
	void ActorInput(const uint8_t* keys) override;
	//
	void SetFootstepSurface(float value);
private:
	//  移动组件
	class MoveComponent* mMoveComp;
	//  声音组件
	class AudioComponent* mAudioComp;
	//  脚步声
	SoundEvent mFootstep;
	//  上一步时间
	float mLastFootstep;
};

