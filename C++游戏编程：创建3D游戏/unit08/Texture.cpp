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
	//  ����˫���Թ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::Unload()
{
	//  ɾ������
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	//  ����
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

