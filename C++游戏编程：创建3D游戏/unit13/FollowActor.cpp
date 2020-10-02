#include "FollowActor.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "FollowCamera.h"
#include "MoveComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "MirrorCamera.h"

FollowActor::FollowActor(Game* game)
	: Actor(game)
	, mMoving(false)
{
	//  �����������
	mMeshComp = new SkeletalMeshComponent(this);
	//  ��������
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/CatWarrior.gpmesh"));
	//  ������Ƥ
	mMeshComp->SetSkeleton(game->GetSkeleton("Assets/CatWarrior.gpskel"));
	//  ���ö���
	mMeshComp->PlayAnimation(game->GetAnimation("Assets/CatActionIdle.gpanim"));
	//  ����λ��
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));
	//  �����ƶ����
	mMoveComp = new MoveComponent(this);
	//  ����������
	mCameraComp = new FollowCamera(this);
	//  �����ʼ��
	mCameraComp->SnapToIdeal();
	//
	MirrorCamera* mirror = new MirrorCamera(this);
	//
	mirror->SnapToIdeal();
}

void FollowActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	//  ���봦��
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::Pi;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angularSpeed += Math::Pi;
	}
	//  �ƶ������Ŷ���
	if (!mMoving && !Math::NearZero(forwardSpeed))
	{
		mMoving = true;
		mMeshComp->PlayAnimation(GetGame()->GetAnimation("Assets/CatRunSprint.gpanim"), 1.25f);
	}
	//  ֹͣ�����Ŷ���
	else if (mMoving && Math::NearZero(forwardSpeed))
	{
		mMoving = false;
		mMeshComp->PlayAnimation(GetGame()->GetAnimation("Assets/CatActionIdle.gpanim"));
	}
	//  �޸��ٶ�
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetAngularSpeed(angularSpeed);
}

void FollowActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}
