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
		"SDL6"  //  ����
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
	return true;
}

void Renderer::Shutdown()
{
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
	//  ָ��һ����ɫ����ɫ��
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//  �����ɫ����������Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  ������Ȼ���
	glEnable(GL_DEPTH_TEST);
	//  ����alpha���
	glDisable(GL_BLEND);
	//  ����������ɫ��
	mMeshShader->SetActive();
	//  �趨��ͼͶӰ����
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	//  ����ȫ�ֱ���
	SetLightUniforms(mMeshShader);
	//  ��������
	for (auto mc : mMeshComps)
	{
		mc->Draw(mMeshShader);
	}
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
		sprite->Draw(mSpriteShader);
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
	//  ��������
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	//  ������
	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	mMeshComps.erase(iter);
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
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	//  ����
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	//  ����������ɫ��
	mMeshShader = new Shader();
	//  ������ɫ��Դ�ļ�
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
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
	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader)
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

