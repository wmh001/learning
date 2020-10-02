#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Enemy.h"

Bullet::Bullet(class Game* game)
	:Actor(game)
{
	//  创建图像组件
	SpriteComponent* sc = new SpriteComponent(this);
	//  绘制图像
	sc->SetTexture(game->GetTexture("Assets/Projectile.png"));
	//  创建移动组件
	MoveComponent* mc = new MoveComponent(this);
	//  设定线速度
	mc->SetForwardSpeed(400.0f);
	//  创建圆组件
	mCircle = new CircleComponent(this);
	//  设定半径
	mCircle->SetRadius(5.0f);
	//  设定存活时间
	mLiveTime = 1.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  检查是否与敌人碰撞
	for (Enemy* e : GetGame()->GetEnemies())
	{
		if (Intersect(*mCircle, *(e->GetCircle())))
		{
			//  子弹与敌人死亡
			e->SetState(EDead);
			SetState(EDead);
			break;
		}
	}
	//  存活时间减小
	mLiveTime -= deltaTime;
	if (mLiveTime <= 0.0f)
	{
		//  时间到，死亡
		SetState(EDead);
	}
	//  子弹位置出窗处理
	if (GetPosition().x < 0.0f) { SetState(EDead); }
	else if (GetPosition().x > 1024.0f) { SetState(EDead); }
	if (GetPosition().y < 160.0f) { SetState(EDead); }
	else if (GetPosition().y > 608.0f) { SetState(EDead); }
}
