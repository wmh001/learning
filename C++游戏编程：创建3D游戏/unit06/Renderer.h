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
	//  ������Ļ�Ŀ�͸�
	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }
private:
	//  ������ɫ��
	bool LoadShaders();
	//  ������������
	void CreateSpriteVerts();
	//  ����ȫ�ֱ���
	void SetLightUniforms(class Shader* shader);
	//  ͼ�������
	std::unordered_map<std::string, class Texture*> mTextures;
	//  ���������
	std::unordered_map<std::string, class Mesh*> mMeshes;
	//  �������������
	std::vector<class SpriteComponent*> mSprites;
	//  �������������
	std::vector<class MeshComponent*> mMeshComps;
	//  ������Ϸ
	class Game* mGame;
	//  ͼ����ɫ��
	class Shader* mSpriteShader;
	//  ͼ�񶥵�����
	class VertexArray* mSpriteVerts;
	//  ������ɫ��
	class Shader* mMeshShader;
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
};

