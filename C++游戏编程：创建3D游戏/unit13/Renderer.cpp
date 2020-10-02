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
	//  ��ʼ��
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
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
	//  ����24λ��Ȼ�����
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//  ����˫������
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//  ʹ��GPU��������opengl
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//  ��������
	mWindow = SDL_CreateWindow(
		"SDL12"  //  ����
		, 100  //  ���Ͻǵ�x����
		, 50  //  ���Ͻǵ�y����
		, static_cast<int>(mScreenWidth)  //  ���ڿ��
		, static_cast<int>(mScreenHeight)  //  ���ڸ߶�
		, SDL_WINDOW_OPENGL);  //  ���ڴ�����־
		/*SDL_WINDOW_FULLSCREENʹ��ȫ��ģʽ��
		SDL_WINDOW_FULLSCREEN_DESKTOP�ڵ�ǰ����ֱ�����ʹ��ȫ��ģʽ��
		SDL_WINDOW_OPENGLΪOpenGL���ṩͼ��֧�֣�
		SDL_WINDOW_RESIZABLE�����û��ص������ڴ�С*/
		//  ʧ�ܴ���
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	//  ����opengl������
	mContext = SDL_GL_CreateContext(mWindow);
	//  ��ʼ��GLEW
	glewExperimental = GL_TRUE;
	//  ʧ�ܴ���
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	//  �����׳�
	glGetError();
	//  ������ɫ��ʧ�ܴ���
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	//  ���������λ�����
	CreateSpriteVerts();
	//  ����֡�������ʧ�ܴ���
	if (!CreateMirrorTarget())
	{
		SDL_Log("Failed to create render target for mirror.");
		return false;
	}
	//  ����G������
	mGBuffer = new GBuffer();
	int width = static_cast<int>(mScreenWidth);
	int height = static_cast<int>(mScreenHeight);
	//  ����G������ʧ�ܴ���
	if (!mGBuffer->Create(width, height))
	{
		SDL_Log("Failed to create G-buffer.");
		return false;
	}
	//  ���õ��Դ����
	mPointLightMesh = GetMesh("Assets/PointLight.gpmesh");
	return true;
}

void Renderer::Shutdown()
{
	//  ɾ�����Ӿ�
	if (mMirrorTexture != nullptr)
	{
		//  ɾ��������
		glDeleteFramebuffers(1, &mMirrorBuffer);
		//  ɾ��ͼ��
		mMirrorTexture->Unload();
		delete mMirrorTexture;
	}
	//  ɾ��G������
	if (mGBuffer != nullptr)
	{
		mGBuffer->Destroy();
		delete mGBuffer;
	}
	//  ɾ�����Դ
	while (!mPointLights.empty())
	{
		delete mPointLights.back();
	}
	//  ɾ����������
	delete mSpriteVerts;
	//  ɾ��ͼ����ɫ��
	mSpriteShader->Unload();
	delete mSpriteShader;
	//  ɾ��������ɫ��
	mMeshShader->Unload();
	delete mMeshShader;
	//  ɾ��opengl������
	SDL_GL_DeleteContext(mContext);
	//  �رմ���
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	//  �ݻ�ͼ��
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();
	//  �ݻ�����
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::Draw()
{
	//  ���ƺ��Ӿ�
	Draw3DScene(mMirrorBuffer, mMirrorView, mProjection, 0.25f);
	//  ����Ĭ�ϴ��ڵ�G������
	Draw3DScene(mGBuffer->GetBufferID(), mView, mProjection, 1.0f, false);
	//  ����֡������ΪĬ��ֵ
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//  ����G�������ı���
	DrawFromGBuffer();
	//  ������Ȼ���
	glDisable(GL_DEPTH_TEST);
	//  ����alpha���
	glEnable(GL_BLEND);
	//  ����RGB��Alphaʹ�ò�ͬ�Ļ�Ϸ�ʽ
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	//  �ֱ�ָ��RGB��alpha��������������
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	//  ������ɫ��
	mSpriteShader->SetActive();
	//  ���������
	mSpriteVerts->SetActive();
	//  ����ͼ��
	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}
	//  �����û�������Ļ
	for (auto ui : mGame->GetUIStack())
	{
		ui->Draw(mSpriteShader);
	}
	//  ����ǰ��̨������
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
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

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	//  ���ܽ�������֪��˳��
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
	//  �ж��Ƿ�Ϊ��Ƥ��������
	if (mesh->GetIsSkeletal())
	{
		//  ����ת��
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		//  ��������
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		//  ��������
		mMeshComps.emplace_back(mesh);
	}
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	//  �ж��Ƿ�Ϊ��Ƥ��������
	if (mesh->GetIsSkeletal())
	{
		//  ����ת��
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		//  Ѱ��
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		//  �Ƴ�
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		//  Ѱ��
		auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
		//  �Ƴ�
		mMeshComps.erase(iter);
	}
}

void Renderer::AddPointLight(PointLightComponent* light)
{
	//  ��������
	mPointLights.emplace_back(light);
}

void Renderer::RemovePointLight(PointLightComponent* light)
{
	//  �Ƴ�����
	auto iter = std::find(mPointLights.begin(), mPointLights.end(), light);
	mPointLights.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
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

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	Mesh* m = nullptr;
	//  Ѱ���ļ�
	auto iter = mMeshes.find(fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	else
	{
		//  ��������
		m = new Mesh();
		//  ����ͼ��
		if (m->Load(fileName, this))
		{
			//  ��������
			mMeshes.emplace(fileName, m);
		}
		else
		{
			//  ʧ�ܴ���
			delete m;
			m = nullptr;
		}
	}
	return m;
}

void Renderer::Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj, float viewPortScale, bool lit)
{
	//  ����
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//  �����Ӵ���С
	glViewport(0, 0,
		static_cast<int>(mScreenWidth * viewPortScale),
		static_cast<int>(mScreenHeight * viewPortScale)
	);
	//  ָ��һ����ɫ����ɫ��
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//  �����������
	glDepthMask(GL_TRUE);
	//  �����ɫ����������Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  ������Ȼ���
	glEnable(GL_DEPTH_TEST);
	//  ����alpha���
	glDisable(GL_BLEND);
	//  ����������ɫ��
	mMeshShader->SetActive();
	//  �趨��ͼͶӰ����
	mMeshShader->SetMatrixUniform("uViewProj", view * proj);
	//
	if (lit)
	{
		//  ����ȫ�ֱ���
		SetLightUniforms(mMeshShader, view);
	}
    //  ��������
	for (auto mc : mMeshComps)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}
	//  �������������ɫ��
	mSkinnedShader->SetActive();
	//  �趨��ͼͶӰ����
	mSkinnedShader->SetMatrixUniform("uViewProj", view * proj);
	//
	if (lit)
	{
		//  ����ȫ�ֱ���
		SetLightUniforms(mSkinnedShader, view);
	}
	//  ���ƹ�������
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
	//  �����Ⱥ͸߶�
	int width = static_cast<int>(mScreenWidth) / 4;
	int height = static_cast<int>(mScreenHeight) / 4;
	//  ����֡���������󲢱���id
	glGenFramebuffers(1, &mMirrorBuffer);
	//  ����
	glBindFramebuffer(GL_FRAMEBUFFER, mMirrorBuffer);
	//  ����ͼ��
	mMirrorTexture = new Texture();
	//  ����ΪGL_RGB��ʽ����
	mMirrorTexture->CreateForRendering(width, height, GL_RGB);
	//  ���Ŀ�������Ȼ�����
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	//  �����Ӿ�ͼ����֡���������������
	glFramebufferTexture(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,  //  ���Ӿ�ͼ���Ӧ��Ƭ����ɫ���ĵ�һ�����
		mMirrorTexture->GetTextureID(),
		0);
	//  ���������Ƶ�GL_COLOR_ATTACHMENTO����
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	//  ���һ���Ƿ�������ʧ�ܴ���
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		//  ɾ��֡������
		glDeleteFramebuffers(1, &mMirrorBuffer);
		//  ɾ��ͼ��
		mMirrorTexture->Unload();
		delete mMirrorTexture;
		mMirrorTexture = nullptr;
		return false;
	}
	return true;
}

void Renderer::DrawFromGBuffer()
{
	//  ������Ȼ���
	glDisable(GL_DEPTH_TEST);
	//  ����ȫ�ֹ�����ɫ��
	mGGlobalShader->SetActive();
	//  ����ȫ�ֹ��ն�������
	mSpriteVerts->SetActive();
	//  ����ͼ��
	mGBuffer->SetTexturesActive();
	//  ������ͼ����
	SetLightUniforms(mGGlobalShader, mView);
	//  ����
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//  ����Ȼ�������G���������Ƶ�Ĭ��֡������
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mGBuffer->GetBufferID());
	int width = static_cast<int>(mScreenWidth);
	int height = static_cast<int>(mScreenHeight);
	glBlitFramebuffer(0, 0, width, height,
		0, 0, width, height,
		GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	//  ������Ȼ���
	glEnable(GL_DEPTH_TEST);
	//  �����������
	glDepthMask(GL_FALSE);
	//  ������Դ������
	mGPointLightShader->SetActive();
	//  ������Դ��������
	mPointLightMesh->GetVertexArray()->SetActive();
	//  ������ͼͶӰ����
	mGPointLightShader->SetMatrixUniform("uViewProj", mView * mProjection);
	//  ����ͼ��
	mGBuffer->SetTexturesActive();
	//  ����alpha���
	glEnable(GL_BLEND);
	//
	glBlendFunc(GL_ONE, GL_ONE);
	//  ���Ƶ��Դ
	for (PointLightComponent* p : mPointLights)
	{
		p->Draw(mGPointLightShader, mPointLightMesh);
	}
}

bool Renderer::LoadShaders()
{
	//  ����ͼ����ɫ��
	mSpriteShader = new Shader();
	//  ������ɫ��Դ�ļ�
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	//  ����
	mSpriteShader->SetActive();
	//  ��������ͼͶӰ����
	Matrix4 spriteViewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	//  ����
	mSpriteShader->SetMatrixUniform("uViewProj", spriteViewProj);
	//  ����������ɫ��
	mMeshShader = new Shader();
	//  ������ɫ��Դ�ļ�
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/GBufferWrite.frag"))
	{
		return false;
	}
	//  ����
	mMeshShader->SetActive();
	//  ��������ͶӰ����
	mView = Matrix4::CreateLookAt(
		Vector3::Zero
		, Vector3::UnitX
		, Vector3::UnitZ);
	//  ����͸��ͶӰ����
	mProjection = Matrix4::CreatePerspectiveFOV(
		Math::ToRadians(70.0f)
		, mScreenWidth
		, mScreenHeight
		, 10.0f
		, 10000.0f);
	//  ������ͼͶӰ����
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	//  ������Ƥ��ɫ��
	mSkinnedShader = new Shader();
	//  ������ɫ��Դ�ļ�
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/GBufferWrite.frag"))
	{
		return false;
	}
	//  ����
	mSkinnedShader->SetActive();
	//  ������ͼͶӰ����
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);
	//  ����ȫ�ֹ�����ɫ��
	mGGlobalShader = new Shader();
	//  ������ɫ��Դ�ļ�
	if (!mGGlobalShader->Load("Shaders/GBufferGlobal.vert", "Shaders/GBufferGlobal.frag"))
	{
		return false;
	}
	//  ����
	mGGlobalShader->SetActive();
	//  ������ɫ
	mGGlobalShader->SetIntUniform("uGDiffuse", 0);
	//  ���÷���
	mGGlobalShader->SetIntUniform("uGNormal", 1);
	//  ����λ��
	mGGlobalShader->SetIntUniform("uGWorldPos", 2);
	//  ������ͼͶӰ����
	mGGlobalShader->SetMatrixUniform("uViewProj", spriteViewProj);
	//  ��������任���󲢷�תy��
	Matrix4 gbufferWorld = Matrix4::CreateScale(mScreenWidth, -mScreenHeight, 1.0f);
	mGGlobalShader->SetMatrixUniform("uWorldTransform", gbufferWorld);
	//  �������Դ��ɫ��
	mGPointLightShader = new Shader();
	//  ������ɫ��Դ�ļ�
	if (!mGPointLightShader->Load("Shaders/BasicMesh.vert", "Shaders/GBufferPointLight.frag"))
	{
		return false;
	}
	//  ����
	mGPointLightShader->SetActive();
	//  ������ɫ
	mGPointLightShader->SetIntUniform("uGDiffuse", 0);
	//  ���÷���
	mGPointLightShader->SetIntUniform("uGNormal", 1);
	//  ����λ��
	mGPointLightShader->SetIntUniform("uGWorldPos", 2);
	//  ������Ļ
	mGPointLightShader->SetVector2Uniform("uScreenDimensions", Vector2(mScreenWidth, mScreenHeight));
	return true;
}

void Renderer::CreateSpriteVerts()
{
	//  �������㻺������������������ͷ���
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f,  //  ����
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f,  //  ����
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f,  //  ����
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f   //  ����
	};
	//  ��������������
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	//  ������������
	mSpriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader, const Matrix4& view)
{
	//  ������ͼ����
	Matrix4 invView = mView;
	//  ����
	invView.Invert();
	//  λ��
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	//  ������
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	//  ����
	shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection);
	//  ������
	shader->SetVectorUniform("uDirLight.mDiffuseColor", mDirLight.mDiffuseColor);
	//  ���淴��
	shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor);
}

Vector3 Renderer::Unproject(const Vector3& screenPoint) const
{
	//  ����Ļ��ת��Ϊ�豸���꣨����-1��+1֮�䣩
	Vector3 deviceCoord = screenPoint;
	deviceCoord.x /= (mScreenWidth) * 0.5f;
	deviceCoord.y /= (mScreenHeight) * 0.5f;
	//  ������ͶӰ����
	Matrix4 unprojection = mView * mProjection;
	unprojection.Invert();
	//  ��ͶӰ����ת��Ϊ����
	return Vector3::TransformWithPerspDiv(deviceCoord, unprojection);
}

void Renderer::GetScreenDirection(Vector3& outStart, Vector3& outDir) const
{
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	//  ������ʼ��
	outStart = Unproject(screenPoint);
	//  ������ֹ��
	screenPoint.z = 0.9f;
	Vector3 end = Unproject(screenPoint);
    //  ��������
	outDir = end - outStart;
	outDir.Normalize();
}

