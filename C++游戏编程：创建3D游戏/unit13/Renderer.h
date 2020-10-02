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
	//  加入/移除点光源
	void AddPointLight(class PointLightComponent* light);
	void RemovePointLight(class PointLightComponent* light);
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
	//  应用逆投影
	Vector3 Unproject(const Vector3& screenPoint) const;
	//  获取屏幕方向
	void GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
	//  访问屏幕的宽和高
	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }
	//  修改后视镜视图矩阵
	void SetMirrorView(const Matrix4& view) { mMirrorView = view; }
	//  访问后视镜图像
	class Texture* GetMirrorTexture() { return mMirrorTexture; }
	//  访问G缓冲区
	class GBuffer* GetGBuffer() { return mGBuffer; }
private:
	//  绘制3D场景
	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj, float viewPortScale = 1.0f, bool lit = true);
	//  创建和配置帧缓冲对象
	bool CreateMirrorTarget();
	//  绘制G缓冲区四边形
	void DrawFromGBuffer();
	//  加载着色器
	bool LoadShaders();
	//  创建顶点数组
	void CreateSpriteVerts();
	//  处理全局变量
	void SetLightUniforms(class Shader* shader, const Matrix4& view);
	//  图像的容器
	std::unordered_map<std::string, class Texture*> mTextures;
	//  网格的容器
	std::unordered_map<std::string, class Mesh*> mMeshes;
	//  精灵组件的容器
	std::vector<class SpriteComponent*> mSprites;
	//  网格组件的容器
	std::vector<class MeshComponent*> mMeshComps;
	//  骨骼网格组件容器
	std::vector<class SkeletalMeshComponent*> mSkeletalMeshes;
	//  所属游戏
	class Game* mGame;
	//  图像着色器
	class Shader* mSpriteShader;
	//  图像顶点数组
	class VertexArray* mSpriteVerts;
	//  网格着色器
	class Shader* mMeshShader;
	//  蒙皮着色器
	class Shader* mSkinnedShader;
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
	//  帧缓冲区对象id
	unsigned int mMirrorBuffer;
	//  后视镜图像
	class Texture* mMirrorTexture;
	//  后视镜视图矩阵
	Matrix4 mMirrorView;
	//  G缓冲区
	class GBuffer* mGBuffer;
	//  全局光照着色器
	class Shader* mGGlobalShader;
	//  点光源着色器
	class Shader* mGPointLightShader;
	//  点光源
	std::vector<class PointLightComponent*> mPointLights;
	//  点光源网格
	class Mesh* mPointLightMesh;
};

