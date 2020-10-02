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
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);
	//  ���ʺ��޸�λ��
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	//  ���ʺ��޸ı���
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	//  ���ʺ��޸Ľ��ٶ�
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	//  ������λ��
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }
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
	//  λ��
	Vector2 mPosition;
	//  ����
	float mScale;
	//  ���ٶ�
	float mRotation;
	//  �������������
	std::vector<class Component*> mComponents;
	//  ������Ϸ
	class Game* mGame;
};

