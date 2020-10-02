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
	//  �����ֺŵ�����
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
	//  Ϊÿ���ֺ���������
	for (auto& size : fontSizes)
	{
		//  ��������
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		//  ����ӳ��
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
	//  ת����ɫ��ʽ
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;
	//  �����ֺ�Ѱ������
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		//  ��ȡ����
		TTF_Font* font = iter->second;
		//  ���ݼ�ֵѰ������
		const std::string& actualText = mGame->GetText(textKey);
		//  ��������ʹ�ð�����͸������
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			//  ת��Ϊͼ��
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	//  ʧ�ܴ���
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return texture;
}
