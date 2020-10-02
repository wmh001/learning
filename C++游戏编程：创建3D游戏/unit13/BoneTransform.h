#pragma once
#include "Math.h"

//  ����λ��
class BoneTransform
{
public:
	//  ��Ԫ��
	Quaternion mRotation;
	//  λ��
	Vector3 mTranslation;
	//  ת��Ϊ����
	Matrix4 ToMatrix() const;
	//  ��ֵ����
	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);
};

