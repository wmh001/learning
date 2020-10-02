#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent :
    public Component
{
public:
	CircleComponent(class Actor* owner);
	//  ���ʺ��޸İ뾶
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
	//  �õ�����
	const Vector3& GetCenter() const;
private:
	//  �뾶
	float mRadius;
};

//  ��ײ���
bool Intersect(const CircleComponent& a, const CircleComponent& b);
