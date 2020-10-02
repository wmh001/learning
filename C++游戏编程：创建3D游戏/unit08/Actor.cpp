#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	: mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
	, mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	//  移除角色
	mGame->RemoveActor(this);
	//  移除组件
	//  ~Component只是移除组件
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
		//  更新世界变换矩阵
		ComputeWorldTransform();
		//  更新组件
		UpdateComponents(deltaTime);
		//  更新角色
		UpdateActor(deltaTime);
		//  更新世界变换矩阵
		ComputeWorldTransform();
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

void Actor::ProcessInput(const struct InputState& state)
{
	if (mState == EActive)
	{
		//  遍历组件
		for (auto comp : mComponents)
		{
			comp->ProcessInput(state);
		}
		//  角色特殊输入
		ActorInput(state);
	}
}

void Actor::ActorInput(const struct InputState& state)
{

}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		//  创建比例均衡的缩放矩阵
		mWorldTransform = Matrix4::CreateScale(mScale);
		//  旋转
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		//  平移
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));
		//  组件处理世界变换矩阵的更新
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	//  在排序容器中寻找插入点
	//  第一个元素有更高的顺序
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
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
