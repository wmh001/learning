#pragma once
#include "CameraComponent.h"

class FollowCamera :
    public CameraComponent
{
public:
	FollowCamera(class Actor* owner);
	//  更新
	void Update(float deltaTime) override;
	//  初始化
	void SnapToIdeal();
	//  修改参数
	void SetHorzDist(float dist) { mHorzDist = dist; }
	void SetVertDist(float dist) { mVertDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	void SetSpringConstant(float spring) { mSpringConstant = spring; }
private:
	//  计算相机位置
	Vector3 ComputeCameraPos() const;
	//  相机实际位置
	Vector3 mActualPos;
	//  跟拍相机速度
	Vector3 mVelocity;
	//  水平距离
	float mHorzDist;
	//  垂直距离
	float mVertDist;
	//  目标距离
	float mTargetDist;
	//  弹簧高度
	float mSpringConstant;
};

