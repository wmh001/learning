#pragma once
#include "Component.h"
#include "Math.h"

class PointLightComponent :
    public Component
{
public:
	PointLightComponent(class Actor* owner);
	~PointLightComponent();
	//  绘制
	void Draw(class Shader* shader, class Mesh* mesh);
	//  漫反射颜色
	Vector3 mDiffuseColor;
	//  内半径
	float mInnerRadius;
	//  外半径
	float mOuterRadius;
};

