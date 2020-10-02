#pragma once
#include "CameraComponent.h"

class OrbitCamera :
    public CameraComponent
{
public:
	OrbitCamera(class Actor* owner);
	//  ����
	void Update(float deltaTime) override;
	//  ����/�޸ĸ���/ƫ���ٶ�
	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetYawSpeed() const { return mYawSpeed; }
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
private:
	//  ���Ŀ���ƫ����
	Vector3 mOffset;
	//  �Ϸ�����
	Vector3 mUp;
	//  �����ٶ�
	float mPitchSpeed;
	//  ƫ���ٶ�
	float mYawSpeed;
};

