#pragma once
#include "Component.h"
#include "Math.h"
class CircleComponent :
    public Component
{
public:
	CircleComponent(class Actor* owner);
	//  ���ʺ��޸�
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
	//  �õ��е�
	const Vector2& GetCenter() const;
private:
	//  �뾶
	float mRadius;
};
//  ��ײ���
bool Intersect(const CircleComponent& a, const CircleComponent& b);
