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
	//  ����
	void SetActive();
	//  �޸�
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	//  ͼ���opengl id
	unsigned int mTextureID;
	//  ͼ��Ŀ�Ⱥ͸߶�
	int mWidth;
	int mHeight;
};

