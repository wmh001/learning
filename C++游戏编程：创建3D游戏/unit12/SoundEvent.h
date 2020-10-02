#pragma once
#include <string>
#include "Math.h"

class SoundEvent
{
public:
	SoundEvent();
	//  �Ƿ����
	bool IsValid();
	//  ����
	void Restart();
	//  ֹͣ
	void Stop(bool allowFadeOut = true);
	//  ��ͣ
	void SetPaused(bool pause);
	//  �޸�����
	void SetVolume(float value);
	//  �޸�����
	void SetPitch(float value);
	//  �޸ķ�Χ
	void SetParameter(const std::string& name, float value);
	//  ����
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	//  �Ƿ�Ϊλ����Ч
	bool Is3D() const;
	//  �޸�3d����
	void Set3DAttributes(const Matrix4& worldTrans);
protected:
	//  ������Ԫ��
	friend class AudioSystem;
	//  ��Ĭ�Ϲ��캯����AudioSystem���Է���
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	//  ����ϵͳ
	class AudioSystem* mSystem;
	//  id
	unsigned int mID;
};

