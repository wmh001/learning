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
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadData()
{
	//  ������ɫ������
	Actor* a = new Actor(this);
	//  ����λ��
	a->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
	//  ���ñ���
	a->SetScale(100.0f);
	//  ������Ԫ��
	Quaternion q(Vector3::UnitY, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
	a->SetRotation(q);
	//  �����������
	MeshComponent* mc = new MeshComponent(a);
	//  ��������
	mc->SetMesh(mRenderer->GetMesh("Assets/Cube.gpmesh"));
	//  ������ɫ����
	a = new Actor(this);
	//  ����λ��
	a->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	//  ���ñ���
	a->SetScale(3.0f);
	//  �����������
	mc = new MeshComponent(a);
	//  ��������
	mc->SetMesh(mRenderer->GetMesh("Assets/Sphere.gpmesh"));
	//  ��ʼ����
	const float start = -1250.0f;
	//  �ߴ�
	const float size = 250.0f;
	//  ��ǽ
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//  ����ƽ���ɫ
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
	//  ���û�����
	mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	//  ���ö����
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	//  ���÷���
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	//  �����������
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	//   ���þ��淴���
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	//  �������
	mCameraActor = new CameraActor(this);
	//  ������ɫ
	a = new Actor(this);
	//  ����λ��
	a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
	//  �����������
	SpriteComponent* sc = new SpriteComponent(a);
	//  ����ͼ��
	sc->SetTexture(mRenderer->GetTexture("Assets/HealthBar.png"));
	//  ������ɫ
	a = new Actor(this);
	//  ����λ��
	a->SetPosition(Vector3(375.0f, -275.0f, 0.0f));
	//  ���ñ���
	a->SetScale(0.75f);
	//  �����������
	sc = new SpriteComponent(a);
	//  ����ͼ��
	sc->SetTexture(mRenderer->GetTexture("Assets/Radar.png"));
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
	//  �ر���Ⱦ��
	if (mRenderer)
	{
		mRenderer->Shutdown();
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
