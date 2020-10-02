#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	//  �����ļ�
	bool Load(const std::string& fileName);
	//  ж���ļ�
	void Unload();
	//  ת��Ϊͼ��
	void CreateFromSurface(struct SDL_Surface* surface);
	//  ������Ⱦ��ͼ����
	void CreateForRendering(int width, int height, unsigned int format);
	//  ����
	void SetActive(int index = 0);
	//  �޸�
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	//
	unsigned int GetTextureID() const { return mTextureID; }
private:
	//  ͼ���opengl id
	unsigned int mTextureID;
	//  ͼ��Ŀ�Ⱥ͸߶�
	int mWidth;
	int mHeight;
};

