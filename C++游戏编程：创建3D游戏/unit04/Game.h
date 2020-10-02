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
	//  加入精灵
	void AddSprite(class SpriteComponent* sprite);
	//  移除精灵
	void RemoveSprite(class SpriteComponent* sprite);
	//  得到图像
	SDL_Texture* GetTexture(const std::string& fileName);
	class Grid* GetGrid() { return mGrid; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	std::vector<class Tower*>& GetTowers() { return mTowers; }
	class Enemy* GetNearestEnemy(const Vector2& pos);
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
	//  图像的容器
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	//  游戏中所有角色的容器
	std::vector<class Actor*> mActors;
	//  挂起角色容器
	std::vector<class Actor*> mPendingActors;
	//  精灵组件的容器
	std::vector<class SpriteComponent*> mSprites;
	//  创建窗口
	SDL_Window* mWindow;
	//  创建渲染器
	SDL_Renderer* mRenderer;
	//  记录从调用SDL_Init函数开始的毫秒数
	Uint32 mTicksCount;
	//  是否应该继续运行
	bool mIsRunning;
	//  是否正在更新角色
	bool mUpdatingActors;
	//  敌人容器
	std::vector<class Enemy*> mEnemies;
	//  塔容器
	std::vector<class Tower*> mTowers;
	//  棋盘
	class Grid* mGrid;
	//  下一个敌人
	float mNextEnemy;
};

