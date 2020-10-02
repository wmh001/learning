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
		//  ����λ�ó�������
		if (pos.x < 0.0f) { mOwner->SetState(Actor::EDead); }
		else if (pos.x > 1024.0f) { mOwner->SetState(Actor::EDead); }
		if (pos.y < 0.0f) { mOwner->SetState(Actor::EDead); }
		else if (pos.y > 768.0f) { mOwner->SetState(Actor::EDead); }
		mOwner->SetPosition(pos);
	}
}