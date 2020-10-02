#pragma once
#include <string>
#include "Math.h"

class SoundEvent
{
public:
	SoundEvent();
	//  是否存在
	bool IsValid();
	//  重启
	void Restart();
	//  停止
	void Stop(bool allowFadeOut = true);
	//  暂停
	void SetPaused(bool pause);
	//  修改音量
	void SetVolume(float value);
	//  修改音高
	void SetPitch(float value);
	//  修改范围
	void SetParameter(const std::string& name, float value);
	//  访问
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	//  是否为位置音效
	bool Is3D() const;
	//  修改3d属性
	void Set3DAttributes(const Matrix4& worldTrans);
protected:
	//  声明友元类
	friend class AudioSystem;
	//  非默认构造函数，AudioSystem可以访问
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	//  所属系统
	class AudioSystem* mSystem;
	//  id
	unsigned int mID;
};

