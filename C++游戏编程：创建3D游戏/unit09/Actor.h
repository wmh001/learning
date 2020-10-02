#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	//  �����ɫ��״̬
	enum State
	{
		EActive,  //  ��Ծ
		EPaused,  //  ��ͣ
		EDead  //  ����
	};
	Actor(class Game* game);
	virtual ~Actor();
	//  ����
	void Update(float deltaTime);
	//  �������
	void UpdateComponents(float deltaTime);
	//  ���½�ɫ
	virtual void UpdateActor(float deltaTime);
	//  ���봦��
	void ProcessInput(const uint8_t* keyState);
	//  ��ɫ��������
	virtual void ActorInput(const uint8_t* keyState);
	//  ���ʺ��޸�λ��
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	//  ���ʺ��޸ı���
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	//  ���ʺ��޸���Ԫ��
	const Quaternion& GetRotation() const { return mRotation; }
	void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	//  ��������任����
	void ComputeWorldTransform();
	//  ��������任����
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	//  ����ǰ��
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	//  ��������
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }
	//  ���ʺ���������״̬
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	//  ����������Ϸ
	class Game* GetGame() { return mGame; }
	//  ���/�Ƴ����
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	//  ��ɫ������״̬
	State mState;
	//  ����任����
	Matrix4 mWorldTransform;
	//  λ��
	Vector3 mPosition;
	//  ����
	float mScale;
	//  ��Ԫ��
	Quaternion mRotation;
	//  �Ƿ���Ҫ���¼�������任����
	bool mRecomputeWorldTransform;
	//  �������������
	std::vector<class Component*> mComponents;
	//  ������Ϸ
	class Game* mGame;
};

