#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	: Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
	, mStrafeSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		//  计算原角度
		Quaternion rot = mOwner->GetRotation();
		//  计算新角度
		float angle = mAngularSpeed * deltaTime;
		//  新角度四元数
		Quaternion inc(Vector3::UnitZ, angle);
		//  四元数乘法
		rot = Quaternion::Concatenate(rot, inc);
		//  更改角度
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed))
	{
		//  计算原位置
		Vector3 pos = mOwner->GetPosition();
		//  计算新位置
		//  前向位移
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		//  侧向位移
		pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
		//  设置位置
		mOwner->SetPosition(pos);
	}
}
