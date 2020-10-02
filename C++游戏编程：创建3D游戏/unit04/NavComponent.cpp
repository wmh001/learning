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
		//  沿着路径前进
		Vector2 diff = mOwner->GetPosition() - mNextNode->GetPosition();
		if (Math::NearZero(diff.Length(), 2.0f))
		{
			mNextNode = mNextNode->GetParent();
			TurnTo(mNextNode->GetPosition());
		}
	}
	//  移动
	MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile* start)
{
	mNextNode = start->GetParent();
	TurnTo(mNextNode->GetPosition());
}

void NavComponent::TurnTo(const Vector2& pos)
{
	//  向量
	Vector2 dir = pos - mOwner->GetPosition();
	//  计算方位角
	//  sdl的y正方向朝下
	float angle = Math::Atan2(-dir.y, dir.x);
	mOwner->SetRotation(angle);
}
