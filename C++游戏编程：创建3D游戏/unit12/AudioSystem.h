#pragma once
#include <unordered_map>
#include <string>
#include "SoundEvent.h"
#include "Math.h"

//  ����ǰ���������������ͷ�ļ�
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
	//  ��ʼ��
	bool Initialize();
	//  �ر�
	void Shutdown();
	//  ���ش洢��
	void LoadBank(const std::string& name);
	//  ж�ش洢��
	void UnloadBank(const std::string& name);
	//  ж�����д洢��
	void UnloadAllBanks();
	//  �����¼�
	SoundEvent PlayEvent(const std::string& name);
	//  ����
	void Update(float deltaTime);
	//  ����������
	void SetListener(const Matrix4& viewMatrix);
	//  �޸ĺͷ������߲���
	float GetBusVolume(const std::string& name) const;
	bool GetBusPaused(const std::string& name) const;
	void SetBusVolume(const std::string& name, float volume);
	void SetBusPaused(const std::string& name, bool pause);
protected:
	//  ������Ԫ��
	friend class SoundEvent;
	//  �����¼�ʵ����soundevent����Ҫ����
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
private:
	// ��̬��������һ���¼���id
	static unsigned int sNextID;
	//  ������Ϸ
	class Game* mGame;
	//  �洢���ӳ�䣬��Ϊ�ַ�����ֵΪ����
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	//  �¼���������ӳ�䣬��Ϊ�ַ�����ֵΪ�¼�������
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	//  �¼�ʵ����ӳ�䣬��Ϊid��ֵΪ�¼�ʵ��
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
	//  ����Ԫ�ص�ӳ�䣬��Ϊ�ַ�����ֵΪ����
	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
	// FMOD studioϵͳ
	FMOD::Studio::System* mSystem;
	// FMOD�ͽ�ϵͳ
	FMOD::System* mLowLevelSystem;
};

