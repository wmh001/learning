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
	//  创建网格组件
	MeshComponent* mc = new MeshComponent(this);
	//  创建网格
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh");
	//  设置网格
	mc->SetMesh(mesh);
	//  创建球移动组件
	mMyMove = new BallMove(this);
	//  设置速度
	mMyMove->SetForwardSpeed(1500.0f);
	//  创建声音组件
	mAudioComp = new AudioComponent(this);
}

void BallActor::UpdateActor(float deltaTime)
{
	//  角色更新
	Actor::UpdateActor(deltaTime);
	//  时间更新
	mLifeSpan -= deltaTime;
	//  死亡
	if (mLifeSpan < 0.0f)
	{
		SetState(EDead);
	}
}

void BallActor::SetPlayer(Actor* player)
{
	//  设置玩家
	mMyMove->SetPlayer(player);
}

void BallActor::HitTarget()
{
	//  中靶声音
	mAudioComp->PlayEvent("event:/Ding");
}
