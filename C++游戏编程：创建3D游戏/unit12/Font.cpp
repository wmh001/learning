#include "Font.h"
#include "Texture.h"
#include <vector>
#include "Game.h"

Font::Font(class Game* game)
	: mGame(game)
{

}

Font::~Font()
{

}

bool Font::Load(const std::string& fileName)
{
	//  创建字号的容器
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};
	//  为每个字号生成文字
	for (auto& size : fontSizes)
	{
		//  加载字体
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		//  进入映射
		mFontData.emplace(size, font);
	}
	return true;
}

void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

Texture* Font::RenderText(const std::string& textKey, const Vector3& color /*= Color::White*/, int pointSize /*= 24*/)
{
	Texture* texture = nullptr;
	//  转换颜色格式
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;
	//  依据字号寻找字体
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		//  获取字体
		TTF_Font* font = iter->second;
		//  根据键值寻找字体
		const std::string& actualText = mGame->GetText(textKey);
		//  绘制文字使用阿尔法透明处理
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			//  转换为图像
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	//  失败处理
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return texture;
}
