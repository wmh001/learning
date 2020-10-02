#pragma once
#include "Component.h"
#include "Math.h"

class PointLightComponent :
    public Component
{
public:
	PointLightComponent(class Actor* owner);
	~PointLightComponent();
	//  ����
	void Draw(class Shader* shader, class Mesh* mesh);
	//  ��������ɫ
	Vector3 mDiffuseColor;
	//  �ڰ뾶
	float mInnerRadius;
	//  ��뾶
	float mOuterRadius;
};

