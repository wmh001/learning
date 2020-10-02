#include "BoneTransform.h"

Matrix4 BoneTransform::ToMatrix() const
{
	//  ��Ԫ��
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	//  λ��
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);
	//  ���
	return rot * trans;
}

BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	BoneTransform retVal;
	//  ���ɽǶ��������Բ�ֵ
	retVal.mRotation = Quaternion::Slerp(a.mRotation, b.mRotation, f);
	//  ����λ���������Բ�ֵ
	retVal.mTranslation = Vector3::Lerp(a.mTranslation, b.mTranslation, f);
	//  ���ز�ֵ
	return retVal;
}
