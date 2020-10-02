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
	//  �����������
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	//  λ��
	Vector2 pos = GetPosition();
	pos += mVelocityDir * mSpeed * deltaTime;
	SetPosition(pos);
	//  �Ƕ�
	float angle = Math::Atan2(mRotationDir.y, mRotationDir.x);
	SetRotation(angle);
}

void Ship::ActorInput(const InputState& state)
{
	if (state.Mouse.GetButtonValue(1) && mLaserCooldown <= 0.0f)
	{
		//  ���켤�Ⲣ����λ�úͽǶ�
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		//  ���¼���CD
		mLaserCooldown = 0.5f;
	}
	//  ������
	/*if (state.Controller.GetIsConnected())
	{
		//  ��ȡ�ٶȷ���
		mVelocityDir = state.Controller.GetLeftStick();
		//  ��ȡ�Ƕ�
		if (!Math::NearZero(state.Controller.GetRightStick().Length()))
		{
			mRotationDir = state.Controller.GetRightStick();
		}
	}*/
}
