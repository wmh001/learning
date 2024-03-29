#include "CircleComponent.h"
#include "Actor.h"
//  初始化
CircleComponent::CircleComponent(class Actor* owner)
	:Component(owner)
	, mRadius(0.0f)
{

}

const Vector2& CircleComponent::GetCenter() const
{
	//  返回圆心
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	//  返回半径
	return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	//  计算距离的平方
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();
	// 计算半径和的平方
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;
	return distSq <= radiiSq;
}
