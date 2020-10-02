#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Enemy.h"

Bullet::Bullet(class Game* game)
	:Actor(game)
{
	//  ����ͼ�����
	SpriteComponent* sc = new SpriteComponent(this);
	//  ����ͼ��
	sc->SetTexture(game->GetTexture("Assets/Projectile.png"));
	//  �����ƶ����
	MoveComponent* mc = new MoveComponent(this);
	//  �趨���ٶ�
	mc->SetForwardSpeed(400.0f);
	//  ����Բ���
	mCircle = new CircleComponent(this);
	//  �趨�뾶
	mCircle->SetRadius(5.0f);
	//  �趨���ʱ��
	mLiveTime = 1.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  ����Ƿ��������ײ
	for (Enemy* e : GetGame()->GetEnemies())
	{
		if (Intersect(*mCircle, *(e->GetCircle())))
		{
			//  �ӵ����������
			e->SetState(EDead);
			SetState(EDead);
			break;
		}
	}
	//  ���ʱ���С
	mLiveTime -= deltaTime;
	if (mLiveTime <= 0.0f)
	{
		//  ʱ�䵽������
		SetState(EDead);
	}
	//  �ӵ�λ�ó�������
	if (GetPosition().x < 0.0f) { SetState(EDead); }
	else if (GetPosition().x > 1024.0f) { SetState(EDead); }
	if (GetPosition().y < 160.0f) { SetState(EDead); }
	else if (GetPosition().y > 608.0f) { SetState(EDead); }
}
