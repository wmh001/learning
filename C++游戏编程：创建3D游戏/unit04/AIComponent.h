#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>

class AIComponent :
    public Component
{
public:
	//  构造函数
	AIComponent(class Actor* owner);
	//  更新
	void Update(float deltaTime) override;
	//  改变状态
	void ChangeState(const std::string& name);
	//  加入新状态到状态图中
	void RegisterState(class AIState* state);
private:
	//  状态图
	std::unordered_map<std::string, class AIState*> mStateMap;
	//  目前的状态
	class AIState* mCurrentState;
};

