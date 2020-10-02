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
	//  �����������
	mMeshComp = new MeshComponent(this);
	//  ��������
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
	//  ����λ��
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));
	//  ����������
	mCameraComp = new OrbitCamera(this);
}

void OrbitActor::ActorInput(const uint8_t* keys)
{
	//  ����������ģʽ
	int x, y;
	Uint32 buttons = SDL_GetRelativeMouseState(&x, &y);
	//  �Ҽ��������
	if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		//  �趨����ٶ�
		const int maxMouseSpeed = 500;
		//  �趨�����ٶ�
		const float maxOrbitSpeed = Math::Pi * 8;
		//  ����ƫ�����ٶ�
		float yawSpeed = 0.0f;
		if (x != 0)
		{
			yawSpeed = static_cast<float>(x) / maxMouseSpeed;
			yawSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetYawSpeed(-yawSpeed);
		//  ���㸩���ٶ�
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