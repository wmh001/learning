#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
	//  方向
	Vector3 mDirection;
	//  漫反射
	Vector3 mDiffuseColor;
	//  镜面反射
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();
	//  初始化渲染器
	bool Initialize(float screenWidth, float screenHeight);
	//  关闭
	void Shutdown();
	//  删除数据
	void UnloadData();
	//  绘制
	void Draw();
	//  加入/移除精灵
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	//  加入/移除网格
	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);
	//  获取图像
	class Texture* GetTexture(const std::string& fileName);
	//  获取网格
	class Mesh* GetMesh(const std::string& fileName);
	//  修改视野矩阵
	void SetViewMatrix(const Matrix4& view) { mView = view; }
	//  修改环境光
	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	//  访问定向光
	DirectionalLight& GetDirectionalLight() { return mDirLight; }
	//  访问屏幕的宽和高
	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }
private:
	//  加载着色器
	bool LoadShaders();
	//  创建顶点数组
	void CreateSpriteVerts();
	//  处理全局变量
	void SetLightUniforms(class Shader* shader);
	//  图像的容器
	std::unordered_map<std::string, class Texture*> mTextures;
	//  网格的容器
	std::unordered_map<std::string, class Mesh*> mMeshes;
	//  精灵组件的容器
	std::vector<class SpriteComponent*> mSprites;
	//  网格组件的容器
	std::vector<class MeshComponent*> mMeshComps;
	//  所属游戏
	class Game* mGame;
	//  图像着色器
	class Shader* mSpriteShader;
	//  图像顶点数组
	class VertexArray* mSpriteVerts;
	//  网格着色器
	class Shader* mMeshShader;
	//  视图矩阵
	Matrix4 mView;
	//  投影矩阵
	Matrix4 mProjection;
	//  屏幕的宽和高
	float mScreenWidth;
	float mScreenHeight;
	//  环境光
	Vector3 mAmbientLight;
	//  定向光
	DirectionalLight mDirLight;
	//  创建窗口
	SDL_Window* mWindow;
	//  opengl上下文
	SDL_GLContext mContext;
};

