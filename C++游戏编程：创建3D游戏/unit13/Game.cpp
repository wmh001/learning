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
	//  ��ʼ����Ƶ��ϵͳ����Ƶ��ϵͳ
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		//  ����ַ�
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//  ������Ⱦ��
	mRenderer = new Renderer(this);
	//  ʧ�ܴ���
	if (!mRenderer->Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}
	//  ��������ϵͳ
	mAudioSystem = new AudioSystem(this);
	//  ʧ�ܴ���
	if (!mAudioSystem->Initialize())
	{
		SDL_Log("Failed to initialize audio system");
		mAudioSystem->Shutdown();
		delete mAudioSystem;
		mAudioSystem = nullptr;
		return false;
	}
	//  ������ײ
	mPhysWorld = new PhysWorld(this);
	//  �����ʼ��
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}
	//  ������ɫ
	LoadData();
	//  ��¼ʱ��
	mTicksCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop()
{
	while (mGameState != EQuit)
	{
		//  ����
		ProcessInput();
		//  ����
		UpdateGame();
		//  ���
		GenerateOutput();
	}
}

void Game::AddPlane(PlaneActor* plane)
{
	//  ǽ������
	mPlanes.emplace_back(plane);
}

void Game::RemovePlane(PlaneActor* plane)
{
	//  ǽ�Ƴ�����
	auto iter = std::find(mPlanes.begin(), mPlanes.end(), plane);
	mPlanes.erase(iter);
}

void Game::ProcessInput()
{
	//  ���������¼�
	SDL_Event event;
	//  �����˳�
	//  SDL_PollEvent�����¼�
	while (SDL_PollEvent(&event))
	{
		//  event.type�������ܵ��¼�
		switch (event.type)
		{
		case SDL_QUIT:
			mGameState = EQuit;
			break;
		//  ������ĳ����ʱ�����ᴥ��
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				//  ��Ϸ��������
				if (mGameState == EGameplay)
				{
					HandleKeyPress(event.key.keysym.sym);
				}
				//  �û�������Ļ����
				else if (!mUIStack.empty())
				{
					mUIStack.back()->HandleKeyPress(event.key.keysym.sym);
				}
			}
			break;
	    //  ���������
		case SDL_MOUSEBUTTONDOWN:
			//  ��Ϸ��������
			if (mGameState == EGameplay)
			{
				HandleKeyPress(event.button.button);
			}
			//  �û�������Ļ����
			else if (!mUIStack.empty())
			{
				mUIStack.back()->HandleKeyPress(event.button.button);
			}
			break;
		default:
			break;
		}
	}
	//  ��������
	//  SDL_GetKeyboardState��ȡ����״̬
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//  ��Ϸ��������
	if (mGameState == EGameplay)
	{
		//  ���½�ɫ
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::EActive)
			{
				actor->ProcessInput(state);
			}
		}
	}
	//  �û�������Ļ����
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
		//  ������ͣ�˵�
		new PauseMenu(this);
		break;
	case '-':
	{
		//  ��������
		float volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Max(0.0f, volume - 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	}
	case '=':
	{
		//  ��������
		float volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Min(1.0f, volume + 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	}
	case '1':
	{
		//  ����Ӣ��
		LoadText("Assets/English.gptext");
		break;
	}
	case '2':
	{
		//  ���ض���
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
	//  ֡���ƣ���֤֮֡��ʱ��������Ϊ16ms
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	//  ����ʱ������
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//  ��֤ʱ����������̫�����¶�֡
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	//  ��������ʱ��
	mTicksCount = SDL_GetTicks();
	if (mGameState == EGameplay)
	{
		//  �������н�ɫ
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;
		//  �ƶ����й����ɫ����ɫ��
		for (auto pending : mPendingActors)
		{
			//  ��������任����
			pending->ComputeWorldTransform();
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();
		//  �ƶ�����������ɫ����ʱ������
		std::vector<Actor*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}
		//  ɾ��������ɫ
		for (auto actor : deadActors)
		{
			delete actor;
		}
	}
	//  ����ϵͳ����
	mAudioSystem->Update(deltaTime);
	//  ���»�Ծ״̬�û�������Ļջ
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}
	//  ɾ���ر�״̬�û�������Ļ
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
	//  �����ļ�������ӳ��
	LoadText("Assets/English.gptext");
	//  ����ǽ��ɫ
	Actor* a = nullptr;
	Quaternion q;
	//MeshComponent* mc = nullptr;
	//  �̵ذ�
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//  ����ƽ���ɫ
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
	//  ��ǽ
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
	//  ���û�����
	mRenderer->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	//  ���ö����
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	//  ���÷���
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	//  �����������
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	//  ���þ��淴���
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	//  ����ƽ����ʾ��
	mHUD = new HUD(this);
	//  ��ʼ����
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
	//  �������ģʽ
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//  ����˶�ģʽ�»�ȡ�������
	SDL_GetRelativeMouseState(nullptr, nullptr);
	//  ����FPS�����ɫ
	mFollowActor = new FollowActor(this);
	//  ��������
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
	//  ɾ����ɫ
	//  ~Actorֻ���Ƴ��˽�ɫ
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	//  ɾ���û�������Ļջ
	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}
	//  ɾ����Ⱦ��
	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
	//  ɾ������
	for (auto f : mFonts)
	{
		f.second->Unload();
		delete f.second;
	}
	//  ɾ����Ƥ
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	//  ɾ������
	for (auto a : mAnims)
	{
		delete a.second;
	}
}

void Game::Shutdown()
{
	//  ɾ������
	UnloadData();
	//  �ر������
	TTF_Quit();
	//  ɾ����ײ
	delete mPhysWorld;
	//  �ر���Ⱦ��
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
	//  ɾ����Ƶ
	if (mAudioSystem)
	{
		mAudioSystem->Shutdown();
	}
	//  �ر�SDL��
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	//  ��Ҫ���µĽ�ɫ�����𣬲���Ҫ���µĽ�ɫ����
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
	//  �Ƿ��ڹ����ɫ��������
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//  ת��������β������������ɾ��������
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	//  �Ƿ��ڽ�ɫ������
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//  ת��������β������������ɾ��������
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::PushUI(UIScreen* screen)
{
	//  ��������
	mUIStack.emplace_back(screen);
}

Font* Game::GetFont(const std::string& fileName)
{
	//  Ѱ������
	auto iter = mFonts.find(fileName);
	//  �ҵ�
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	//  δ�ҵ�
	else
	{
		//  ��������
		Font* font = new Font(this);
		if (font->Load(fileName))
		{
			mFonts.emplace(fileName, font);
		}
		//  ʧ�ܴ���
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
	//  ���ӳ��
	mText.clear();
	//  ���ļ�
	std::ifstream file(fileName);
	//  ʧ�ܴ���
	if (!file.is_open())
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}
	//  ��ȡ�ļ�
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	//  rapidJSON���ļ�
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	//  ʧ�ܴ���
	if (!doc.IsObject())
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}
	//  ����ӳ��
	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin(); itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			//  ����ӳ��
			mText.emplace(itr->name.GetString(), itr->value.GetString());
		}
	}
}

const std::string& Game::GetText(const std::string& key)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	//  ��ӳ����Ѱ���ַ���
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
	//  Ѱ����Ƥ
	auto iter = mSkeletons.find(fileName);
	//  �ҵ�������
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	//  ������Ƥ
	else
	{
		Skeleton* sk = new Skeleton();
		//  ����
		if (sk->Load(fileName))
		{
			mSkeletons.emplace(fileName, sk);
		}
		//  ʧ�ܴ���
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
	//  Ѱ�Ҷ���
	auto iter = mAnims.find(fileName);
	//  �ҵ�������
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	//  �����¶���
	else
	{
		Animation* anim = new Animation();
		//  ����
		if (anim->Load(fileName))
		{
			mAnims.emplace(fileName, anim);
		}
		//  ʧ�ܴ���
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}
