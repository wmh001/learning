#pragma once
#include <cstdint>

class Component
{
public:
	//  更新顺序越小，更新越早
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	//  更新组件
	virtual void Update(float deltaTime);
	//  输入处理
	virtual void ProcessInput(const struct InputState& state) {}
	//  处理世界变换矩阵的更新
	virtual void OnUpdateWorldTransform() { }
	//  访问更新顺序
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//  所属角色
	class Actor* mOwner;
	//  更新顺序
	int mUpdateOrder;
};

