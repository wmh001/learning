#include "AudioSystem.h"
#include <SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>

//  ��ʼ��Ϊ0
unsigned int AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(Game* game)
	: mGame(game)
	, mSystem(nullptr)
	, mLowLevelSystem(nullptr)
{

}

AudioSystem::~AudioSystem()
{

}

bool AudioSystem::Initialize()
{
	//  ���ô�����־��¼
	FMOD::Debug_Initialize(
		FMOD_DEBUG_LEVEL_ERROR, //  ֻ��¼����
		FMOD_DEBUG_MODE_TTY //  ��־д���׼���
	);
	//  ����FMOD studio����
	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&mSystem);
	//  ʧ�ܴ���
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}
	//  ��ʼ��FMOD studio
	result = mSystem->initialize(
		512, //  ��󲢷�������
		FMOD_STUDIO_INIT_NORMAL, //  FMOD studioĬ������
		FMOD_INIT_NORMAL, //  FMOD�ͽ�Ĭ������
		nullptr //  �޶�����������
	);
	//  ʧ�ܴ���
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}
	//  ��ȡFMOD�ͽ�ϵͳָ��
	mSystem->getLowLevelSystem(&mLowLevelSystem);
	//  ����Ĭ�����洢��
	LoadBank("Assets/Master Bank.strings.bank");
	LoadBank("Assets/Master Bank.bank");
	return true;
}

void AudioSystem::Shutdown()
{
	//  ж�����п�
	UnloadAllBanks();
	//  �ر�FMODϵͳ
	if (mSystem)
	{
		mSystem->release();
	}
}

void AudioSystem::LoadBank(const std::string& name)
{
	//  �����μ���
	if (mBanks.find(name) != mBanks.end())
	{
		return;
	}
	//  ���ؿ�
	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(
		name.c_str(),  //  ���ļ���
		FMOD_STUDIO_LOAD_BANK_NORMAL,  //  �������
		&bank  //  ��ȡָ����ָ��
	);
	//  ���·����
	const int maxPathLength = 512;
	if (result == FMOD_OK)
	{
		//  ��ӵ�ӳ����
		mBanks.emplace(name, bank);
		//  ������������
		bank->loadSampleData();
		//  ��ȡ�����¼�������
		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0)
		{
			//  ��ȡ�����¼��������б�
			std::vector<FMOD::Studio::EventDescription*> events(numEvents);
			bank->getEventList(events.data(), numEvents, &numEvents);
			char eventName[maxPathLength];
			for (int i = 0; i < numEvents; i++)
			{
				//  ��ȡ�¼�����
				FMOD::Studio::EventDescription* e = events[i];
				//  ��ȡ�¼���·����ʽ����
				e->getPath(eventName, maxPathLength, nullptr);
				//  ��ӵ�ӳ����
				mEvents.emplace(eventName, e);
			}
		}
		//  ������
		int numBuses = 0;
		//  ��ȡ������
		bank->getBusCount(&numBuses);
		if (numBuses > 0)
		{
			//  ��ȡ���������б�
			std::vector<FMOD::Studio::Bus*> buses(numBuses);
			bank->getBusList(buses.data(), numBuses, &numBuses);
			char busName[512];
			for (int i = 0; i < numBuses; i++)
			{
				//  ��ȡ����
				FMOD::Studio::Bus* bus = buses[i];
				//  ��ȡ���ߵ�·����ʽ����
				bus->getPath(busName, 512, nullptr);
				//  ��ӵ�ӳ����
				mBuses.emplace(busName, bus);
			}
		}
	}
}

void AudioSystem::UnloadBank(const std::string& name)
{
	//  ����δ����
	auto iter = mBanks.find(name);
	if (iter == mBanks.end())
	{
		return;
	}
	//  �ӿ����Ƴ������¼�
	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0)
	{
		//  ��ȡ�¼�����
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		//  �õ��¼������б�
		bank->getEventList(events.data(), numEvents, &numEvents);
		char eventName[512];
		for (int i = 0; i < numEvents; i++)
		{
			//  ��ȡ�¼�����
			FMOD::Studio::EventDescription* e = events[i];
			//  ��ȡ�¼�·����ʽ����
			e->getPath(eventName, 512, nullptr);
			//  �Ƴ��¼�
			auto eventi = mEvents.find(eventName);
			if (eventi != mEvents.end())
			{
				mEvents.erase(eventi);
			}
		}
	}
	//  ������
	int numBuses = 0;
	//  ��ȡ������
	bank->getBusCount(&numBuses);
	if (numBuses > 0)
	{
		//  ��ȡ���������б�
		std::vector<FMOD::Studio::Bus*> buses(numBuses);
		bank->getBusList(buses.data(), numBuses, &numBuses);
		char busName[512];
		for (int i = 0; i < numBuses; i++)
		{
			//  ��ȡ����
			FMOD::Studio::Bus* bus = buses[i];
			//  ��ȡ���ߵ�·����ʽ����
			bus->getPath(busName, 512, nullptr);
			//  �Ƴ�����
			auto busi = mBuses.find(busName);
			if (busi != mBuses.end())
			{
				mBuses.erase(busi);
			}
		}
	}
	//  ����������ݺͿ�
	bank->unloadSampleData();
	bank->unload();
	//  ������
	mBanks.erase(iter);
}

void AudioSystem::UnloadAllBanks()
{
	for (auto& iter : mBanks)
	{
		//  ����������ݺͿ�
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	//  �����
	mBanks.clear();
	//  ����¼�
	mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
	//  �����¼�id
	unsigned int retID = 0;
	//  ��ȡ�¼�
	auto iter = mEvents.find(name);
	if (iter != mEvents.end())
	{
		//  �����¼�ʵ��
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			//  ��ʼ�¼�ʵ��
			event->start();
			//  ������id
			sNextID++;
			//  ���¼�ʵ����ӵ�ӳ����
			retID = sNextID;
			mEventInstances.emplace(retID, event);
		}
	}
	//  ��ֱ�ӷ���EventInstanceָ�룬��ֹFMOD API��¶
	return SoundEvent(this, retID);
}

void AudioSystem::Update(float deltaTime)
{
	//  ��ȡ����Ҫ���¼�ʵ��
	std::vector<unsigned int> done;
	for (auto& iter : mEventInstances)
	{
		//  ��ȡ�¼�ʵ��
		FMOD::Studio::EventInstance* e = iter.second;
		//  ��ȡ�¼�״̬
		FMOD_STUDIO_PLAYBACK_STATE state;
		e->getPlaybackState(&state);
		//  ֹͣ�¼�����
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			//  �ر��¼�
			e->release();
			//  ���id������Ҫ���¼���
			done.emplace_back(iter.first);
		}
	}
	//  ɾ������Ҫ���¼�
	for (auto id : done)
	{
		mEventInstances.erase(id);
	}
	//  ����FMOD
	mSystem->update();
}

namespace
{
	//  ��Ϸ��������Ƶ������ת��
	FMOD_VECTOR VecToFMOD(const Vector3& in)
	{
		// +xǰ��+y�ң�+z�ϵ�FMOD+zǰ,+x��, +y��
		FMOD_VECTOR v;
		v.x = in.y;
		v.y = in.z;
		v.z = in.x;
		return v;
	}
}

void AudioSystem::SetListener(const Matrix4& viewMatrix)
{
	//  ת����Ұ����
	Matrix4 invView = viewMatrix;
	invView.Invert();
	//  ����������
	FMOD_3D_ATTRIBUTES listener;
	//  ������ǰ��������Ϊ�ռ�λ��
	listener.position = VecToFMOD(invView.GetTranslation());
	//  ������ǰ����������ǰ
	listener.forward = VecToFMOD(invView.GetZAxis());
	//  �ڶ���ǰ������������
	listener.up = VecToFMOD(invView.GetYAxis());
	//  ���ٶ�����Ϊ�㣨���ʹ�ö�����ЧӦ�������������
	listener.velocity = { 0.0f, 0.0f, 0.0f };
	//  �͵�FMOD
	mSystem->setListenerAttributes(0, &listener);
}

float AudioSystem::GetBusVolume(const std::string& name) const
{
	float retVal = 0.0f;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getVolume(&retVal);
	}
	return retVal;
}

bool AudioSystem::GetBusPaused(const std::string& name) const
{
	bool retVal = false;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getPaused(&retVal);
	}
	return retVal;
}

void AudioSystem::SetBusVolume(const std::string& name, float volume)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setVolume(volume);
	}
}

void AudioSystem::SetBusPaused(const std::string& name, bool pause)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setPaused(pause);
	}
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
	FMOD::Studio::EventInstance* event = nullptr;
	//  ��ȡ�¼�ʵ��
	auto iter = mEventInstances.find(id);
	if (iter != mEventInstances.end())
	{
		event = iter->second;
	}
	return event;
}
