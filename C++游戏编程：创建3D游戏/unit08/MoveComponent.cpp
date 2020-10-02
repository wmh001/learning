#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	: Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
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
		//  出窗处理
		if (pos.x < -512.0f) { pos.x = 510.0f; }
		else if (pos.x > 512.0f) { pos.x = -510.0f; }
		if (pos.y < -384.0f) { pos.y = 382.0f; }
		else if (pos.y > 384.0f) { pos.y = -382.0f; }
		mOwner->SetPosition(pos);
	}
}