#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "AIComponent.h"
#include "AIState.h"
#include "Grid.h"
#include "Enemy.h"

Game::Game() :mWindow(nullptr)
    , mRenderer(nullptr)
    , mIsRunning(true)
    , mUpdatingActors(false)
    , mTicksCount(0)
{

}

bool Game::Initialize()
{
	//  初始化视频子系统和音频子系统
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		//  输出字符
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//  创建窗口
	mWindow = SDL_CreateWindow("SDL4"  //  标题
		, 100  //  左上角的x坐标
		, 100  //  左上角的y坐标
		, 1024  //  窗口宽度
		, 768  //  窗口高度
		, 0);  //  窗口创建标志，0表示没有标志
		/*SDL_WINDOW_FULLSCREEN使用全屏模式，
		SDL_WINDOW_FULLSCREEN_DESKTOP在当前桌面分辨率下使用全屏模式，
		SDL_WINDOW_OPENGL为OpenGL库提供图形支持，
		SDL_WINDOW_RESIZABLE允许用户重调整窗口大小*/
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	//  创建渲染器，用于绘制图像
	mRenderer = SDL_CreateRenderer(mWindow  //  所属窗口
		, -1  //  指定使用哪个使用哪个图形驱动程序，只有一个窗口时默认为-1
		, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);  //  初始化参数标志
		//  使用加速渲染器和垂直同步法
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//  初始化SDL图像，IMG_INIT_PNG支持PNG，IMG_INIT_JPG支持JPEG，IMG_INIT_TIF支持TIFF
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	//  创建角色
	LoadData();
	//  记录时间
	mTicksCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		//  输入
		ProcessInput();
		//  更新
		UpdateGame();
		//  输出
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	//  定义输入事件
	SDL_Event event;
	//  按×退出
	//  SDL_PollEvent接收事件
	while (SDL_PollEvent(&event))
	{
		//  event.type包含接受的事件
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	//  按键输入
	//  SDL_GetKeyboardState获取键盘状态
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	//  按Esc键退出
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	//  按B建塔
	if (keyState[SDL_SCANCODE_B])
	{
		mGrid->BuildTower();
	}
	//  按V拆塔
	if (keyState[SDL_SCANCODE_V])
	{
		mGrid->DestroyTower();
	}
	//  鼠标输入
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	{
		mGrid->ProcessClick(x, y);
	}
	//  输入并更新角色
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	//  帧限制，保证帧之间时间间隔至少为16ms
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	//  计算时间增量
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//  保证时间增量不能太大以致短帧
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	//  保留本次时间
	mTicksCount = SDL_GetTicks();
	//  更新所有角色
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
	//  移动所有挂起角色到角色中
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();
	//  移动所有死亡角色到临时容器中
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	//  删除死亡角色
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{

	//  指定一种颜色
	SDL_SetRenderDrawColor(mRenderer  //  指定渲染器
		, 220  //  R
		, 220  //  G
		, 220  //  B
		, 255);  //  A
//  清除后台缓冲区为此种颜色
	SDL_RenderClear(mRenderer);
	//  绘制游戏场景
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}
	//  互换前后台缓冲区
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	//  
	mGrid = new Grid(this);
	//  测试AI组件
	//  Actor* a = new Actor(this);
	//  AIComponent* aic = new AIComponent(a);
	//  添加状态
	//  aic->RegisterState(new AIPatrol(aic));
	//  aic->RegisterState(new AIDeath(aic));
	//  aic->RegisterState(new AIAttack(aic));
	//  始于训逻状态
	//  aic->ChangeState("Patrol");
}

void Game::UnloadData()
{
	//  删除角色
	//  ~Actor只是移除了角色
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	//  摧毁图像
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	//  图像是否存在
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//  文件转换为封面
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}
		//  封面转换为图像
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		//  加入图像
		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::Shutdown()
{
	//  删除图像
	UnloadData();
	//  关闭IMG
	IMG_Quit();
	//  关闭渲染器
	SDL_DestroyRenderer(mRenderer);
	//  关闭窗口
	SDL_DestroyWindow(mWindow);
	//  关闭SDL库
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	//  需要更新的角色被挂起，不需要更新的角色加入
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	//  是否在挂起角色的容器中
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//  转换到容器尾并弹出（避免删除副本）
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	//  是否在角色容器中
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//  转换到容器尾并弹出（避免删除副本）
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	//  在有序容器中寻找插入点
	//  第一个元素的插入顺序更大
	int myDrawOrder = sprite->GetDrawOrder();
	//  寻找位置
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	//  插入元素
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	//  不能交换，不知道顺序
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

Enemy* Game::GetNearestEnemy(const Vector2& pos)
{
	//  定义敌人
	Enemy* best = nullptr;
	//  判断最近敌人
	if (mEnemies.size() > 0)
	{
		//  初始化为第一个敌人
		best = mEnemies[0];
		//  计算第一个敌人距离的平方
		float bestDistSq = (pos - mEnemies[0]->GetPosition()).LengthSq();
		for (size_t i = 1; i < mEnemies.size(); i++)
		{
			//  计算第i+1个敌人距离的平方
			float newDistSq = (pos - mEnemies[i]->GetPosition()).LengthSq();
			//  比较大小确定最佳
			if (newDistSq < bestDistSq)
			{
				bestDistSq = newDistSq;
				best = mEnemies[i];
			}
		}
	}
	return best;
}