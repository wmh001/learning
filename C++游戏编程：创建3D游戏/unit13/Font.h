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
	//  ��������
	bool Load(const std::string& fileName);
	//  ж������
	void Unload();
	//  �ַ���ת��Ϊͼ��
	class Texture* RenderText(const std::string& textKey, const Vector3& color = Color::White, int pointSize = 30);
private:
	//  �ֺŵ����ֵ�ӳ��
	std::unordered_map<int, TTF_Font*> mFontData;
	//  ������Ϸ
	class Game* mGame;
};

