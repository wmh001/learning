#include "Game.h"
#include <algorithm>
#include "Renderer.h"
#include "Texture.h"
#include "AudioSystem.h"
#include "PhysWorld.h"
#include "Actor.h"
#include "UIScreen.h"
#include "HUD.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "FollowActor.h"
#include "PlaneActor.h"
#include "TargetActor.h"
#include "BallActor.h"
#include "PauseMenu.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Font.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include "Skeleton.h"
#include "Animation.h"
#include "PointLightComponent.h"

Game::Game()
	: mRenderer(nullptr)
	, mAudioSystem(nullptr)
	, mPhysWorld(nullptr)
	, mUpdatingActors(false)
	, mTicksCount(0)
	, mCrosshair(nullptr)
	, mFollowActor(nullptr)
	, mGameState(EGameplay)
	, mHUD(nullptr)
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
	//  创建声音系统
	mAudioSystem = new AudioSystem(this);
	//  失败处理
	if (!mAudioSystem->Initialize())
	{
		SDL_Log("Failed to initialize audio system");
		mAudioSystem->Shutdown();
		delete mAudioSystem;
		mAudioSystem = nullptr;
		return false;
	}
	//  创建碰撞
	mPhysWorld = new PhysWorld(this);
	//  字体初始化
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
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
	while (mGameState != EQuit)
	{
		//  输入
		ProcessInput();
		//  更新
		UpdateGame();
		//  输出
		GenerateOutput();
	}
}

void Game::AddPlane(PlaneActor* plane)
{
	//  墙入容器
	mPlanes.emplace_back(plane);
}

void Game::RemovePlane(PlaneActor* plane)
{
	//  墙移除容器
	auto iter = std::find(mPlanes.begin(), mPlanes.end(), plane);
	mPlanes.erase(iter);
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
			mGameState = EQuit;
			break;
		//  当按下某个键时，它会触发
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				//  游戏世界输入
				if (mGameState == EGameplay)
				{
					HandleKeyPress(event.key.keysym.sym);
				}
				//  用户界面屏幕输入
				else if (!mUIStack.empty())
				{
					mUIStack.back()->HandleKeyPress(event.key.keysym.sym);
				}
			}
			break;
	    //  鼠标点击反射
		case SDL_MOUSEBUTTONDOWN:
			//  游戏世界输入
			if (mGameState == EGameplay)
			{
				HandleKeyPress(event.button.button);
			}
			//  用户界面屏幕输入
			else if (!mUIStack.empty())
			{
				mUIStack.back()->HandleKeyPress(event.button.button);
			}
			break;
		default:
			break;
		}
	}
	//  按键输入
	//  SDL_GetKeyboardState获取键盘状态
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//  游戏世界输入
	if (mGameState == EGameplay)
	{
		//  更新角色
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::EActive)
			{
				actor->ProcessInput(state);
			}
		}
	}
	//  用户界面屏幕输入
	else if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}
}

void Game::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		//  创建暂停菜单
		new PauseMenu(this);
		break;
	case '-':
	{
		//  降低音量
		float volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Max(0.0f, volume - 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	}
	case '=':
	{
		//  增加音量
		float volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Min(1.0f, volume + 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	}
	case '1':
	{
		//  加载英文
		LoadText("Assets/English.gptext");
		break;
	}
	case '2':
	{
		//  加载俄文
		LoadText("Assets/Russian.gptext");
		break;
	}
	case SDL_BUTTON_LEFT:
	{
		break;
	}
	default:
		break;
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
	if (mGameState == EGameplay)
	{
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
	//  声音系统更新
	mAudioSystem->Update(deltaTime);
	//  更新活跃状态用户界面屏幕栈
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}
	//  删除关闭状态用户界面屏幕
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::EClosing)
		{
			delete* iter;
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadData()
{
	//  解析文件，进入映射
	LoadText("Assets/English.gptext");
	//  创建墙角色
	Actor* a = nullptr;
	Quaternion q;
	//MeshComponent* mc = nullptr;
	//  铺地板
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//  创建平面角色
			a = new PlaneActor(this);
			//
			Vector3 pos = Vector3(start + i * size, start + j * size, -100.0f);
			//
			a->SetPosition(pos);
			//
			a = new Actor(this);
			//
			pos.z += 100.0f;
			//
			a->SetPosition(pos);
			//
			PointLightComponent* p = new PointLightComponent(a);
			//
			Vector3 color;
			//
			switch ((i + j) % 5)
			{
			case 0:
				//
				color = Color::Green;
				break;
			case 1:
				//
				color = Color::Blue;
				break;
			case 2:
				//
				color = Color::Red;
				break;
			case 3:
				//
				color = Color::Yellow;
				break;
			case 4:
				//
				color = Color::LightPink;
				break;
			}
			//
			p->mDiffuseColor = color;
			//
			p->mInnerRadius = 100.0f;
			//
			p->mOuterRadius = 200.0f;
		}
	}
	//  铺墙
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
	mRenderer->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	//  设置定向光
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	//  设置方向
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	//  设置漫反射光
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	//  设置镜面反射光
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	//  创建平视显示器
	mHUD = new HUD(this);
	//  初始音乐
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
	//  启用相对模式
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//  相对运动模式下获取鼠标坐标
	SDL_GetRelativeMouseState(nullptr, nullptr);
	//  创建FPS相机角色
	mFollowActor = new FollowActor(this);
	//  创建靶子
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 0.0f, 100.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 0.0f, 400.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, -500.0f, 200.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 500.0f, 200.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(0.0f, -1450.0f, 200.0f));
	a->SetRotation(Quaternion(Vector3::UnitZ, Math::PiOver2));
	a = new TargetActor(this);
	a->SetPosition(Vector3(0.0f, 1450.0f, 200.0f));
	a->SetRotation(Quaternion(Vector3::UnitZ, -Math::PiOver2));
}

void Game::UnloadData()
{
	//  删除角色
	//  ~Actor只是移除了角色
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	//  删除用户界面屏幕栈
	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}
	//  删除渲染器
	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
	//  删除字体
	for (auto f : mFonts)
	{
		f.second->Unload();
		delete f.second;
	}
	//  删除蒙皮
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	//  删除动画
	for (auto a : mAnims)
	{
		delete a.second;
	}
}

void Game::Shutdown()
{
	//  删除数据
	UnloadData();
	//  关闭字体库
	TTF_Quit();
	//  删除碰撞
	delete mPhysWorld;
	//  关闭渲染器
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
	//  删除音频
	if (mAudioSystem)
	{
		mAudioSystem->Shutdown();
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

void Game::PushUI(UIScreen* screen)
{
	//  进入容器
	mUIStack.emplace_back(screen);
}

Font* Game::GetFont(const std::string& fileName)
{
	//  寻找字体
	auto iter = mFonts.find(fileName);
	//  找到
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	//  未找到
	else
	{
		//  创建字体
		Font* font = new Font(this);
		if (font->Load(fileName))
		{
			mFonts.emplace(fileName, font);
		}
		//  失败处理
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}

void Game::LoadText(const std::string& fileName)
{
	//  清除映射
	mText.clear();
	//  打开文件
	std::ifstream file(fileName);
	//  失败处理
	if (!file.is_open())
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}
	//  读取文件
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	//  rapidJSON打开文件
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	//  失败处理
	if (!doc.IsObject())
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}
	//  构建映射
	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin(); itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			//  进入映射
			mText.emplace(itr->name.GetString(), itr->value.GetString());
		}
	}
}

const std::string& Game::GetText(const std::string& key)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	//  在映射中寻找字符串
	auto iter = mText.find(key);
	if (iter != mText.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}

Skeleton* Game::GetSkeleton(const std::string& fileName)
{
	//  寻找蒙皮
	auto iter = mSkeletons.find(fileName);
	//  找到并返回
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	//  创建蒙皮
	else
	{
		Skeleton* sk = new Skeleton();
		//  加载
		if (sk->Load(fileName))
		{
			mSkeletons.emplace(fileName, sk);
		}
		//  失败处理
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

Animation* Game::GetAnimation(const std::string& fileName)
{
	//  寻找动画
	auto iter = mAnims.find(fileName);
	//  找到并返回
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	//  创建新动画
	else
	{
		Animation* anim = new Animation();
		//  加载
		if (anim->Load(fileName))
		{
			mAnims.emplace(fileName, anim);
		}
		//  失败处理
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}
