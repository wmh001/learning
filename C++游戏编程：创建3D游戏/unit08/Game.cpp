#include "Game.h"
#include <glew.h>
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"
#include "InputSystem.h"

Game::Game()
	: mWindow(nullptr)
    , mSpriteShader(nullptr)
	, mInputSystem(nullptr)
	, mShip(nullptr)
	, mSpriteVerts(nullptr)
    , mIsRunning(true)
    , mUpdatingActors(false)
    , mTicksCount(0)
{

}

bool Game::Initialize()
{
	//  ��ʼ����Ƶ��ϵͳ����Ƶ��ϵͳ�Ϳ�������ϵͳ
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		//  ����ַ�
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//  ����opengl����
	/*SDL_GL_SetAttribute(
	    SDL_GLattr attr,
		int value
	);*/
	//  opengl��������
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//  ���ð汾3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//  ����4��8λRGBAͨ��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//  ����˫������
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//  ʹ��GPU��������opengl
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//  ��������
	mWindow = SDL_CreateWindow("SDL5"  //  ����
		, 100  //  ���Ͻǵ�x����
		, 100  //  ���Ͻǵ�y����
		, 1024  //  ���ڿ��
		, 768  //  ���ڸ߶�
		, SDL_WINDOW_OPENGL);  //  ���ڴ�����־��0��ʾû�б�־
		/*SDL_WINDOW_FULLSCREENʹ��ȫ��ģʽ��
		SDL_WINDOW_FULLSCREEN_DESKTOP�ڵ�ǰ����ֱ�����ʹ��ȫ��ģʽ��
		SDL_WINDOW_OPENGLΪOpenGL���ṩͼ��֧�֣�
		SDL_WINDOW_RESIZABLE�����û��ص������ڴ�С*/
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	//
	mInputSystem = new InputSystem();
	//
	if (!mInputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}
	//  ����opengl������
	mContext = SDL_GL_CreateContext(mWindow);
	//  ��ʼ��GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	//  �����׳�
	glGetError();
	//  ������ɫ��
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	//  ���������λ�����
	CreateSpriteVerts();
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
	//  ׼�������¼�
	mInputSystem->PrepareForUpdate();
	//  ���������¼�
	SDL_Event event;
	//  SDL_PollEvent�����¼�
	while (SDL_PollEvent(&event))
	{
		//  event.type�������ܵ��¼�
		switch (event.type)
		{
	    //  �����˳�
		case SDL_QUIT:
			mIsRunning = false;
			break;
		//  �����ִ���
		case SDL_MOUSEWHEEL:
			mInputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}
	//  ����ϵͳ����
	mInputSystem->Update();
	//  ��ȡ״̬
	const InputState& state = mInputSystem->GetState();
	//  Esc���ͷ�ʱ�˳�
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EReleased)
	{
		mIsRunning = false;
	}
	//  ���벢���½�ɫ
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
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
	//  ָ��һ����ɫ����ɫ��
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	//  �����ɫ������
	glClear(GL_COLOR_BUFFER_BIT);
	//  ����alpha��Ϲ���
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA  //  ��Դ����
		, GL_ONE_MINUS_SRC_ALPHA);  //  Ŀ������
	//  ������ɫ��
	mSpriteShader->SetActive();
	//  ���������
	mSpriteVerts->SetActive();
	//  ����ͼ��
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}
	//  ����ǰ��̨������
	SDL_GL_SwapWindow(mWindow);
}


bool Game::LoadShaders()
{
	//  ������ɫ��
	mSpriteShader = new Shader();
	//  ������ɫ��Դ�ļ�
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	//  ����
	mSpriteShader->SetActive();
	//  ��������ͼͶӰ����
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	//  ����
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void Game::CreateSpriteVerts()
{
	//  �������㻺������������������
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, //  ����
		 0.5f,  0.5f, 0.f, 1.f, 0.f, //  ����
		 0.5f, -0.5f, 0.f, 1.f, 1.f, //  ����
		-0.5f, -0.5f, 0.f, 0.f, 1.f  //  ����
	};
	//  ��������������
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	//  ������������
	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Game::LoadData()
{
	//  �����ɴ�
	mShip = new Ship(this);
	//  ��ʼ���Ƕ�
	mShip->SetRotation(Math::PiOver2);
	//  ������ʯ
	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
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
		//
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();
}

Texture* Game::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	//  ͼ���Ƿ����
	auto iter = mTextures.find(fileName);
	//  ͼ��ת��
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//  ����ͼ��
		tex = new Texture();
		//  ����ͼ��
		if (tex->Load(fileName))
		{
			//  ��������
			mTextures.emplace(fileName, tex);
		}
		else
		{
			//  ʧ�ܴ���
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
	//  ��������
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	//  Ѱ����ʯ
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		//  �뿪����
		mAsteroids.erase(iter);
	}
}

void Game::Shutdown()
{
	//  ɾ��ͼ��
	UnloadData();
	//  �ر�����ϵͳ
	mInputSystem->Shutdown();
	//  ɾ������ϵͳ
	delete mInputSystem;
	//  ɾ����������
	delete mSpriteVerts;
	//  ɾ����ɫ��
	mSpriteShader->Unload();
	delete mSpriteShader;
    //  ɾ��opengl������
	SDL_GL_DeleteContext(mContext);
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
