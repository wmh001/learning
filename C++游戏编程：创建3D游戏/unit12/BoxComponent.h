#pragma once
#include "Component.h"
#include "Collision.h"

class BoxComponent :
    public Component
{
public:
	BoxComponent(class Actor* owner, int updateOrder = 100);
	~BoxComponent();
	//  处理世界变换矩阵的更新
	void OnUpdateWorldTransform() override;
	//  修改对象空间内的AABB框
	void SetObjectBox(const AABB& model) { mObjectBox = model; }
	//  访问世界空间内的AABB框
	const AABB& GetWorldBox() const { return mWorldBox; }
	//  修改
	void SetShouldRotate(bool value) { mShouldRotate = value; }
private:
	//  对象空间内的AABB框
	AABB mObjectBox;
	//  世界空间内的AABB框
	AABB mWorldBox;
	//  是否随世界旋转
	bool mShouldRotate;
};

