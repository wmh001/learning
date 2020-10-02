#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "UIScreen.h"
#include "Game.h"
#include <glew.h>
#include "SkeletalMeshComponent.h"
#include "GBuffer.h"
#include "PointLightComponent.h"

Renderer::Renderer(Game* game)
	: mGame(game)
	, mSpriteShader(nullptr)
	, mMeshShader(nullptr)
	, mSpriteVerts(nullptr)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mWindow(nullptr)
	, mSkinnedShader(nullptr)
	, mMirrorBuffer(0)
	, mMirrorTexture(nullptr)
	, mGBuffer(nullptr)
	, mGGlobalShader(nullptr)
	, mGPointLightShader(nullptr)
	, mPointLightMesh(nullptr)
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
		"SDL12"  //  标题
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
	//  创建帧缓冲对象及失败处理
	if (!CreateMirrorTarget())
	{
		SDL_Log("Failed to create render target for mirror.");
		return false;
	}
	//  创建G缓冲区
	mGBuffer = new GBuffer();
	int width = static_cast<int>(mScreenWidth);
	int height = static_cast<int>(mScreenHeight);
	//  创建G缓冲区失败处理
	if (!mGBuffer->Create(width, height))
	{
		SDL_Log("Failed to create G-buffer.");
		return false;
	}
	//  设置点光源网格
	mPointLightMesh = GetMesh("Assets/PointLight.gpmesh");
	return true;
}

void Renderer::Shutdown()
{
	//  删除后视镜
	if (mMirrorTexture != nullptr)
	{
		//  删除缓冲区
		glDeleteFramebuffers(1, &mMirrorBuffer);
		//  删除图像
		mMirrorTexture->Unload();
		delete mMirrorTexture;
	}
	//  删除G缓冲区
	if (mGBuffer != nullptr)
	{
		mGBuffer->Destroy();
		delete mGBuffer;
	}
	//  删除点光源
	while (!mPointLights.empty())
	{
		delete mPointLights.back();
	}
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
	//  绘制后视镜
	Draw3DScene(mMirrorBuffer, mMirrorView, mProjection, 0.25f);
	//  绘制默认窗口到G缓冲区
	Draw3DScene(mGBuffer->GetBufferID(), mView, mProjection, 1.0f, false);
	//  更改帧缓冲区为默认值
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//  绘制G缓冲区四边形
	DrawFromGBuffer();
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
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}
	//  绘制用户界面屏幕
	for (auto ui : mGame->GetUIStack())
	{
		ui->Draw(mSpriteShader);
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
	//  判断是否为蒙皮骨骼网格
	if (mesh->GetIsSkeletal())
	{
		//  类型转换
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		//  进入容器
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		//  进入容器
		mMeshComps.emplace_back(mesh);
	}
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	//  判断是否为蒙皮骨骼网格
	if (mesh->GetIsSkeletal())
	{
		//  类型转换
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		//  寻找
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		//  移除
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		//  寻找
		auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
		//  移除
		mMeshComps.erase(iter);
	}
}

void Renderer::AddPointLight(PointLightComponent* light)
{
	//  进入容器
	mPointLights.emplace_back(light);
}

void Renderer::RemovePointLight(PointLightComponent* light)
{
	//  移除容器
	auto iter = std::find(mPointLights.begin(), mPointLights.end(), light);
	mPointLights.erase(iter);
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

void Renderer::Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj, float viewPortScale, bool lit)
{
	//  激活
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//  设置视窗大小
	glViewport(0, 0,
		static_cast<int>(mScreenWidth * viewPortScale),
		static_cast<int>(mScreenHeight * viewPortScale)
	);
	//  指定一种颜色（灰色）
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//  启用深度掩码
	glDepthMask(GL_TRUE);
	//  清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  启用深度缓冲
	glEnable(GL_DEPTH_TEST);
	//  禁用alpha混合
	glDisable(GL_BLEND);
	//  激活网格着色器
	mMeshShader->SetActive();
	//  设定视图投影矩阵
	mMeshShader->SetMatrixUniform("uViewProj", view * proj);
	//
	if (lit)
	{
		//  处理全局变量
		SetLightUniforms(mMeshShader, view);
	}
    //  绘制网格
	for (auto mc : mMeshComps)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}
	//  激活骨骼网格着色器
	mSkinnedShader->SetActive();
	//  设定视图投影矩阵
	mSkinnedShader->SetMatrixUniform("uViewProj", view * proj);
	//
	if (lit)
	{
		//  处理全局变量
		SetLightUniforms(mSkinnedShader, view);
	}
	//  绘制骨骼网格
	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedShader);
		}
	}
}

bool Renderer::CreateMirrorTarget()
{
	//  计算宽度和高度
	int width = static_cast<int>(mScreenWidth) / 4;
	int height = static_cast<int>(mScreenHeight) / 4;
	//  创建帧缓冲区对象并保存id
	glGenFramebuffers(1, &mMirrorBuffer);
	//  激活
	glBindFramebuffer(GL_FRAMEBUFFER, mMirrorBuffer);
	//  创建图像
	mMirrorTexture = new Texture();
	//  设置为GL_RGB格式纹理
	mMirrorTexture->CreateForRendering(width, height, GL_RGB);
	//  向该目标添加深度缓冲区
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	//  将后视镜图像与帧缓冲区对象相关联
	glFramebufferTexture(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,  //  后视镜图像对应与片段着色器的第一个输出
		mMirrorTexture->GetTextureID(),
		0);
	//  将场景绘制到GL_COLOR_ATTACHMENTO槽中
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	//  检测一切是否正常及失败处理
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		//  删除帧缓冲区
		glDeleteFramebuffers(1, &mMirrorBuffer);
		//  删除图像
		mMirrorTexture->Unload();
		delete mMirrorTexture;
		mMirrorTexture = nullptr;
		return false;
	}
	return true;
}

void Renderer::DrawFromGBuffer()
{
	//  禁用深度缓冲
	glDisable(GL_DEPTH_TEST);
	//  激活全局光照着色器
	mGGlobalShader->SetActive();
	//  激活全局光照顶点数组
	mSpriteVerts->SetActive();
	//  激活图像
	mGBuffer->SetTexturesActive();
	//  设置视图矩阵
	SetLightUniforms(mGGlobalShader, mView);
	//  绘制
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//  将深度缓冲区从G缓冲区复制到默认帧缓冲区
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mGBuffer->GetBufferID());
	int width = static_cast<int>(mScreenWidth);
	int height = static_cast<int>(mScreenHeight);
	glBlitFramebuffer(0, 0, width, height,
		0, 0, width, height,
		GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	//  启用深度缓冲
	glEnable(GL_DEPTH_TEST);
	//  禁用深度掩码
	glDepthMask(GL_FALSE);
	//  激活点光源缓冲区
	mGPointLightShader->SetActive();
	//  激活点光源顶点数组
	mPointLightMesh->GetVertexArray()->SetActive();
	//  数组视图投影矩阵
	mGPointLightShader->SetMatrixUniform("uViewProj", mView * mProjection);
	//  激活图像
	mGBuffer->SetTexturesActive();
	//  启用alpha混合
	glEnable(GL_BLEND);
	//
	glBlendFunc(GL_ONE, GL_ONE);
	//  绘制点光源
	for (PointLightComponent* p : mPointLights)
	{
		p->Draw(mGPointLightShader, mPointLightMesh);
	}
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
	Matrix4 spriteViewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	//  设置
	mSpriteShader->SetMatrixUniform("uViewProj", spriteViewProj);
	//  创建网格着色器
	mMeshShader = new Shader();
	//  加载着色器源文件
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/GBufferWrite.frag"))
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
	//  创建蒙皮着色器
	mSkinnedShader = new Shader();
	//  加载着色器源文件
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/GBufferWrite.frag"))
	{
		return false;
	}
	//  激活
	mSkinnedShader->SetActive();
	//  设置视图投影矩阵
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);
	//  创建全局光照着色器
	mGGlobalShader = new Shader();
	//  加载着色器源文件
	if (!mGGlobalShader->Load("Shaders/GBufferGlobal.vert", "Shaders/GBufferGlobal.frag"))
	{
		return false;
	}
	//  激活
	mGGlobalShader->SetActive();
	//  设置颜色
	mGGlobalShader->SetIntUniform("uGDiffuse", 0);
	//  设置法线
	mGGlobalShader->SetIntUniform("uGNormal", 1);
	//  设置位置
	mGGlobalShader->SetIntUniform("uGWorldPos", 2);
	//  设置视图投影矩阵
	mGGlobalShader->SetMatrixUniform("uViewProj", spriteViewProj);
	//  设置世界变换矩阵并翻转y轴
	Matrix4 gbufferWorld = Matrix4::CreateScale(mScreenWidth, -mScreenHeight, 1.0f);
	mGGlobalShader->SetMatrixUniform("uWorldTransform", gbufferWorld);
	//  创建点光源着色器
	mGPointLightShader = new Shader();
	//  加载着色器源文件
	if (!mGPointLightShader->Load("Shaders/BasicMesh.vert", "Shaders/GBufferPointLight.frag"))
	{
		return false;
	}
	//  激活
	mGPointLightShader->SetActive();
	//  设置颜色
	mGPointLightShader->SetIntUniform("uGDiffuse", 0);
	//  设置法线
	mGPointLightShader->SetIntUniform("uGNormal", 1);
	//  设置位置
	mGPointLightShader->SetIntUniform("uGWorldPos", 2);
	//  设置屏幕
	mGPointLightShader->SetVector2Uniform("uScreenDimensions", Vector2(mScreenWidth, mScreenHeight));
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
	mSpriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader, const Matrix4& view)
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

