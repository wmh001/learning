#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	//  加载文件
	bool Load(const std::string& fileName);
	//  卸载文件
	void Unload();
	//  转换为图像
	void CreateFromSurface(struct SDL_Surface* surface);
	//  激活
	void SetActive();
	//  修改
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	//  图像的opengl id
	unsigned int mTextureID;
	//  图像的宽度和高度
	int mWidth;
	int mHeight;
};

