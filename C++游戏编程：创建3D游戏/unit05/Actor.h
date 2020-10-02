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
	//  ���캯��
	Actor(class Game* game);
	//  ��������
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
	const Vector2& GetPosition() const { return mPosition;}
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true;}
	//  ���ʺ��޸ı���
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true;}
	//  ���ʺ��޸Ľ��ٶ�
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true;}
	//  ��������任����
	void ComputeWorldTransform();
	//  ��������任����
	const Matrix4& GetWorldTransform() const { return mWorldTransform;}
	//  ������λ��
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }
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
	Vector2 mPosition;
	//  ����
	float mScale;
	//  ���ٶ�
	float mRotation;
	//  �Ƿ���Ҫ���¼�������任����
	bool mRecomputeWorldTransform;
	//  �������������
	std::vector<class Component*> mComponents;
	//  ������Ϸ
	class Game* mGame;
};

