#include "MoveComponentL.h"
#include "Actor.h"

MoveComponentL::MoveComponentL(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
{

}

void MoveComponentL::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		//  计算原角度
		float rot = mOwner->GetRotation();
		//  计算新角度
		rot += mAngularSpeed * deltaTime;
		//  更改角度
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed))
	{
		//  计算原位置
		Vector2 pos = mOwner->GetPosition();
		//  计算新位置
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		//  激光位置出窗处理
		if (pos.x < 0.0f) { mOwner->SetState(Actor::EDead); }
		else if (pos.x > 1024.0f) { mOwner->SetState(Actor::EDead); }
		if (pos.y < 0.0f) { mOwner->SetState(Actor::EDead); }
		else if (pos.y > 768.0f) { mOwner->SetState(Actor::EDead); }
		mOwner->SetPosition(pos);
	}
}