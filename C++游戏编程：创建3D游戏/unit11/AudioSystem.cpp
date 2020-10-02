#include "AudioSystem.h"
#include <SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>

//  初始化为0
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
	//  设置错误日志记录
	FMOD::Debug_Initialize(
		FMOD_DEBUG_LEVEL_ERROR, //  只记录错误
		FMOD_DEBUG_MODE_TTY //  日志写入标准输出
	);
	//  创建FMOD studio对象
	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&mSystem);
	//  失败处理
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}
	//  初始化FMOD studio
	result = mSystem->initialize(
		512, //  最大并发声音数
		FMOD_STUDIO_INIT_NORMAL, //  FMOD studio默认设置
		FMOD_INIT_NORMAL, //  FMOD低阶默认设置
		nullptr //  无额外驱动数据
	);
	//  失败处理
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}
	//  获取FMOD低阶系统指针
	mSystem->getLowLevelSystem(&mLowLevelSystem);
	//  加载默认主存储库
	LoadBank("Assets/Master Bank.strings.bank");
	LoadBank("Assets/Master Bank.bank");
	return true;
}

void AudioSystem::Shutdown()
{
	//  卸载所有库
	UnloadAllBanks();
	//  关闭FMOD系统
	if (mSystem)
	{
		mSystem->release();
	}
}

void AudioSystem::LoadBank(const std::string& name)
{
	//  避免多次加载
	if (mBanks.find(name) != mBanks.end())
	{
		return;
	}
	//  加载库
	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(
		name.c_str(),  //  库文件名
		FMOD_STUDIO_LOAD_BANK_NORMAL,  //  常规加载
		&bank  //  获取指向库的指针
	);
	//  最大路径数
	const int maxPathLength = 512;
	if (result == FMOD_OK)
	{
		//  添加到映射中
		mBanks.emplace(name, bank);
		//  加载样例数据
		bank->loadSampleData();
		//  获取库中事件的数量
		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0)
		{
			//  获取库中事件描述的列表
			std::vector<FMOD::Studio::EventDescription*> events(numEvents);
			bank->getEventList(events.data(), numEvents, &numEvents);
			char eventName[maxPathLength];
			for (int i = 0; i < numEvents; i++)
			{
				//  获取事件描述
				FMOD::Studio::EventDescription* e = events[i];
				//  获取事件的路径形式名称
				e->getPath(eventName, maxPathLength, nullptr);
				//  添加到映射中
				mEvents.emplace(eventName, e);
			}
		}
		//  总线数
		int numBuses = 0;
		//  获取总线数
		bank->getBusCount(&numBuses);
		if (numBuses > 0)
		{
			//  获取库中总线列表
			std::vector<FMOD::Studio::Bus*> buses(numBuses);
			bank->getBusList(buses.data(), numBuses, &numBuses);
			char busName[512];
			for (int i = 0; i < numBuses; i++)
			{
				//  获取总线
				FMOD::Studio::Bus* bus = buses[i];
				//  获取总线的路径形式名称
				bus->getPath(busName, 512, nullptr);
				//  添加到映射中
				mBuses.emplace(busName, bus);
			}
		}
	}
}

void AudioSystem::UnloadBank(const std::string& name)
{
	//  忽略未加载
	auto iter = mBanks.find(name);
	if (iter == mBanks.end())
	{
		return;
	}
	//  从库中移除所有事件
	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0)
	{
		//  获取事件描述
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		//  得到事件描述列表
		bank->getEventList(events.data(), numEvents, &numEvents);
		char eventName[512];
		for (int i = 0; i < numEvents; i++)
		{
			//  获取事件描述
			FMOD::Studio::EventDescription* e = events[i];
			//  获取事件路径形式名称
			e->getPath(eventName, 512, nullptr);
			//  移除事件
			auto eventi = mEvents.find(eventName);
			if (eventi != mEvents.end())
			{
				mEvents.erase(eventi);
			}
		}
	}
	//  总线数
	int numBuses = 0;
	//  获取总线数
	bank->getBusCount(&numBuses);
	if (numBuses > 0)
	{
		//  获取库中总线列表
		std::vector<FMOD::Studio::Bus*> buses(numBuses);
		bank->getBusList(buses.data(), numBuses, &numBuses);
		char busName[512];
		for (int i = 0; i < numBuses; i++)
		{
			//  获取总线
			FMOD::Studio::Bus* bus = buses[i];
			//  获取总线的路径形式名称
			bus->getPath(busName, 512, nullptr);
			//  移除总线
			auto busi = mBuses.find(busName);
			if (busi != mBuses.end())
			{
				mBuses.erase(busi);
			}
		}
	}
	//  清除样例数据和库
	bank->unloadSampleData();
	bank->unload();
	//  出容器
	mBanks.erase(iter);
}

void AudioSystem::UnloadAllBanks()
{
	for (auto& iter : mBanks)
	{
		//  清除样例数据和库
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	//  清除库
	mBanks.clear();
	//  清除事件
	mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
	//  定义事件id
	unsigned int retID = 0;
	//  获取事件
	auto iter = mEvents.find(name);
	if (iter != mEvents.end())
	{
		//  创建事件实例
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			//  开始事件实例
			event->start();
			//  增加新id
			sNextID++;
			//  将事件实例添加到映射中
			retID = sNextID;
			mEventInstances.emplace(retID, event);
		}
	}
	//  不直接返回EventInstance指针，防止FMOD API暴露
	return SoundEvent(this, retID);
}

void AudioSystem::Update(float deltaTime)
{
	//  获取不需要的事件实例
	std::vector<unsigned int> done;
	for (auto& iter : mEventInstances)
	{
		//  获取事件实例
		FMOD::Studio::EventInstance* e = iter.second;
		//  获取事件状态
		FMOD_STUDIO_PLAYBACK_STATE state;
		e->getPlaybackState(&state);
		//  停止事件处理
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			//  关闭事件
			e->release();
			//  添加id到不需要的事件中
			done.emplace_back(iter.first);
		}
	}
	//  删除不需要的事件
	for (auto id : done)
	{
		mEventInstances.erase(id);
	}
	//  更新FMOD
	mSystem->update();
}

namespace
{
	//  游戏坐标与音频库坐标转换
	FMOD_VECTOR VecToFMOD(const Vector3& in)
	{
		// +x前，+y右，+z上到FMOD+z前,+x右, +y上
		FMOD_VECTOR v;
		v.x = in.y;
		v.y = in.z;
		v.z = in.x;
		return v;
	}
}

void AudioSystem::SetListener(const Matrix4& viewMatrix)
{
	//  转置视野矩阵
	Matrix4 invView = viewMatrix;
	invView.Invert();
	//  创建侦听器
	FMOD_3D_ATTRIBUTES listener;
	//  第四行前三个分量为空间位置
	listener.position = VecToFMOD(invView.GetTranslation());
	//  第三行前三个分量向前
	listener.forward = VecToFMOD(invView.GetZAxis());
	//  第二行前三个分量向上
	listener.up = VecToFMOD(invView.GetYAxis());
	//  将速度设置为零（如果使用多普勒效应，则进行修正）
	listener.velocity = { 0.0f, 0.0f, 0.0f };
	//  送到FMOD
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
	//  获取事件实例
	auto iter = mEventInstances.find(id);
	if (iter != mEventInstances.end())
	{
		event = iter->second;
	}
	return event;
}
