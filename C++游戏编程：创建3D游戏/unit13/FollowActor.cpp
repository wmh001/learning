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
	//  创建网格组件
	mMeshComp = new SkeletalMeshComponent(this);
	//  设置网格
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/CatWarrior.gpmesh"));
	//  设置蒙皮
	mMeshComp->SetSkeleton(game->GetSkeleton("Assets/CatWarrior.gpskel"));
	//  设置动画
	mMeshComp->PlayAnimation(game->GetAnimation("Assets/CatActionIdle.gpanim"));
	//  设置位置
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));
	//  创建移动组件
	mMoveComp = new MoveComponent(this);
	//  创建相机组件
	mCameraComp = new FollowCamera(this);
	//  相机初始化
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
	//  输入处理
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
	//  移动并播放动画
	if (!mMoving && !Math::NearZero(forwardSpeed))
	{
		mMoving = true;
		mMeshComp->PlayAnimation(GetGame()->GetAnimation("Assets/CatRunSprint.gpanim"), 1.25f);
	}
	//  停止并播放动画
	else if (mMoving && Math::NearZero(forwardSpeed))
	{
		mMoving = false;
		mMeshComp->PlayAnimation(GetGame()->GetAnimation("Assets/CatActionIdle.gpanim"));
	}
	//  修改速度
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetAngularSpeed(angularSpeed);
}

void FollowActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}
