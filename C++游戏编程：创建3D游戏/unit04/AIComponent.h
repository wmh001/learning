#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>

class AIComponent :
    public Component
{
public:
	//  ���캯��
	AIComponent(class Actor* owner);
	//  ����
	void Update(float deltaTime) override;
	//  �ı�״̬
	void ChangeState(const std::string& name);
	//  ������״̬��״̬ͼ��
	void RegisterState(class AIState* state);
private:
	//  ״̬ͼ
	std::unordered_map<std::string, class AIState*> mStateMap;
	//  Ŀǰ��״̬
	class AIState* mCurrentState;
};

