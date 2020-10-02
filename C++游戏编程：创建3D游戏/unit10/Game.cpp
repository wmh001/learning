#include "Game.h"
#include <algorithm>
#include "Renderer.h"
#include "Texture.h"
#include "AudioSystem.h"
#include "PhysWorld.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "FPSActor.h"
#include "PlaneActor.h"
#include "TargetActor.h"
#include "BallActor.h"

Game::Game()
	: mRenderer(nullptr)
	, mAudioSystem(nullptr)
	, mPhysWorld(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
	, mTicksCount(0)
	, mCrosshair(nullptr)
	, mFPSActor(nullptr)
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
	//  ������ɫ
	LoadData();
	//  ��¼ʱ��
	mTicksCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
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
			mIsRunning = false;
			break;
		//  ������ĳ����ʱ�����ᴥ��
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				HandleKeyPress(event.key.keysym.sym);
			}
			break;
	    //  ���������
		case SDL_MOUSEBUTTONDOWN:
			HandleKeyPress(event.button.button);
			break;
		default:
			break;
		}
	}
	//  ��������
	//  SDL_GetKeyboardState��ȡ����״̬
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//  ��Esc���˳�
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	//  ���벢���½�ɫ
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
}

void Game::HandleKeyPress(int key)
{
	switch (key)
	{
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
	case SDL_BUTTON_LEFT:
	{	
		//  ���
		mFPSActor->Shoot();
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
	//  ����ϵͳ����
	mAudioSystem->Update(deltaTime);
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadData()
{
	//  ����ǽ��ɫ
	Actor* a = nullptr;
	Quaternion q;
	//MeshComponent* mc = nullptr;
	//  �̵ذ�
	const float start = -1250.0f;
	//
	const float size = 250.0f;
	for (int i = 1; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//  ����ƽ���ɫ
			a = new PlaneActor(this);
			a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
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
	mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	//  ���ö����
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	//  ���÷���
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	//  �����������
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	//  ���þ��淴���
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	//  ����Ѫ��
	a = new Actor(this);
	//  ����λ��
	a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
	//  �����������
	SpriteComponent* sc = new SpriteComponent(a);
	//  ����ͼ��
	sc->SetTexture(mRenderer->GetTexture("Assets/HealthBar.png"));
	//  �����״�
	a = new Actor(this);
	//  ����λ��
	a->SetPosition(Vector3(-390.0f, 275.0f, 0.0f));
	//  ���ñ���
	a->SetScale(0.75f);
	//  �����������
	sc = new SpriteComponent(a);
	//  ����ͼ��
	sc->SetTexture(mRenderer->GetTexture("Assets/Radar.png"));
	//  ����׼�ǽ�ɫ
	a = new Actor(this);
	//  ���ñ���
	a->SetScale(2.0f);
	//  �����������
	mCrosshair = new SpriteComponent(a);
	//  ����ͼ��
	mCrosshair->SetTexture(mRenderer->GetTexture("Assets/Crosshair.png"));
	//  ��ʼ����
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
	//  �������ģʽ
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//  ����˶�ģʽ�»�ȡ�������
	SDL_GetRelativeMouseState(nullptr, nullptr);
	//  ����FPS�����ɫ
	mFPSActor = new FPSActor(this);
	//  ��������
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 0.0f, 100.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 0.0f, 400.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, -500.0f, 200.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 500.0f, 200.0f));
}

void Game::UnloadData()
{
	//  ɾ����ɫ
	//  ~Actorֻ���Ƴ��˽�ɫ
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	//  ɾ����Ⱦ��
	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void Game::Shutdown()
{
	//  ɾ��ͼ��
	UnloadData();
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
