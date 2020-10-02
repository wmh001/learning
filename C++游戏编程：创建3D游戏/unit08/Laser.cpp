#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Texture.h"

Laser::Laser(Game* game)
	: Actor(game)
	, mDeathTimer(1.0f)
{
	//  创建精灵组件
    SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));
	//  创建移动组件并设定速度
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);
	//  为碰撞检测创建圆组件
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	//  超过时间激光消失
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		//  激光与卫星的碰撞检测
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//  改变生活状态
				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
}
