#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"

class SkeletalMeshComponent :
    public MeshComponent
{
public:
	SkeletalMeshComponent(class Actor* owner);
	//  绘制骨骼网格
	void Draw(class Shader* shader) override;
	//  更新
	void Update(float deltaTime) override;
	//  修改骨骼
	void SetSkeleton(class Skeleton* sk) { mSkeleton = sk; }
	//  处理动画
	float PlayAnimation(class Animation* anim, float playRate = 1.0f);
protected:
	//  计算矩阵调色板
	void ComputeMatrixPalette();
	//  矩阵调色板
	MatrixPalette mPalette;
	//  骨骼
	const class Skeleton* mSkeleton;
	//  动画数据
	const class Animation* mAnimation;
	//  动画播放速率
	float mAnimPlayRate;
	//  动画中的当前时间
	float mAnimTime;
};

