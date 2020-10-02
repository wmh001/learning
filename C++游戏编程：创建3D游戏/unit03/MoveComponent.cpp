#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		//  ����ԭ�Ƕ�
		float rot = mOwner->GetRotation();
		//  �����½Ƕ�
		rot += mAngularSpeed * deltaTime;
		//  ���ĽǶ�
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed))
	{
		//  ����ԭλ��
		Vector2 pos = mOwner->GetPosition();
		//  ������λ��
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		//  ��ʯλ�ó�������
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }
		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }
		mOwner->SetPosition(pos);
	}
}