#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

Enemy::Enemy(class Game* game)
	:Actor(game)
{
	//  加入敌人容器
	game->GetEnemies().emplace_back(this);
	//  创建图像组件
	SpriteComponent* sc = new SpriteComponent(this);
	//  绘制图像
	sc->SetTexture(game->GetTexture("Assets/Airplane.png"));
	//  设定起始位置
	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
	//  创建寻路组件
	NavComponent* nc = new NavComponent(this);
	//  设定线速度
	nc->SetForwardSpeed(150.0f);
	//  设定起始方格
	nc->StartPath(GetGame()->GetGrid()->GetStartTile());
	//  创建圆组件
	mCircle = new CircleComponent(this);
	//  设定半径
	mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
	//  移出敌人容器
	auto iter = std::find(GetGame()->GetEnemies().begin(), GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  是否到达终点
	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.0f))
	{
		SetState(EDead);
	}
}
