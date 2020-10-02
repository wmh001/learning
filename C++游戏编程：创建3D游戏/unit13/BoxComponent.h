#pragma once
#include "Component.h"
#include "Collision.h"

class BoxComponent :
    public Component
{
public:
	BoxComponent(class Actor* owner, int updateOrder = 100);
	~BoxComponent();
	//  ��������任����ĸ���
	void OnUpdateWorldTransform() override;
	//  �޸Ķ���ռ��ڵ�AABB��
	void SetObjectBox(const AABB& model) { mObjectBox = model; }
	//  ��������ռ��ڵ�AABB��
	const AABB& GetWorldBox() const { return mWorldBox; }
	//  �޸�
	void SetShouldRotate(bool value) { mShouldRotate = value; }
private:
	//  ����ռ��ڵ�AABB��
	AABB mObjectBox;
	//  ����ռ��ڵ�AABB��
	AABB mWorldBox;
	//  �Ƿ���������ת
	bool mShouldRotate;
};

