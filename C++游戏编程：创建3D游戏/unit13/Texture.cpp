#include "Texture.h"
#include <SOIL.h>
#include <glew.h>
#include <SDL.h>

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;
	//  加载纹理
	unsigned char* image = SOIL_load_image(
		fileName.c_str()  //  文件名
		, &mWidth  //  宽度
		, &mHeight  //  高度
		, &channels  //  通道数
		, SOIL_LOAD_AUTO);  //  图像类型
	//  加载失败处理
	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}
	//  确定图像是否为RGB或RGBA
	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}
	//  创建纹理对象并保存id
	glGenTextures(1, &mTextureID);
	//  激活
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	//  将数据复制到纹理对象中
	glTexImage2D(
		GL_TEXTURE_2D  //  纹理目标
		, 0  //  细节程度
		, format  //  颜色格式
		, mWidth  //  宽
		, mHeight  //  高
		, 0  //  边
		, format  //  输入数据的颜色格式
		, GL_UNSIGNED_BYTE  //  输入数据的位深
		, image);  //  纹理对象
	//  释放内存
	SOIL_free_image_data(image);
	//  启用纹理分级细化
	glGenerateMipmap(GL_TEXTURE_2D);
	//  启用三线性过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//  测试各向异性过滤技术是否可用
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		//  获取最大各向异性过滤值
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		//  使用各向异性过滤
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}
	return true;
}

void Texture::Unload()
{
	//  删除纹理
	glDeleteTextures(1, &mTextureID);
}

void Texture::CreateFromSurface(SDL_Surface* surface)
{
	mWidth = surface->w;
	mHeight = surface->h;

	// Generate a GL texture
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, surface->pixels);

	// Use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::CreateForRendering(int width, int height, unsigned int format)
{
	//  设置宽度和高度
	mWidth = width;
	mHeight = height;
	//  创建纹理对象并保存id
	glGenTextures(1, &mTextureID);
	//  激活
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	//  设置初始数据为空的图像宽度/高度
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, GL_RGB, GL_FLOAT, nullptr);
	//  启用最近邻滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::SetActive(int index)
{
	//
	glActiveTexture(GL_TEXTURE0 + index);
	//  激活
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
