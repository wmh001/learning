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
	//  �����������
	mBoxComp = new BoxComponent(this);
	//  ������Գư�Χ��
	AABB myBox(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
	//  ���÷���
	mBoxComp->SetObjectBox(myBox);
	//  ��ֹ��ת
	mBoxComp->SetShouldRotate(false);
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  ��ǽ��ײ
	FixCollisions();
	//  ������ʱ��
	mLastFootstep -= deltaTime;
	if ((!Math::NearZero(mMoveComp->GetForwardSpeed()) || !Math::NearZero(mMoveComp->GetStrafeSpeed())) && mLastFootstep <= 0.0f)
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

void FPSActor::Shoot()
{
	//  ��ȡ��ʼ��
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = GetGame()->GetRenderer()->Unproject(screenPoint);
	//  ��ȡ��ֹ��
	screenPoint.z = 0.9f;
	Vector3 end = GetGame()->GetRenderer()->Unproject(screenPoint);
	//  ��ȡ����
	Vector3 dir = end - start;
	dir.Normalize();
	//  �����ӵ�
	BallActor* ball = new BallActor(GetGame());
	//  �������
	ball->SetPlayer(this);
	//  ����λ��
	ball->SetPosition(start + dir * 20.0f);
	//  ���÷���
	ball->RotateToNewForward(dir);
	//  ��������
	mAudioComp->PlayEvent("event:/Shot");
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

void FPSActor::FixCollisions()
{
	//  ��������任����
	ComputeWorldTransform();
	//  ��ȡ���������µ�AABB��
	const AABB& playerBox = mBoxComp->GetWorldBox();
	//  ��ȡλ��
	Vector3 pos = GetPosition();
	//  ��ȡǽ��ɫ����
	auto& planes = GetGame()->GetPlanes();
	for (auto pa : planes)
	{
		//  ��ȡAABB��
		const AABB& planeBox = pa->GetBox()->GetWorldBox();
		//  �Ƿ��ཻ
		if (Intersect(playerBox, planeBox))
		{
			//  ������С���
			float dx1 = planeBox.mMax.x - playerBox.mMin.x;
			float dx2 = planeBox.mMin.x - playerBox.mMax.x;
			float dy1 = planeBox.mMax.y - playerBox.mMin.y;
			float dy2 = planeBox.mMin.y - playerBox.mMax.y;
			float dz1 = planeBox.mMax.z - playerBox.mMin.z;
			float dz2 = planeBox.mMin.z - playerBox.mMax.z;
			float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
			float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
			float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;
			//  ����λ��
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
			//  ��������任����
			mBoxComp->OnUpdateWorldTransform();
		}
	}
}
