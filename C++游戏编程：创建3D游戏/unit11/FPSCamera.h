#pragma once
#include "CameraComponent.h"

class FPSCamera :
    public CameraComponent
{
public:
	FPSCamera(class Actor* owner);
	//  ����
	void Update(float deltaTime) override;
	//  �������޸Ĳ���
	float GetPitch() const { return mPitch; }
	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetMaxPitch() const { return mMaxPitch; }
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetMaxPitch(float pitch) { mMaxPitch = pitch; }
private:
	//  ���������ϵĽ��ٶ�
	float mPitchSpeed;
	//  ������Ƕ�
	float mMaxPitch;
	//  ��ǰ����
	float mPitch;
};

