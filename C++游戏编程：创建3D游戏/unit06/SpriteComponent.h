#pragma once
#include "Component.h"
#include "Shader.h"
#include "Texture.h"
#include "SDL.h"

class SpriteComponent :
    public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	//  ����
    virtual void Draw(Shader* shader);
	//  ����ͼ��
	virtual void SetTexture(Texture* texture);
	//  ����
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
protected:
	//  ͼ��
	class Texture* mTexture;
	//  �����㷨�Ļ���˳��
	int mDrawOrder;
	//  ͼ��Ŀ�͸�
	int mTexWidth;
	int mTexHeight;
};

