#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	//  构造函数
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
private:
	//  输入处理
	void ProcessInput();
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
	//  记录从调用SDL_Init函数开始的毫秒数
	Uint32 mTicksCount;
	//  是否应该继续运行
	bool mIsRunning;
	//  是否正在更新角色
	bool mUpdatingActors;
	//
	class CameraActor* mCameraActor;
};

