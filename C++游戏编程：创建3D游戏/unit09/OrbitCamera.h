#pragma once
#include "CameraComponent.h"

class OrbitCamera :
    public CameraComponent
{
public:
	OrbitCamera(class Actor* owner);
	//  更新
	void Update(float deltaTime) override;
	//  访问/修改俯仰/偏航速度
	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetYawSpeed() const { return mYawSpeed; }
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
private:
	//  相对目标的偏移量
	Vector3 mOffset;
	//  上方向量
	Vector3 mUp;
	//  俯仰速度
	float mPitchSpeed;
	//  偏航速度
	float mYawSpeed;
};

