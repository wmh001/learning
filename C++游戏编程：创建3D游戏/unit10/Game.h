#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"

class Game
{
public:
	Game();
	//  初始化
	bool Initialize();
	//  循环
	void RunLoop();
	//  结束
	void Shutdown();
	//  加入角色
	void AddActor(class Actor* actor);
	//  移除角色
	void RemoveActor(class Actor* actor);
	//  访问渲染器
	class Renderer* GetRenderer() { return mRenderer; }
	//  访问声音系统
	class AudioSystem* GetAudioSystem() { return mAudioSystem; }
	//
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }
	//
	void AddPlane(class PlaneActor* plane);
	//
	void RemovePlane(class PlaneActor* plane);
	//
	std::vector<class PlaneActor*>& GetPlanes() { return mPlanes; }
private:
	//  输入处理
	void ProcessInput();
	//  拟手柄处理
	void HandleKeyPress(int key);
	//  更新游戏
	void UpdateGame();
	//  输出图像
	void GenerateOutput();
	//  绘制图像
	void LoadData();
	//  删除图像
	void UnloadData();
	//  游戏中所有角色的容器
	std::vector<class Actor*> mActors;
	//  挂起角色容器
	std::vector<class Actor*> mPendingActors;
	//  渲染器
	class Renderer* mRenderer;
	//  声音系统
	class AudioSystem* mAudioSystem;
	//
	class PhysWorld* mPhysWorld;
	//  记录从调用SDL_Init函数开始的毫秒数
	Uint32 mTicksCount;
	//  是否应该继续运行
	bool mIsRunning;
	//  是否正在更新角色
	bool mUpdatingActors;
	//
	std::vector<class PlaneActor*> mPlanes;
	//  FPS相机
	class FPSActor* mFPSActor;
	//  准星
	class SpriteComponent* mCrosshair;
	//  声音事件
	SoundEvent mMusicEvent;
};

