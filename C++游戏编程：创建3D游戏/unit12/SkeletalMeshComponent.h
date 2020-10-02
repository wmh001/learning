#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"

class SkeletalMeshComponent :
    public MeshComponent
{
public:
	SkeletalMeshComponent(class Actor* owner);
	//  ���ƹ�������
	void Draw(class Shader* shader) override;
	//  ����
	void Update(float deltaTime) override;
	//  �޸Ĺ���
	void SetSkeleton(class Skeleton* sk) { mSkeleton = sk; }
	//  ������
	float PlayAnimation(class Animation* anim, float playRate = 1.0f);
protected:
	//  ��������ɫ��
	void ComputeMatrixPalette();
	//  �����ɫ��
	MatrixPalette mPalette;
	//  ����
	const class Skeleton* mSkeleton;
	//  ��������
	const class Animation* mAnimation;
	//  ������������
	float mAnimPlayRate;
	//  �����еĵ�ǰʱ��
	float mAnimTime;
};

