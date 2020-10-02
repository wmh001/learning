#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>

Renderer::Renderer(Game* game)
	: mGame(game)
	, mSpriteShader(nullptr)
	, mMeshShader(nullptr)
	, mSpriteVerts(nullptr)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mWindow(nullptr)
{
}

Renderer::~Renderer()
{

}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	//  初始化
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
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
	//  申请24位深度缓冲区
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//  启用双缓冲区
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//  使用GPU加速运行opengl
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//  创建窗口
	mWindow = SDL_CreateWindow(
		"SDL6"  //  标题
		, 100  //  左上角的x坐标
		, 50  //  左上角的y坐标
		, static_cast<int>(mScreenWidth)  //  窗口宽度
		, static_cast<int>(mScreenHeight)  //  窗口高度
		, SDL_WINDOW_OPENGL);  //  窗口创建标志
		/*SDL_WINDOW_FULLSCREEN使用全屏模式，
		SDL_WINDOW_FULLSCREEN_DESKTOP在当前桌面分辨率下使用全屏模式，
		SDL_WINDOW_OPENGL为OpenGL库提供图形支持，
		SDL_WINDOW_RESIZABLE允许用户重调整窗口大小*/
		//  失败处理
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	//  创建opengl上下文
	mContext = SDL_GL_CreateContext(mWindow);
	//  初始化GLEW
	glewExperimental = GL_TRUE;
	//  失败处理
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	//  错误抛出
	glGetError();
	//  加载着色器失败处理
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	//  创建三角形缓冲区
	CreateSpriteVerts();
	return true;
}

void Renderer::Shutdown()
{
	//  删除顶点数组
	delete mSpriteVerts;
	//  删除图像着色器
	mSpriteShader->Unload();
	delete mSpriteShader;
	//  删除网格着色器
	mMeshShader->Unload();
	delete mMeshShader;
	//  删除opengl上下文
	SDL_GL_DeleteContext(mContext);
	//  关闭窗口
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	//  摧毁图像
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();
	//  摧毁网格
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::Draw()
{
	//  指定一种颜色（灰色）
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//  清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  启用深度缓冲
	glEnable(GL_DEPTH_TEST);
	//  禁用alpha混合
	glDisable(GL_BLEND);
	//  激活网格着色器
	mMeshShader->SetActive();
	//  设定视图投影矩阵
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	//  处理全局变量
	SetLightUniforms(mMeshShader);
	//  绘制网格
	for (auto mc : mMeshComps)
	{
		mc->Draw(mMeshShader);
	}
	//  禁用深度缓冲
	glDisable(GL_DEPTH_TEST);
	//  启用alpha混合
	glEnable(GL_BLEND);
	//  允许RGB和Alpha使用不同的混合方式
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	//  分别指定RGB和alpha分量的像素算术
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
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

void Renderer::AddSprite(SpriteComponent* sprite)
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

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	//  不能交换，不知道顺序
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
	//  进入容器
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	//  出容器
	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	mMeshComps.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
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

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	Mesh* m = nullptr;
	//  寻找文件
	auto iter = mMeshes.find(fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	else
	{
		//  创建网格
		m = new Mesh();
		//  加载图像
		if (m->Load(fileName, this))
		{
			//  进入容器
			mMeshes.emplace(fileName, m);
		}
		else
		{
			//  失败处理
			delete m;
			m = nullptr;
		}
	}
	return m;
}

bool Renderer::LoadShaders()
{
	//  创建图像着色器
	mSpriteShader = new Shader();
	//  加载着色器源文件
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	//  激活
	mSpriteShader->SetActive();
	//  创建简单视图投影矩阵
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	//  设置
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	//  创建网格着色器
	mMeshShader = new Shader();
	//  加载着色器源文件
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
	{
		return false;
	}
	//  激活
	mMeshShader->SetActive();
	//  计算正交投影矩阵
	mView = Matrix4::CreateLookAt(
		Vector3::Zero
		, Vector3::UnitX
		, Vector3::UnitZ);
	//  计算透视投影矩阵
	mProjection = Matrix4::CreatePerspectiveFOV(
		Math::ToRadians(70.0f)
		, mScreenWidth
		, mScreenHeight
		, 10.0f
		, 10000.0f);
	//  设置视图投影矩阵
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	return true;
}

void Renderer::CreateSpriteVerts()
{
	//  创建顶点缓冲区，加入纹理坐标和法线
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f,  //  左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f,  //  右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f,  //  右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f   //  左下
	};
	//  创建索引缓冲区
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	//  创建顶点数组
	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader)
{
	//  创建视图矩阵
	Matrix4 invView = mView;
	//  倒置
	invView.Invert();
	//  位置
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	//  环境光
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	//  方向
	shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection);
	//  漫反射
	shader->SetVectorUniform("uDirLight.mDiffuseColor", mDirLight.mDiffuseColor);
	//  镜面反射
	shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor);
}

Vector3 Renderer::Unproject(const Vector3& screenPoint) const
{
	//  将屏幕点转换为设备坐标（介于-1和+1之间）
	Vector3 deviceCoord = screenPoint;
	deviceCoord.x /= (mScreenWidth) * 0.5f;
	deviceCoord.y /= (mScreenHeight) * 0.5f;
	//  计算逆投影矩阵
	Matrix4 unprojection = mView * mProjection;
	unprojection.Invert();
	//  逆投影矩阵转换为向量
	return Vector3::TransformWithPerspDiv(deviceCoord, unprojection);
}

void Renderer::GetScreenDirection(Vector3& outStart, Vector3& outDir) const
{
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	//  计算起始点
	outStart = Unproject(screenPoint);
	//  计算终止点
	screenPoint.z = 0.9f;
	Vector3 end = Unproject(screenPoint);
    //  计算向量
	outDir = end - outStart;
	outDir.Normalize();
}

