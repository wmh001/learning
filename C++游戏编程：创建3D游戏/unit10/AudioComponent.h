#pragma once
#include "Component.h"
#include "SoundEvent.h"
#include <vector>
#include <string>

class AudioComponent :
    public Component
{
public:
	AudioComponent(class Actor* owner, int updateOrder = 200);
	~AudioComponent();
	//  ����
	void Update(float deltaTime) override;
	//  ��������任����
	void OnUpdateWorldTransform() override;
	//  �����¼�
	SoundEvent PlayEvent(const std::string& name);
	//  ֹͣ�����¼�
	void StopAllEvents();
private:
	//  2d�¼�������
	std::vector<SoundEvent> mEvents2D;
	//  3d�¼�������
	std::vector<SoundEvent> mEvents3D;
};

