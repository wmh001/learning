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
	//  ����
	virtual void Draw(class Shader* shader);
	//  ����ͼ��
	virtual void SetTexture(class Texture* texture);
	//  ����
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
protected:
	//  ͼ��
	class Texture* mTexture;
	//  ����˳��
	int mDrawOrder;
	//  ͼ��Ŀ�͸�
	int mTexWidth;
	int mTexHeight;
};

