#include "OrbitActor.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "OrbitCamera.h"
#include "MoveComponent.h"

OrbitActor::OrbitActor(Game* game)
	:Actor(game)
{
	//  创建网格组件
	mMeshComp = new MeshComponent(this);
	//  设置网格
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
	//  设置位置
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));
	//  创建相机组件
	mCameraComp = new OrbitCamera(this);
}

void OrbitActor::ActorInput(const uint8_t* keys)
{
	//  启用鼠标相对模式
	int x, y;
	Uint32 buttons = SDL_GetRelativeMouseState(&x, &y);
	//  右键点击处理
	if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		//  设定最大速度
		const int maxMouseSpeed = 500;
		//  设定最大角速度
		const float maxOrbitSpeed = Math::Pi * 8;
		//  计算偏航设速度
		float yawSpeed = 0.0f;
		if (x != 0)
		{
			yawSpeed = static_cast<float>(x) / maxMouseSpeed;
			yawSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetYawSpeed(-yawSpeed);
		//  计算俯仰速度
		float pitchSpeed = 0.0f;
		if (y != 0)
		{
			pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetPitchSpeed(pitchSpeed);
	}
}

void OrbitActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}