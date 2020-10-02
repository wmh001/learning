#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	//  定义角色的状态
	enum State
	{
		EActive,  //  活跃
		EPaused,  //  暂停
		EDead  //  死亡
	};
	Actor(class Game* game);
	virtual ~Actor();
	//  更新
	void Update(float deltaTime);
	//  更新组件
	void UpdateComponents(float deltaTime);
	//  更新角色
	virtual void UpdateActor(float deltaTime);
	//  输入处理
	void ProcessInput(const uint8_t* keyState);
	//  角色特殊输入
	virtual void ActorInput(const uint8_t* keyState);
	//  访问和修改位置
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	//  访问和修改比例
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	//  访问和修改四元数
	const Quaternion& GetRotation() const { return mRotation; }
	void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	//  计算世界变换矩阵
	void ComputeWorldTransform();
	//  访问世界变换矩阵
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	//  访问前向
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	//  访问右向
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }
	//  访问和设置生活状态
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	//  访问所属游戏
	class Game* GetGame() { return mGame; }
	//  添加/移除组件
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	//  角色的生活状态
	State mState;
	//  世界变换矩阵
	Matrix4 mWorldTransform;
	//  位置
	Vector3 mPosition;
	//  比例
	float mScale;
	//  四元数
	Quaternion mRotation;
	//  是否需要重新计算世界变换矩阵
	bool mRecomputeWorldTransform;
	//  所有组件的容器
	std::vector<class Component*> mComponents;
	//  所属游戏
	class Game* mGame;
};

