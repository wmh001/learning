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
	//  更新
	void Update(float deltaTime) override;
	//  更新世界变换矩阵
	void OnUpdateWorldTransform() override;
	//  播放事件
	SoundEvent PlayEvent(const std::string& name);
	//  停止所有事件
	void StopAllEvents();
private:
	//  2d事件的容器
	std::vector<SoundEvent> mEvents2D;
	//  3d事件的容器
	std::vector<SoundEvent> mEvents3D;
};

