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
	//  �����ƶ����
	mMoveComp = new MoveComponent(this);
	//  �����������
	mAudioComp = new AudioComponent(this);
	//  ��ʱ
	mLastFootstep = 0.0f;
	//  ���ŽŲ���
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);
	//  ����FPS������
	mCameraComp = new FPSCamera(this);
	//  ������һ�˳�ģ��
	mFPSModel = new Actor(game);
	//  �趨����
	mFPSModel->SetScale(0.75f);
	//  �����������
	mMeshComp = new MeshComponent(mFPSModel);
	//  ��������
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Rifle.gpmesh"));
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  ������ʱ��
	mLastFootstep -= deltaTime;
	if (!Math::NearZero(mMoveComp->GetForwardSpeed()) && mLastFootstep <= 0.0f)
	{
		//  ��ͣ
		mFootstep.SetPaused(false);
		//  ����
		mFootstep.Restart();
		//  ����ʱ��
		mLastFootstep = 0.5f;
	}
	//  ���ƫ��
	const Vector3 modelOffset(Vector3(10.0f, 10.0f, -10.0f));
	//  ��ȡλ��
	Vector3 modelPos = GetPosition();
	modelPos += GetForward() * modelOffset.x;
	modelPos += GetRight() * modelOffset.y;
	modelPos.z += modelOffset.z;
	//  ����λ��
	mFPSModel->SetPosition(modelPos);
	//  ��������Ԫ��
	Quaternion q = GetRotation();
	q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCameraComp->GetPitch()));
	//  ���ýǶ�
	mFPSModel->SetRotation(q);
}

void FPSActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
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
		strafeSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += 400.0f;
	}
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);
	//  ��������
	int x, y;
	//  �������ģʽ
	SDL_GetRelativeMouseState(&x, &y);
	//  ����������ٶ�
	const int maxMouseSpeed = 500;
	//  ���������ٶ�
	const float maxAngularSpeed = Math::Pi * 8;
	//  ����ƽ����ٶ�
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		//  ������ٶ�
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	//  �޸Ľ��ٶ�
	mMoveComp->SetAngularSpeed(angularSpeed);
	//  �趨�����ٶ�
	const float maxPitchSpeed = Math::Pi * 8;
	//  ���㸩���ٶ�
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	//  �趨���ٶ�
	mCameraComp->SetPitchSpeed(pitchSpeed);
}

void FPSActor::SetFootstepSurface(float value)
{
	//  ��ͣ
	mFootstep.SetPaused(true);
	//  ����
	mFootstep.SetParameter("Surface", value);
}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}
