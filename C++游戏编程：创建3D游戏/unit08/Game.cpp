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
	//  初始化视频子系统、音频子系统和控制器子系统
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		//  输出字符
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//  请求opengl属性
	/*SDL_GL_SetAttribute(
	    SDL_GLattr attr,
		int value
	);*/
	//  opengl核心配置
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//  设置版本3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//  请求4个8位RGBA通道
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//  启用双缓冲区
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//  使用GPU加速运行opengl
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//  创建窗口
	mWindow = SDL_CreateWindow("SDL5"  //  标题
		, 100  //  左上角的x坐标
		, 100  //  左上角的y坐标
		, 1024  //  窗口宽度
		, 768  //  窗口高度
		, SDL_WINDOW_OPENGL);  //  窗口创建标志，0表示没有标志
		/*SDL_WINDOW_FULLSCREEN使用全屏模式，
		SDL_WINDOW_FULLSCREEN_DESKTOP在当前桌面分辨率下使用全屏模式，
		SDL_WINDOW_OPENGL为OpenGL库提供图形支持，
		SDL_WINDOW_RESIZABLE允许用户重调整窗口大小*/
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
	//  创建opengl上下文
	mContext = SDL_GL_CreateContext(mWindow);
	//  初始化GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	//  错误抛出
	glGetError();
	//  加载着色器
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	//  创建三角形缓冲区
	CreateSpriteVerts();
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
	//  准备接收事件
	mInputSystem->PrepareForUpdate();
	//  定义输入事件
	SDL_Event event;
	//  SDL_PollEvent接收事件
	while (SDL_PollEvent(&event))
	{
		//  event.type包含接受的事件
		switch (event.type)
		{
	    //  按×退出
		case SDL_QUIT:
			mIsRunning = false;
			break;
		//  滚动轮处理
		case SDL_MOUSEWHEEL:
			mInputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}
	//  输入系统更新
	mInputSystem->Update();
	//  获取状态
	const InputState& state = mInputSystem->GetState();
	//  Esc键释放时退出
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EReleased)
	{
		mIsRunning = false;
	}
	//  输入并更新角色
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
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
	//  指定一种颜色（灰色）
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	//  清除颜色缓冲区
	glClear(GL_COLOR_BUFFER_BIT);
	//  启用alpha混合功能
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA  //  来源因子
		, GL_ONE_MINUS_SRC_ALPHA);  //  目标因子
	//  激活着色器
	mSpriteShader->SetActive();
	//  激活顶点数组
	mSpriteVerts->SetActive();
	//  绘制图像
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}
	//  互换前后台缓冲区
	SDL_GL_SwapWindow(mWindow);
}


bool Game::LoadShaders()
{
	//  定义着色器
	mSpriteShader = new Shader();
	//  加载着色器源文件
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	//  激活
	mSpriteShader->SetActive();
	//  创建简单视图投影矩阵
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	//  设置
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void Game::CreateSpriteVerts()
{
	//  创建顶点缓冲区，加入纹理坐标
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, //  左上
		 0.5f,  0.5f, 0.f, 1.f, 0.f, //  右上
		 0.5f, -0.5f, 0.f, 1.f, 1.f, //  右下
		-0.5f, -0.5f, 0.f, 0.f, 1.f  //  左下
	};
	//  创建索引缓冲区
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	//  创建顶点数组
	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Game::LoadData()
{
	//  创建飞船
	mShip = new Ship(this);
	//  初始化角度
	mShip->SetRotation(Math::PiOver2);
	//  创建陨石
	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
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
		//
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();
}

Texture* Game::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	//  图像是否存在
	auto iter = mTextures.find(fileName);
	//  图像转换
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//  创建图像
		tex = new Texture();
		//  加载图像
		if (tex->Load(fileName))
		{
			//  进入容器
			mTextures.emplace(fileName, tex);
		}
		else
		{
			//  失败处理
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
	//  进入容器
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	//  寻找陨石
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		//  离开容器
		mAsteroids.erase(iter);
	}
}

void Game::Shutdown()
{
	//  删除图像
	UnloadData();
	//  关闭输入系统
	mInputSystem->Shutdown();
	//  删除输入系统
	delete mInputSystem;
	//  删除顶点数组
	delete mSpriteVerts;
	//  删除着色器
	mSpriteShader->Unload();
	delete mSpriteShader;
    //  删除opengl上下文
	SDL_GL_DeleteContext(mContext);
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
