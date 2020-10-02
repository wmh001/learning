#include "BallActor.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "BallMove.h"
#include "AudioComponent.h"

BallActor::BallActor(Game* game)
	: Actor(game)
	, mLifeSpan(3.0f)
{
	//SetScale(10.0f);
	//  �����������
	MeshComponent* mc = new MeshComponent(this);
	//  ��������
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh");
	//  ��������
	mc->SetMesh(mesh);
	//  �������ƶ����
	mMyMove = new BallMove(this);
	//  �����ٶ�
	mMyMove->SetForwardSpeed(1500.0f);
	//  �����������
	mAudioComp = new AudioComponent(this);
}

void BallActor::UpdateActor(float deltaTime)
{
	//  ��ɫ����
	Actor::UpdateActor(deltaTime);
	//  ʱ�����
	mLifeSpan -= deltaTime;
	//  ����
	if (mLifeSpan < 0.0f)
	{
		SetState(EDead);
	}
}

void BallActor::SetPlayer(Actor* player)
{
	//  �������
	mMyMove->SetPlayer(player);
}

void BallActor::HitTarget()
{
	//  �а�����
	mAudioComp->PlayEvent("event:/Ding");
}
