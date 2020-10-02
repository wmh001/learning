#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	//  �Ƴ���ɫ
	mGame->RemoveActor(this);
	//  �Ƴ����
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	//  ���»�Ծ��ɫ
	if (mState == EActive)
	{
		//  �������
		UpdateComponents(deltaTime);
		//  ���½�ɫ
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	//  �������
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		//  �������
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::AddComponent(Component* component)
{
	//  ������������Ѱ�Ҳ����
	//  ��һ��Ԫ���и��ߵ�˳��
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;iter != mComponents.end();++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	//  �ڵ�����֮ǰ��λ�ò���Ԫ��
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	//  Ѱ��Ԫ��
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	//  ɾ��Ԫ��
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
