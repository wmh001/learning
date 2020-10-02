#include "Ship.h"
#include "SpriteComponent.h"
#include "InputSystem.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "Texture.h"

Ship::Ship(Game* game)
	:Actor(game)
	, mSpeed(400.0f)
	, mLaserCooldown(0.0f)
{
	//  创建精灵组件
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	//  位置
	Vector2 pos = GetPosition();
	pos += mVelocityDir * mSpeed * deltaTime;
	SetPosition(pos);
	//  角度
	float angle = Math::Atan2(mRotationDir.y, mRotationDir.x);
	SetRotation(angle);
}

void Ship::ActorInput(const InputState& state)
{
	if (state.Mouse.GetButtonValue(1) && mLaserCooldown <= 0.0f)
	{
		//  创造激光并设置位置和角度
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		//  更新激光CD
		mLaserCooldown = 0.5f;
	}
	//  控制器
	/*if (state.Controller.GetIsConnected())
	{
		//  获取速度方向
		mVelocityDir = state.Controller.GetLeftStick();
		//  获取角度
		if (!Math::NearZero(state.Controller.GetRightStick().Length()))
		{
			mRotationDir = state.Controller.GetRightStick();
		}
	}*/
}
