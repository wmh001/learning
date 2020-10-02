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
	//  �Ƴ���ɫ
	mGame->RemoveActor(this);
	//  �Ƴ����
	//  ~Componentֻ���Ƴ����
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
		//  ��������任����
		ComputeWorldTransform();
		//  �������
		UpdateComponents(deltaTime);
		//  ���½�ɫ
		UpdateActor(deltaTime);
		//  ��������任����
		ComputeWorldTransform();
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

void Actor::ProcessInput(const struct InputState& state)
{
	if (mState == EActive)
	{
		//  �������
		for (auto comp : mComponents)
		{
			comp->ProcessInput(state);
		}
		//  ��ɫ��������
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
		//  ����������������ž���
		mWorldTransform = Matrix4::CreateScale(mScale);
		//  ��ת
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		//  ƽ��
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));
		//  �����������任����ĸ���
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	//  ������������Ѱ�Ҳ����
	//  ��һ��Ԫ���и��ߵ�˳��
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
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
