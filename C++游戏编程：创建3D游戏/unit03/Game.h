#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

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

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	//  得到纹理
	SDL_Texture* GetTexture(const std::string& fileName);
	//  游戏特性（加入/移除陨石）
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	//  得到陨石容器
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
private:
	//  输入处理
	void ProcessInput();
	//  更新游戏
	void UpdateGame();
	//  输出图像
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//  游戏中所有角色的容器
	std::vector<class Actor*> mActors;
	//  挂起角色容器
	std::vector<class Actor*> mPendingActors;
	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;
	//  创建窗口
	SDL_Window* mWindow;
	//  创建渲染器
	SDL_Renderer* mRenderer;
	//  记录从调用SDL_Init函数开始的毫秒数
	Uint32 mTicksCount;
	//  是否应该继续运行
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	//  飞船
	class Ship* mShip;
	//  陨石的容器
	std::vector<class Asteroid*> mAsteroids;
};

