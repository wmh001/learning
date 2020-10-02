#pragma once
#include <unordered_map>
#include <string>
#include "SoundEvent.h"
#include "Math.h"

//  创建前向声明来避免包括头文件
namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};

class AudioSystem
{
public:
	AudioSystem(class Game* game);
	~AudioSystem();
	//  初始化
	bool Initialize();
	//  关闭
	void Shutdown();
	//  加载存储库
	void LoadBank(const std::string& name);
	//  卸载存储库
	void UnloadBank(const std::string& name);
	//  卸载所有存储库
	void UnloadAllBanks();
	//  播放事件
	SoundEvent PlayEvent(const std::string& name);
	//  更新
	void Update(float deltaTime);
	//  设置侦听器
	void SetListener(const Matrix4& viewMatrix);
	//  修改和访问总线参数
	float GetBusVolume(const std::string& name) const;
	bool GetBusPaused(const std::string& name) const;
	void SetBusVolume(const std::string& name, float volume);
	void SetBusPaused(const std::string& name, bool pause);
protected:
	//  声明友元类
	friend class SoundEvent;
	//  访问事件实例，soundevent类需要访问
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
private:
	// 静态变量，下一个事件的id
	static unsigned int sNextID;
	//  所属游戏
	class Game* mGame;
	//  存储库的映射，键为字符串，值为库名
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	//  事件描述名的映射，键为字符串，值为事件描述名
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	//  事件实例的映射，键为id，值为事件实例
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
	//  总线元素的映射，键为字符串，值为总线
	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
	// FMOD studio系统
	FMOD::Studio::System* mSystem;
	// FMOD低阶系统
	FMOD::System* mLowLevelSystem;
};

