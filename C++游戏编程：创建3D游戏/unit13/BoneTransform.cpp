#include "BoneTransform.h"

Matrix4 BoneTransform::ToMatrix() const
{
	//  四元数
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	//  位置
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);
	//  相乘
	return rot * trans;
}

BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	BoneTransform retVal;
	//  生成角度球面线性插值
	retVal.mRotation = Quaternion::Slerp(a.mRotation, b.mRotation, f);
	//  生成位置球面线性插值
	retVal.mTranslation = Vector3::Lerp(a.mTranslation, b.mTranslation, f);
	//  返回插值
	return retVal;
}
