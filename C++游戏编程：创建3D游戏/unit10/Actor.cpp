#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	: mState(EActive)
	, mPosition(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mScale(1.0f)
	, mGame(game)
	, mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	//  �Ƴ���ɫ
	mGame->RemoveActor(this);
	//  ɾ�����
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

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		//  �������
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}
		//  ��ɫ��������
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{

}

void Actor::RotateToNewForward(const Vector3& forward)
{
	//  ����ɷ������·���ļн�
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	//  ���򲻱�
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	//  ������
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	//  ������Ԫ������ת
	else
	{
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		//  ����������������ž���
		mWorldTransform = Matrix4::CreateScale(mScale);
		//  ��ת��Ԫ��
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		//  ƽ��
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);
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

