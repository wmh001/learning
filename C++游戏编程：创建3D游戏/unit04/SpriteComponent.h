#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent :
    public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);
	//  ����
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
protected:
	//  ͼ��
	SDL_Texture* mTexture;
	//  �����㷨�Ļ���˳��
	int mDrawOrder;
	//  ͼ��Ŀ�͸�
	int mTexWidth;
	int mTexHeight;
};

