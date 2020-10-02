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
	//  移除角色
	mGame->RemoveActor(this);
	//  移除组件
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	//  更新活跃角色
	if (mState == EActive)
	{
		//  更新组件
		UpdateComponents(deltaTime);
		//  更新角色
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	//  遍历组件
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
		//  遍历组件
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
	//  在排序容器中寻找插入点
	//  第一个元素有更高的顺序
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;iter != mComponents.end();++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	//  在迭代器之前的位置插入元素
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	//  寻找元素
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	//  删除元素
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
