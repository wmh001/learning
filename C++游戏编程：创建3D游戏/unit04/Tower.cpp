#include "Tower.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"

Tower::Tower(class Game* game)
	:Actor(game)
{
	//  加入敌人容器
	game->GetTowers().emplace_back(this);
	//  创建精灵组件
	SpriteComponent* sc = new SpriteComponent(this, 200);
	//  绘制图像
	sc->SetTexture(game->GetTexture("Assets/Tower.png"));
	//  创建移动组件
	mMove = new MoveComponent(this);
	//  mMove->SetAngularSpeed(Math::Pi);
	//  设定进攻时间
	mNextAttack = AttackTime;
}

void Tower::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//  时间减少
	mNextAttack -= deltaTime;
	if (mNextAttack <= 0.0f)
	{
		Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
		if (e != nullptr)
		{
			//  是否进入进攻范围
			Vector2 dir = e->GetPosition() - GetPosition();
			float dist = dir.Length();
			if (dist < AttackRange)
			{
				//  转向敌人
				SetRotation(Math::Atan2(-dir.y, dir.x));
				//  发射子弹
				Bullet* b = new Bullet(GetGame());
				b->SetPosition(GetPosition());
				b->SetRotation(GetRotation());
			}
		}
		mNextAttack += AttackTime;
	}
}