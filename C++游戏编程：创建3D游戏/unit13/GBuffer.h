#pragma once
#include <vector>

class GBuffer
{
public:
	//  G缓冲区的不同数据类型
	enum Type
	{
		//  漫反射颜色
		EDiffuse = 0,
		//  法线
		ENormal,
		//  位置
		EWorldPos,
		NUM_GBUFFER_TEXTURES
	};
	GBuffer();
	~GBuffer();
	//  创建G缓冲区
	bool Create(int width, int height);
	//  删除G缓冲区
	void Destroy();
	//  访问特定类型数据的纹理
	class Texture* GetTexture(Type type);
	// Get the framebuffer object ID
	unsigned int GetBufferID() const { return mBufferID; }
	//  激活图像并绑定索引
	void SetTexturesActive();
private:
	//  纹理容器
	std::vector<class Texture*> mTextures;
	//  帧缓冲区id
	unsigned int mBufferID;
};

