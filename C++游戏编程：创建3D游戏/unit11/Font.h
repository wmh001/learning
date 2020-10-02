#pragma once
#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include "Math.h"

class Font
{
public:
	Font(class Game* game);
	~Font();
	//  加载/卸载字体
	bool Load(const std::string& fileName);
	void Unload();
	//  字符串转换为图像
	class Texture* RenderText(const std::string& textKey, const Vector3& color = Color::White, int pointSize = 30);
private:
	//  字号到文字的映射
	std::unordered_map<int, TTF_Font*> mFontData;
	//  所属游戏
	class Game* mGame;
};

