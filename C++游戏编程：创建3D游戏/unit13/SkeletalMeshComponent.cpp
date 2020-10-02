#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"

SkeletalMeshComponent::SkeletalMeshComponent(Actor* owner)
	: MeshComponent(owner, true)
	, mSkeleton(nullptr)
	, mAnimation(nullptr)
	, mAnimPlayRate(0)
	, mAnimTime(0)
{

}

void SkeletalMeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		//  数组世界变换矩阵
		shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
		//  设置数组调色板
		shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0], MAX_SKELETON_BONES);
		//  设置光强度
		shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
		//  创建图像
		Texture* t = mMesh->GetTexture(mTextureIndex);
		//  激活
		if (t)
		{
			t->SetActive();
		}
		//  创建顶点数组
		VertexArray* va = mMesh->GetVertexArray();
		//  激活
		va->SetActive();
		//  绘制
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void SkeletalMeshComponent::Update(float deltaTime)
{
	if (mAnimation && mSkeleton)
	{
		//  重置动画时间
		mAnimTime += deltaTime * mAnimPlayRate;
		//  如果超过持续时间，则折回动画时间
		while (mAnimTime > mAnimation->GetDuration())
		{
			mAnimTime -= mAnimation->GetDuration();
		}
		//  计算矩阵调色板
		ComputeMatrixPalette();
	}
}

float SkeletalMeshComponent::PlayAnimation(Animation* anim, float playRate)
{
	//  接收动画数据
	mAnimation = anim;
	//  定义动画时间
	mAnimTime = 0.0f;
	//  接收动画播放速率
	mAnimPlayRate = playRate;
	//  空指针处理
	if (!mAnimation) { return 0.0f; }
	//  计算矩阵调色板
	ComputeMatrixPalette();
	//  返回动画持续时间
	return mAnimation->GetDuration();
}

void SkeletalMeshComponent::ComputeMatrixPalette()
{
	//  获取全局反向绑定姿势矩阵容器
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	//  定义当前姿势容器
	std::vector<Matrix4> currentPoses;
	//  计算每个骨骼全局姿势矩阵
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);
	//  为每个骨骼设置调色板
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		// 全局反向绑定姿势矩阵乘以当前姿势矩阵
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
