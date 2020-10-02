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
		//  ��������任����
		shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
		//  ���������ɫ��
		shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0], MAX_SKELETON_BONES);
		//  ���ù�ǿ��
		shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
		//  ����ͼ��
		Texture* t = mMesh->GetTexture(mTextureIndex);
		//  ����
		if (t)
		{
			t->SetActive();
		}
		//  ������������
		VertexArray* va = mMesh->GetVertexArray();
		//  ����
		va->SetActive();
		//  ����
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void SkeletalMeshComponent::Update(float deltaTime)
{
	if (mAnimation && mSkeleton)
	{
		//  ���ö���ʱ��
		mAnimTime += deltaTime * mAnimPlayRate;
		//  �����������ʱ�䣬���ۻض���ʱ��
		while (mAnimTime > mAnimation->GetDuration())
		{
			mAnimTime -= mAnimation->GetDuration();
		}
		//  ��������ɫ��
		ComputeMatrixPalette();
	}
}

float SkeletalMeshComponent::PlayAnimation(Animation* anim, float playRate)
{
	//  ���ն�������
	mAnimation = anim;
	//  ���嶯��ʱ��
	mAnimTime = 0.0f;
	//  ���ն�����������
	mAnimPlayRate = playRate;
	//  ��ָ�봦��
	if (!mAnimation) { return 0.0f; }
	//  ��������ɫ��
	ComputeMatrixPalette();
	//  ���ض�������ʱ��
	return mAnimation->GetDuration();
}

void SkeletalMeshComponent::ComputeMatrixPalette()
{
	//  ��ȡȫ�ַ�������ƾ�������
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	//  ���嵱ǰ��������
	std::vector<Matrix4> currentPoses;
	//  ����ÿ������ȫ�����ƾ���
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);
	//  Ϊÿ���������õ�ɫ��
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		// ȫ�ַ�������ƾ�����Ե�ǰ���ƾ���
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
