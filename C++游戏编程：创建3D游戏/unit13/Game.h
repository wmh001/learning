#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"
#include <SDL_types.h>

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
	//  访问碰撞系统
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }
	//  访问平视显示器
	class HUD* GetHUD() { return mHUD; }
	//  访问用户界面屏幕栈
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	//  入栈
	void PushUI(class UIScreen* screen);
	//  访问玩家
	class FollowActor* GetPlayer() { return mFollowActor; }
	//  游戏状态
	enum GameState
	{
		EGameplay,  //  运行
		EPaused,  //  暂停
		EQuit  //  退出
	};
	//  访问游戏状态
	GameState GetState() const { return mGameState; }
	//  修改游戏状态
	void SetState(GameState state) { mGameState = state; }
	//  访问字体
	class Font* GetFont(const std::string& fileName);
	//  解析gptext文件并添加到映射中
	void LoadText(const std::string& fileName);
	//  根据键值访问字符串
	const std::string& GetText(const std::string& key);
	//  根据键值访问蒙皮骨骼
	class Skeleton* GetSkeleton(const std::string& fileName);
	//  根据键值访问动画数据
	class Animation* GetAnimation(const std::string& fileName);
	//  添加墙
	void AddPlane(class PlaneActor* plane);
	//  移除墙
	void RemovePlane(class PlaneActor* plane);
	//  访问墙
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
	//  加载数据
	void LoadData();
	//  删除数据
	void UnloadData();
	//  游戏中所有角色的容器
	std::vector<class Actor*> mActors;
	//  用户界面屏幕栈
	std::vector<class UIScreen*> mUIStack;
	//  文件名到字体的映射
	std::unordered_map<std::string, class Font*> mFonts;
	//  文件名到蒙皮骨骼的映射
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	//  文件名到动画数据的映射
	std::unordered_map<std::string, class Animation*> mAnims;
	//  英文字符串到本地字符串的映射
	std::unordered_map<std::string, std::string> mText;
	//  挂起角色容器
	std::vector<class Actor*> mPendingActors;
	//  渲染器
	class Renderer* mRenderer;
	//  声音系统
	class AudioSystem* mAudioSystem;
	//  碰撞系统
	class PhysWorld* mPhysWorld;
	//  平视显示器
	class HUD* mHUD;
	//  记录从调用SDL_Init函数开始的毫秒数
	Uint32 mTicksCount;
	//  游戏状态
	GameState mGameState;
	//  是否正在更新角色
	bool mUpdatingActors;
	//  墙容器
	std::vector<class PlaneActor*> mPlanes;
	//  跟随相机
	class FollowActor* mFollowActor;
	//  准星
	class SpriteComponent* mCrosshair;
	//  声音事件
	SoundEvent mMusicEvent;
};

