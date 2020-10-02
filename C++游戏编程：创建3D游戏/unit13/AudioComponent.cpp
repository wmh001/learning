#include "AudioComponent.h"
#include "Actor.h"
#include "Game.h"
#include "AudioSystem.h"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
	: Component(owner, updateOrder)
{

}

AudioComponent::~AudioComponent()
{
	//  ֹͣ�����¼�
	StopAllEvents();
}

void AudioComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);
	//  �Ƴ���Ч��2d�¼�
	auto iter = mEvents2D.begin();
	while (iter != mEvents2D.end())
	{
		if (!iter->IsValid())
		{
			//  �Ƴ��¼�
			iter = mEvents2D.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//  �Ƴ���Ч��3d�¼�
	iter = mEvents3D.begin();
	while (iter != mEvents3D.end())
	{
		if (!iter->IsValid())
		{
			//  �Ƴ��¼�
			iter = mEvents3D.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void AudioComponent::OnUpdateWorldTransform()
{
	//  ����3d�¼�������任����
	Matrix4 world = mOwner->GetWorldTransform();
	for (auto& event : mEvents3D)
	{
		if (event.IsValid())
		{
			event.Set3DAttributes(world);
		}
	}
}

SoundEvent AudioComponent::PlayEvent(const std::string& name)
{
	SoundEvent e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
	//  2d����3d
	if (e.Is3D())
	{
		//  ������
		mEvents3D.emplace_back(e);
		//  ��ʼ��3d����
		e.Set3DAttributes(mOwner->GetWorldTransform());
	}
	else
	{
		mEvents2D.emplace_back(e);
	}
	return e;
}

void AudioComponent::StopAllEvents()
{
	//  ֹͣ��������
	for (auto& e : mEvents2D)
	{
		e.Stop();
	}
	for (auto& e : mEvents3D)
	{
		e.Stop();
	}
	//  ����¼�
	mEvents2D.clear();
	mEvents3D.clear();
}
