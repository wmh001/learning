#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent :
    public Component
{
public:
	CircleComponent(class Actor* owner);
	//  访问和修改半径
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
	//  得到中心
	const Vector3& GetCenter() const;
private:
	//  半径
	float mRadius;
};

//  碰撞检测
bool Intersect(const CircleComponent& a, const CircleComponent& b);
