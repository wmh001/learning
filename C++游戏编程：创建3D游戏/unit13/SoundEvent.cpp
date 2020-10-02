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
	//  �Ƿ���ϵͳ���Ƿ��д�id
	return (mSystem && mSystem->GetEventInstance(mID) != nullptr);
}

void SoundEvent::Restart()
{
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ����
	if (event)
	{
		event->start();
	}
}

void SoundEvent::Stop(bool allowFadeOut /* true */)
{
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ֹͣ
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
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ��ͣ
	if (event)
	{
		event->setPaused(pause);
	}
}

void SoundEvent::SetVolume(float value)
{
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ��������
	if (event)
	{
		event->setVolume(value);
	}
}

void SoundEvent::SetPitch(float value)
{
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ��������
	if (event)
	{
		event->setPitch(value);
	}
}

void SoundEvent::SetParameter(const std::string& name, float value)
{
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ���÷�Χ
	if (event)
	{
		event->setParameterValue(name.c_str(), value);
	}
}

bool SoundEvent::GetPaused() const
{
	bool retVal = false;
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ����״̬
	if (event)
	{
		event->getPaused(&retVal);
	}
	return retVal;
}

float SoundEvent::GetVolume() const
{
	float retVal = 0.0f;
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ��������
	if (event)
	{
		event->getVolume(&retVal);
	}
	return retVal;
}

float SoundEvent::GetPitch() const
{
	float retVal = 0.0f;
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ��������
	if (event)
	{
		event->getPitch(&retVal);
	}
	return retVal;
}

float SoundEvent::GetParameter(const std::string& name)
{
	float retVal = 0.0f;
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	//  ���ʷ�Χ
	if (event)
	{
		event->getParameterValue(name.c_str(), &retVal);
	}
	return retVal;
}

bool SoundEvent::Is3D() const
{
	bool retVal = false;
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		//  ��ȡ�¼�����
		FMOD::Studio::EventDescription* ed = nullptr;
		event->getDescription(&ed);
		if (ed)
		{
			//  �Ƿ�3d
			ed->is3D(&retVal);
		}
	}
	return retVal;
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

void SoundEvent::Set3DAttributes(const Matrix4& worldTrans)
{
	//  ��ȡ�¼�
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		//  ����3d����
		FMOD_3D_ATTRIBUTES attr;
		//  ������ǰ��������Ϊ�ռ�λ��
		attr.position = VecToFMOD(worldTrans.GetTranslation());
		//  ���������У���һ��ǰ����������ǰ
		attr.forward = VecToFMOD(worldTrans.GetXAxis());
		//  ������ǰ������������
		attr.up = VecToFMOD(worldTrans.GetZAxis());
		//  ���ٶ�����Ϊ�㣨���ʹ�ö�����ЧӦ�������������
		attr.velocity = { 0.0f, 0.0f, 0.0f };
		//  ����3d����
		event->set3DAttributes(&attr);
	}
}
