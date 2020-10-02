#include "SoundEvent.h"
#include "AudioSystem.h"
#include <fmod_studio.hpp>

SoundEvent::SoundEvent(class AudioSystem* system, unsigned int id)
	: mSystem(system)
	, mID(id)
{

}

SoundEvent::SoundEvent()
	: mSystem(nullptr)
	, mID(0)
{

}

bool SoundEvent::IsValid()
{
	//  是否无系统及是否有此id
	return (mSystem && mSystem->GetEventInstance(mID) != nullptr);
}

void SoundEvent::Restart()
{
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  启动
	if (event)
	{
		event->start();
	}
}

void SoundEvent::Stop(bool allowFadeOut /* true */)
{
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  停止
	if (event)
	{
		FMOD_STUDIO_STOP_MODE mode = allowFadeOut ?
			FMOD_STUDIO_STOP_ALLOWFADEOUT :
			FMOD_STUDIO_STOP_IMMEDIATE;
		event->stop(mode);
	}
}

void SoundEvent::SetPaused(bool pause)
{
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  暂停
	if (event)
	{
		event->setPaused(pause);
	}
}

void SoundEvent::SetVolume(float value)
{
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  设置音量
	if (event)
	{
		event->setVolume(value);
	}
}

void SoundEvent::SetPitch(float value)
{
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  设置音高
	if (event)
	{
		event->setPitch(value);
	}
}

void SoundEvent::SetParameter(const std::string& name, float value)
{
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  设置范围
	if (event)
	{
		event->setParameterValue(name.c_str(), value);
	}
}

bool SoundEvent::GetPaused() const
{
	bool retVal = false;
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  访问状态
	if (event)
	{
		event->getPaused(&retVal);
	}
	return retVal;
}

float SoundEvent::GetVolume() const
{
	float retVal = 0.0f;
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  访问音量
	if (event)
	{
		event->getVolume(&retVal);
	}
	return retVal;
}

float SoundEvent::GetPitch() const
{
	float retVal = 0.0f;
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  访问音高
	if (event)
	{
		event->getPitch(&retVal);
	}
	return retVal;
}

float SoundEvent::GetParameter(const std::string& name)
{
	float retVal = 0.0f;
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  访问范围
	if (event)
	{
		event->getParameterValue(name.c_str(), &retVal);
	}
	return retVal;
}

bool SoundEvent::Is3D() const
{
	bool retVal = false;
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		//  获取事件描述
		FMOD::Studio::EventDescription* ed = nullptr;
		event->getDescription(&ed);
		if (ed)
		{
			//  是否3d
			ed->is3D(&retVal);
		}
	}
	return retVal;
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

void SoundEvent::Set3DAttributes(const Matrix4& worldTrans)
{
	//  获取事件
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		//  定义3d属性
		FMOD_3D_ATTRIBUTES attr;
		//  第四行前三个分量为空间位置
		attr.position = VecToFMOD(worldTrans.GetTranslation());
		//  世界坐标中，第一行前三个分量向前
		attr.forward = VecToFMOD(worldTrans.GetXAxis());
		//  第三行前三个分量向上
		attr.up = VecToFMOD(worldTrans.GetZAxis());
		//  将速度设置为零（如果使用多普勒效应，则进行修正）
		attr.velocity = { 0.0f, 0.0f, 0.0f };
		//  设置3d属性
		event->set3DAttributes(&attr);
	}
}
