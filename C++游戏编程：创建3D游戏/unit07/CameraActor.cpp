#include "CameraActor.h"
#include "MoveComponent.h"
#include "SDL.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include "Game.h"
#include "AudioComponent.h"

CameraActor::CameraActor(Game* game)
	:Actor(game)
{
	//  �����ƶ����
	mMoveComp = new MoveComponent(this);
	//  �����������
	mAudioComp = new AudioComponent(this);
	mLastFootstep = 0.0f;
	//  ���ŽŲ���
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);
}

void CameraActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  ������ʱ��
	mLastFootstep -= deltaTime;
	//  ֹͣ���߻�ʱ�䵽�����Ų���
	if (!Math::NearZero(mMoveComp->GetForwardSpeed()) && mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.5f;
	}
	//  ��ȡλ��
	Vector3 cameraPos = GetPosition();
	//  Ŀ��
	Vector3 target = GetPosition() + GetForward() * 100.0f;
	//  ���Ϸ���
	Vector3 up = Vector3::UnitZ;
	//  ��ͼ����
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	GetGame()->GetRenderer()->SetViewMatrix(view);
	//  ����������
	GetGame()->GetAudioSystem()->SetListener(view);
}

void CameraActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	//  ���봦��
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::TwoPi;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angularSpeed += Math::TwoPi;
	}
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetAngularSpeed(angularSpeed);
}

void CameraActor::SetFootstepSurface(float value)
{
	//
	mFootstep.SetPaused(true);
	mFootstep.SetParameter("Surface", value);
}
