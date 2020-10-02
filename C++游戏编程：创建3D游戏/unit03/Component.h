#pragma once
#include <cstdint>

class Component
{
public:
	//  ����˳��ԽС������Խ��
	Component(class Actor* owner, int updateOrder = 100);
	//  ����
	virtual ~Component();
	//  �������
	virtual void Update(float deltaTime);
	//  ���봦��
	virtual void ProcessInput(const uint8_t* keyState) {}
	//  ���ʸ���˳��
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//  ������ɫ
	class Actor* mOwner;
	//  ����˳��
	int mUpdateOrder;
};

