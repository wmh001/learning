#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponentL.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	:Actor(game)
	, mDeathTimer(1.0f)
{
	//  �����������
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));
	//  �����ƶ�������趨�ٶ�
	MoveComponentL* mc = new MoveComponentL(this);
	mc->SetForwardSpeed(800.0f);
	//  Ϊ��ײ��ⴴ��Բ���
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	//  ����ʱ�伤����ʧ
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		//  ���������ǵ���ײ���
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//  �ı�����״̬
				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
}