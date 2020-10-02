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

FPSActor::FPSActor(Game* game)
	:Actor(game)
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
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  计算新时间
	mLastFootstep -= deltaTime;
	if (!Math::NearZero(mMoveComp->GetForwardSpeed()) && mLastFootstep <= 0.0f)
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
