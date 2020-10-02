#pragma once
#include "Component.h"
#include "Math.h"

class CameraComponent :
    public Component
{
public:
	CameraComponent(class Actor* owner, int updateOrder = 200);
protected:
	//  ´«µİÊÓÍ¼¾ØÕó
	void SetViewMatrix(const Matrix4& view);
};
