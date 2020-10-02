#include "Tower.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"

Tower::Tower(class Game* game)
	:Actor(game)
{
	//  �����������
	game->GetTowers().emplace_back(this);
	//  �����������
	SpriteComponent* sc = new SpriteComponent(this, 200);
	//  ����ͼ��
	sc->SetTexture(game->GetTexture("Assets/Tower.png"));
	//  �����ƶ����
	mMove = new MoveComponent(this);
	//  mMove->SetAngularSpeed(Math::Pi);
	//  �趨����ʱ��
	mNextAttack = AttackTime;
}

void Tower::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  ʱ�����
	mNextAttack -= deltaTime;
	if (mNextAttack <= 0.0f)
	{
		Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
		if (e != nullptr)
		{
			//  �Ƿ���������Χ
			Vector2 dir = e->GetPosition() - GetPosition();
			float dist = dir.Length();
			if (dist < AttackRange)
			{
				//  ת�����
				SetRotation(Math::Atan2(-dir.y, dir.x));
				//  �����ӵ�
				Bullet* b = new Bullet(GetGame());
				b->SetPosition(GetPosition());
				b->SetRotation(GetRotation());
			}
		}
		mNextAttack += AttackTime;
	}
}