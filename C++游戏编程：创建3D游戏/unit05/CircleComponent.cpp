#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner)
	:Component(owner)
	, mRadius(0.0f)
{

}

const Vector2& CircleComponent::GetCenter() const
{
	//  ����Բ��
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	//  ���ذ뾶
	return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	//  ��������ƽ��
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();
	// ����뾶�͵�ƽ��
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;
	return distSq <= radiiSq;
}