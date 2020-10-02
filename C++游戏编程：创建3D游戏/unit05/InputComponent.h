#pragma once
#include "MoveComponent.h"
#include "Math.h"

class InputComponent :
    public MoveComponent
{
public:
	//  首先更新的更新率低
	InputComponent(class Actor* owner);
	//  输入处理
	void ProcessInput(const uint8_t* keyState) override;
	//  访问和设置
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
	//  最大线速度和角速度
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	//  前进后退的按键
	int mForwardKey;
	int mBackKey;
	//  方向改变的按键
	int mClockwiseKey;
	int mCounterClockwiseKey;
};

