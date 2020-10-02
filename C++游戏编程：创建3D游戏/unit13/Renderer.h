#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
	//  ����
	Vector3 mDirection;
	//  ������
	Vector3 mDiffuseColor;
	//  ���淴��
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();
	//  ��ʼ����Ⱦ��
	bool Initialize(float screenWidth, float screenHeight);
	//  �ر�
	void Shutdown();
	//  ɾ������
	void UnloadData();
	//  ����
	void Draw();
	//  ����/�Ƴ�����
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	//  ����/�Ƴ�����
	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);
	//  ����/�Ƴ����Դ
	void AddPointLight(class PointLightComponent* light);
	void RemovePointLight(class PointLightComponent* light);
	//  ��ȡͼ��
	class Texture* GetTexture(const std::string& fileName);
	//  ��ȡ����
	class Mesh* GetMesh(const std::string& fileName);
	//  �޸���Ұ����
	void SetViewMatrix(const Matrix4& view) { mView = view; }
	//  �޸Ļ�����
	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	//  ���ʶ����
	DirectionalLight& GetDirectionalLight() { return mDirLight; }
	//  Ӧ����ͶӰ
	Vector3 Unproject(const Vector3& screenPoint) const;
	//  ��ȡ��Ļ����
	void GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
	//  ������Ļ�Ŀ�͸�
	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }
	//  �޸ĺ��Ӿ���ͼ����
	void SetMirrorView(const Matrix4& view) { mMirrorView = view; }
	//  ���ʺ��Ӿ�ͼ��
	class Texture* GetMirrorTexture() { return mMirrorTexture; }
	//  ����G������
	class GBuffer* GetGBuffer() { return mGBuffer; }
private:
	//  ����3D����
	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj, float viewPortScale = 1.0f, bool lit = true);
	//  ����������֡�������
	bool CreateMirrorTarget();
	//  ����G�������ı���
	void DrawFromGBuffer();
	//  ������ɫ��
	bool LoadShaders();
	//  ������������
	void CreateSpriteVerts();
	//  ����ȫ�ֱ���
	void SetLightUniforms(class Shader* shader, const Matrix4& view);
	//  ͼ�������
	std::unordered_map<std::string, class Texture*> mTextures;
	//  ���������
	std::unordered_map<std::string, class Mesh*> mMeshes;
	//  �������������
	std::vector<class SpriteComponent*> mSprites;
	//  �������������
	std::vector<class MeshComponent*> mMeshComps;
	//  ���������������
	std::vector<class SkeletalMeshComponent*> mSkeletalMeshes;
	//  ������Ϸ
	class Game* mGame;
	//  ͼ����ɫ��
	class Shader* mSpriteShader;
	//  ͼ�񶥵�����
	class VertexArray* mSpriteVerts;
	//  ������ɫ��
	class Shader* mMeshShader;
	//  ��Ƥ��ɫ��
	class Shader* mSkinnedShader;
	//  ��ͼ����
	Matrix4 mView;
	//  ͶӰ����
	Matrix4 mProjection;
	//  ��Ļ�Ŀ�͸�
	float mScreenWidth;
	float mScreenHeight;
	//  ������
	Vector3 mAmbientLight;
	//  �����
	DirectionalLight mDirLight;
	//  ��������
	SDL_Window* mWindow;
	//  opengl������
	SDL_GLContext mContext;
	//  ֡����������id
	unsigned int mMirrorBuffer;
	//  ���Ӿ�ͼ��
	class Texture* mMirrorTexture;
	//  ���Ӿ���ͼ����
	Matrix4 mMirrorView;
	//  G������
	class GBuffer* mGBuffer;
	//  ȫ�ֹ�����ɫ��
	class Shader* mGGlobalShader;
	//  ���Դ��ɫ��
	class Shader* mGPointLightShader;
	//  ���Դ
	std::vector<class PointLightComponent*> mPointLights;
	//  ���Դ����
	class Mesh* mPointLightMesh;
};

