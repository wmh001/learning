#pragma once
#include "CameraComponent.h"

class FollowCamera :
    public CameraComponent
{
public:
	FollowCamera(class Actor* owner);
	//  ����
	void Update(float deltaTime) override;
	//  ��ʼ��
	void SnapToIdeal();
	//  �޸Ĳ���
	void SetHorzDist(float dist) { mHorzDist = dist; }
	void SetVertDist(float dist) { mVertDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	void SetSpringConstant(float spring) { mSpringConstant = spring; }
private:
	//  �������λ��
	Vector3 ComputeCameraPos() const;
	//  ���ʵ��λ��
	Vector3 mActualPos;
	//  ��������ٶ�
	Vector3 mVelocity;
	//  ˮƽ����
	float mHorzDist;
	//  ��ֱ����
	float mVertDist;
	//  Ŀ�����
	float mTargetDist;
	//  ���ɸ߶�
	float mSpringConstant;
};

