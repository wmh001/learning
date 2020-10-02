#include "NavComponent.h"
#include "Tile.h"

NavComponent::NavComponent(class Actor* owner, int updateOrder)
	:MoveComponent(owner, updateOrder)
	, mNextNode(nullptr)
{

}

void NavComponent::Update(float deltaTime)
{
	if (mNextNode)
	{
		//  ����·��ǰ��
		Vector2 diff = mOwner->GetPosition() - mNextNode->GetPosition();
		if (Math::NearZero(diff.Length(), 2.0f))
		{
			mNextNode = mNextNode->GetParent();
			TurnTo(mNextNode->GetPosition());
		}
	}
	//  �ƶ�
	MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile* start)
{
	mNextNode = start->GetParent();
	TurnTo(mNextNode->GetPosition());
}

void NavComponent::TurnTo(const Vector2& pos)
{
	//  ����
	Vector2 dir = pos - mOwner->GetPosition();
	//  ���㷽λ��
	//  sdl��y��������
	float angle = Math::Atan2(-dir.y, dir.x);
	mOwner->SetRotation(angle);
}
