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
		//  ����ԭ�Ƕ�
		Quaternion rot = mOwner->GetRotation();
		//  �����½Ƕ�
		float angle = mAngularSpeed * deltaTime;
		//  �½Ƕ���Ԫ��
		Quaternion inc(Vector3::UnitZ, angle);
		//  ��Ԫ���˷�
		rot = Quaternion::Concatenate(rot, inc);
		//  ���ĽǶ�
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed))
	{
		//  ����ԭλ��
		Vector3 pos = mOwner->GetPosition();
		//  ������λ��
		//  ǰ��λ��
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		//  ����λ��
		pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
		//  ����λ��
		mOwner->SetPosition(pos);
	}
}
