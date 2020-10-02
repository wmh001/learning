#pragma once
#include "Math.h"

//  骨骼位置
class BoneTransform
{
public:
	//  四元数
	Quaternion mRotation;
	//  位置
	Vector3 mTranslation;
	//  转换为矩阵
	Matrix4 ToMatrix() const;
	//  插值函数
	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);
};

