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
	//  ��������
	unsigned char* image = SOIL_load_image(
		fileName.c_str()  //  �ļ���
		, &mWidth  //  ���
		, &mHeight  //  �߶�
		, &channels  //  ͨ����
		, SOIL_LOAD_AUTO);  //  ͼ������
	//  ����ʧ�ܴ���
	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}
	//  ȷ��ͼ���Ƿ�ΪRGB��RGBA
	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}
	//  ����������󲢱���id
	glGenTextures(1, &mTextureID);
	//  ����
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	//  �����ݸ��Ƶ����������
	glTexImage2D(
		GL_TEXTURE_2D  //  ����Ŀ��
		, 0  //  ϸ�ڳ̶�
		, format  //  ��ɫ��ʽ
		, mWidth  //  ��
		, mHeight  //  ��
		, 0  //  ��
		, format  //  �������ݵ���ɫ��ʽ
		, GL_UNSIGNED_BYTE  //  �������ݵ�λ��
		, image);  //  �������
	//  �ͷ��ڴ�
	SOIL_free_image_data(image);
	//  ��������ּ�ϸ��
	glGenerateMipmap(GL_TEXTURE_2D);
	//  ���������Թ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//  ���Ը������Թ��˼����Ƿ����
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		//  ��ȡ���������Թ���ֵ
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		//  ʹ�ø������Թ���
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}
	return true;
}

void Texture::Unload()
{
	//  ɾ������
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
	//  ���ÿ�Ⱥ͸߶�
	mWidth = width;
	mHeight = height;
	//  ����������󲢱���id
	glGenTextures(1, &mTextureID);
	//  ����
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	//  ���ó�ʼ����Ϊ�յ�ͼ����/�߶�
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, GL_RGB, GL_FLOAT, nullptr);
	//  ����������˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::SetActive(int index)
{
	//
	glActiveTexture(GL_TEXTURE0 + index);
	//  ����
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
