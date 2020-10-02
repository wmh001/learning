#pragma once
#include "MoveComponent.h"
#include "Math.h"

class InputComponent :
    public MoveComponent
{
public:
	//  ���ȸ��µĸ����ʵ�
	InputComponent(class Actor* owner);
	//  ���봦��
	void ProcessInput(const uint8_t* keyState) override;
	//  ���ʺ�����
	float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }
	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
private:
	//  ������ٶȺͽ��ٶ�
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	//  ǰ�����˵İ���
	int mForwardKey;
	int mBackKey;
	//  ����ı�İ���
	int mClockwiseKey;
	int mCounterClockwiseKey;
};

