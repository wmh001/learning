#include "Game.h"
#include <algorithm>
#include "Renderer.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "CameraActor.h"
#include "PlaneActor.h"

Game::Game()
	: mRenderer(nullptr)
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
	//  创建渲染器
	mRenderer = new Renderer(this);
	//  失败处理
	if (!mRenderer->Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
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
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//  按Esc键退出
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	//  输入并更新角色
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
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
		//  计算世界变换矩阵
		pending->ComputeWorldTransform();
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
	mRenderer->Draw();
}

void Game::LoadData()
{
	//  创建角色立方体
	Actor* a = new Actor(this);
	//  设置位置
	a->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
	//  设置比例
	a->SetScale(100.0f);
	//  设置四元数
	Quaternion q(Vector3::UnitY, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
	a->SetRotation(q);
	//  创建网格组件
	MeshComponent* mc = new MeshComponent(a);
	//  设置网格
	mc->SetMesh(mRenderer->GetMesh("Assets/Cube.gpmesh"));
	//  创建角色球体
	a = new Actor(this);
	//  设置位置
	a->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	//  设置比例
	a->SetScale(3.0f);
	//  创建网格组件
	mc = new MeshComponent(a);
	//  设置网格
	mc->SetMesh(mRenderer->GetMesh("Assets/Sphere.gpmesh"));
	//  起始坐标
	const float start = -1250.0f;
	//  尺寸
	const float size = 250.0f;
	//  铺墙
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//  创建平面角色
			a = new PlaneActor(this);
			a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}
	q = Quaternion(Vector3::UnitX, Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, start - size, 0.0f));
		a->SetRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
		a->SetRotation(q);
	}
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
		a->SetRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
		a->SetRotation(q);
	}
	//  设置环境光
	mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	//  设置定向光
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	//  设置方向
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	//  设置漫反射光
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	//   设置镜面反射光
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	//  创建相近
	mCameraActor = new CameraActor(this);
	//  创建角色
	a = new Actor(this);
	//  设置位置
	a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
	//  创建精灵组件
	SpriteComponent* sc = new SpriteComponent(a);
	//  设置图像
	sc->SetTexture(mRenderer->GetTexture("Assets/HealthBar.png"));
	//  创建角色
	a = new Actor(this);
	//  设置位置
	a->SetPosition(Vector3(375.0f, -275.0f, 0.0f));
	//  设置比例
	a->SetScale(0.75f);
	//  创建精灵组件
	sc = new SpriteComponent(a);
	//  设置图像
	sc->SetTexture(mRenderer->GetTexture("Assets/Radar.png"));
}

void Game::UnloadData()
{
	//  删除角色
	//  ~Actor只是移除了角色
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	//  删除渲染器
	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void Game::Shutdown()
{
	//  删除图像
	UnloadData();
	//  关闭渲染器
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
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
