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
	//  启用双线性过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::Unload()
{
	//  删除纹理
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	//  激活
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

