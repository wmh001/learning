#include "FPSActor.h"
#include "MoveComponent.h"
#include "SDL.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include "Game.h"
#include "AudioComponent.h"
#include "FPSCamera.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "BallActor.h"
#include "BoxComponent.h"
#include "PlaneActor.h"

FPSActor::FPSActor(Game* game)
	: Actor(game)
{
	//  创建移动组件
	mMoveComp = new MoveComponent(this);
	//  创建声音组件
	mAudioComp = new AudioComponent(this);
	//  计时
	mLastFootstep = 0.0f;
	//  播放脚步声
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);
	//  创建FPS相机组件
	mCameraComp = new FPSCamera(this);
	//  创建第一人称模型
	mFPSModel = new Actor(game);
	//  设定比例
	mFPSModel->SetScale(0.75f);
	//  创建网格组件
	mMeshComp = new MeshComponent(mFPSModel);
	//  设置网格
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Rifle.gpmesh"));
	//  创建方盒组件
	mBoxComp = new BoxComponent(this);
	//  定义轴对称包围框
	AABB myBox(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
	//  设置方盒
	mBoxComp->SetObjectBox(myBox);
	//  禁止旋转
	mBoxComp->SetShouldRotate(false);
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  人墙碰撞
	FixCollisions();
	//  计算新时间
	mLastFootstep -= deltaTime;
	if ((!Math::NearZero(mMoveComp->GetForwardSpeed()) || !Math::NearZero(mMoveComp->GetStrafeSpeed())) && mLastFootstep <= 0.0f)
	{
		//  暂停
		mFootstep.SetPaused(false);
		//  重启
		mFootstep.Restart();
		//  重置时间
		mLastFootstep = 0.5f;
	}
	//  相对偏移
	const Vector3 modelOffset(Vector3(10.0f, 10.0f, -10.0f));
	//  获取位置
	Vector3 modelPos = GetPosition();
	modelPos += GetForward() * modelOffset.x;
	modelPos += GetRight() * modelOffset.y;
	modelPos.z += modelOffset.z;
	//  设置位置
	mFPSModel->SetPosition(modelPos);
	//  计算新四元数
	Quaternion q = GetRotation();
	q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCameraComp->GetPitch()));
	//  设置角度
	mFPSModel->SetRotation(q);
}

void FPSActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
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
		strafeSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += 400.0f;
	}
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);
	//  定义坐标
	int x, y;
	//  启用相对模式
	SDL_GetRelativeMouseState(&x, &y);
	//  设置最大线速度
	const int maxMouseSpeed = 500;
	//  设置最大角速度
	const float maxAngularSpeed = Math::Pi * 8;
	//  计算平面角速度
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		//  计算角速度
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	//  修改角速度
	mMoveComp->SetAngularSpeed(angularSpeed);
	//  设定最大角速度
	const float maxPitchSpeed = Math::Pi * 8;
	//  计算俯仰速度
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	//  设定角速度
	mCameraComp->SetPitchSpeed(pitchSpeed);
}

void FPSActor::Shoot()
{
	//  获取起始点
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = GetGame()->GetRenderer()->Unproject(screenPoint);
	//  获取终止点
	screenPoint.z = 0.9f;
	Vector3 end = GetGame()->GetRenderer()->Unproject(screenPoint);
	//  获取方向
	Vector3 dir = end - start;
	dir.Normalize();
	//  创建子弹
	BallActor* ball = new BallActor(GetGame());
	//  设置玩家
	ball->SetPlayer(this);
	//  设置位置
	ball->SetPosition(start + dir * 20.0f);
	//  设置方向
	ball->RotateToNewForward(dir);
	//  设置声音
	mAudioComp->PlayEvent("event:/Shot");
}

void FPSActor::SetFootstepSurface(float value)
{
	//  暂停
	mFootstep.SetPaused(true);
	//  重置
	mFootstep.SetParameter("Surface", value);
}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}

void FPSActor::FixCollisions()
{
	//  计算世界变换矩阵
	ComputeWorldTransform();
	//  获取世界坐标下的AABB框
	const AABB& playerBox = mBoxComp->GetWorldBox();
	//  获取位置
	Vector3 pos = GetPosition();
	//  获取墙角色容器
	auto& planes = GetGame()->GetPlanes();
	for (auto pa : planes)
	{
		//  获取AABB框
		const AABB& planeBox = pa->GetBox()->GetWorldBox();
		//  是否相交
		if (Intersect(playerBox, planeBox))
		{
			//  计算最小相差
			float dx1 = planeBox.mMax.x - playerBox.mMin.x;
			float dx2 = planeBox.mMin.x - playerBox.mMax.x;
			float dy1 = planeBox.mMax.y - playerBox.mMin.y;
			float dy2 = planeBox.mMin.y - playerBox.mMax.y;
			float dz1 = planeBox.mMax.z - playerBox.mMin.z;
			float dz2 = planeBox.mMin.z - playerBox.mMax.z;
			float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
			float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
			float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;
			//  更新位置
			if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
			{
				pos.x += dx;
			}
			else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
			{
				pos.y += dy;
			}
			else
			{
				pos.z += dz;
			}
			SetPosition(pos);
			//  计算世界变换矩阵
			mBoxComp->OnUpdateWorldTransform();
		}
	}
}
