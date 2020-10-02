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
	//  ��ʼ����Ƶ��ϵͳ����Ƶ��ϵͳ
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		//  ����ַ�
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//  ��������
	mWindow = SDL_CreateWindow("SDL4"  //  ����
		, 100  //  ���Ͻǵ�x����
		, 100  //  ���Ͻǵ�y����
		, 1024  //  ���ڿ��
		, 768  //  ���ڸ߶�
		, 0);  //  ���ڴ�����־��0��ʾû�б�־
		/*SDL_WINDOW_FULLSCREENʹ��ȫ��ģʽ��
		SDL_WINDOW_FULLSCREEN_DESKTOP�ڵ�ǰ����ֱ�����ʹ��ȫ��ģʽ��
		SDL_WINDOW_OPENGLΪOpenGL���ṩͼ��֧�֣�
		SDL_WINDOW_RESIZABLE�����û��ص������ڴ�С*/
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	//  ������Ⱦ�������ڻ���ͼ��
	mRenderer = SDL_CreateRenderer(mWindow  //  ��������
		, -1  //  ָ��ʹ���ĸ�ʹ���ĸ�ͼ����������ֻ��һ������ʱĬ��Ϊ-1
		, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);  //  ��ʼ��������־
		//  ʹ�ü�����Ⱦ���ʹ�ֱͬ����
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//  ��ʼ��SDLͼ��IMG_INIT_PNG֧��PNG��IMG_INIT_JPG֧��JPEG��IMG_INIT_TIF֧��TIFF
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
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
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	//  ��Esc���˳�
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	//  ��B����
	if (keyState[SDL_SCANCODE_B])
	{
		mGrid->BuildTower();
	}
	//  ��V����
	if (keyState[SDL_SCANCODE_V])
	{
		mGrid->DestroyTower();
	}
	//  �������
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	{
		mGrid->ProcessClick(x, y);
	}
	//  ���벢���½�ɫ
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
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

	//  ָ��һ����ɫ
	SDL_SetRenderDrawColor(mRenderer  //  ָ����Ⱦ��
		, 220  //  R
		, 220  //  G
		, 220  //  B
		, 255);  //  A
//  �����̨������Ϊ������ɫ
	SDL_RenderClear(mRenderer);
	//  ������Ϸ����
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}
	//  ����ǰ��̨������
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	//  
	mGrid = new Grid(this);
	//  ����AI���
	//  Actor* a = new Actor(this);
	//  AIComponent* aic = new AIComponent(a);
	//  ���״̬
	//  aic->RegisterState(new AIPatrol(aic));
	//  aic->RegisterState(new AIDeath(aic));
	//  aic->RegisterState(new AIAttack(aic));
	//  ʼ��ѵ��״̬
	//  aic->ChangeState("Patrol");
}

void Game::UnloadData()
{
	//  ɾ����ɫ
	//  ~Actorֻ���Ƴ��˽�ɫ
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	//  �ݻ�ͼ��
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	//  ͼ���Ƿ����
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//  �ļ�ת��Ϊ����
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}
		//  ����ת��Ϊͼ��
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		//  ����ͼ��
		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::Shutdown()
{
	//  ɾ��ͼ��
	UnloadData();
	//  �ر�IMG
	IMG_Quit();
	//  �ر���Ⱦ��
	SDL_DestroyRenderer(mRenderer);
	//  �رմ���
	SDL_DestroyWindow(mWindow);
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

void Game::AddSprite(SpriteComponent* sprite)
{
	//  ������������Ѱ�Ҳ����
	//  ��һ��Ԫ�صĲ���˳�����
	int myDrawOrder = sprite->GetDrawOrder();
	//  Ѱ��λ��
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	//  ����Ԫ��
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	//  ���ܽ�������֪��˳��
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

Enemy* Game::GetNearestEnemy(const Vector2& pos)
{
	//  �������
	Enemy* best = nullptr;
	//  �ж��������
	if (mEnemies.size() > 0)
	{
		//  ��ʼ��Ϊ��һ������
		best = mEnemies[0];
		//  �����һ�����˾����ƽ��
		float bestDistSq = (pos - mEnemies[0]->GetPosition()).LengthSq();
		for (size_t i = 1; i < mEnemies.size(); i++)
		{
			//  �����i+1�����˾����ƽ��
			float newDistSq = (pos - mEnemies[i]->GetPosition()).LengthSq();
			//  �Ƚϴ�Сȷ�����
			if (newDistSq < bestDistSq)
			{
				bestDistSq = newDistSq;
				best = mEnemies[i];
			}
		}
	}
	return best;
}