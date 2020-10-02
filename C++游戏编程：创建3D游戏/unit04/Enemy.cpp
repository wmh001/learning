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
	//  �����������
	game->GetEnemies().emplace_back(this);
	//  ����ͼ�����
	SpriteComponent* sc = new SpriteComponent(this);
	//  ����ͼ��
	sc->SetTexture(game->GetTexture("Assets/Airplane.png"));
	//  �趨��ʼλ��
	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
	//  ����Ѱ·���
	NavComponent* nc = new NavComponent(this);
	//  �趨���ٶ�
	nc->SetForwardSpeed(150.0f);
	//  �趨��ʼ����
	nc->StartPath(GetGame()->GetGrid()->GetStartTile());
	//  ����Բ���
	mCircle = new CircleComponent(this);
	//  �趨�뾶
	mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
	//  �Ƴ���������
	auto iter = std::find(GetGame()->GetEnemies().begin(), GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  �Ƿ񵽴��յ�
	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.0f))
	{
		SetState(EDead);
	}
}
