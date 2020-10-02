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
	if (!Math::NearZero(mForwardSpeed))
	{
		//  ����ԭλ��
		Vector3 pos = mOwner->GetPosition();
		//  ������λ��
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}
