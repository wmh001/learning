#pragma once
#include "CameraComponent.h"

class FPSCamera :
    public CameraComponent
{
public:
	FPSCamera(class Actor* owner);
	//  更新
	void Update(float deltaTime) override;
	//  访问与修改参数
	float GetPitch() const { return mPitch; }
	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetMaxPitch() const { return mMaxPitch; }
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetMaxPitch(float pitch) { mMaxPitch = pitch; }
private:
	//  俯仰方向上的角速度
	float mPitchSpeed;
	//  最大俯仰角度
	float mMaxPitch;
	//  当前俯仰
	float mPitch;
};

