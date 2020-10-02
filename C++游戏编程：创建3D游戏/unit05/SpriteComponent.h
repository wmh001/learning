#pragma once
#include "Component.h"
#include "Shader.h"
#include "SDL.h"
#include "Texture.h"

class SpriteComponent :
    public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(Shader* shader);
	virtual void SetTexture(Texture* texture);
	//  访问
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
protected:
	//  图像
	class Texture* mTexture;
	//  画家算法的绘制顺序
	int mDrawOrder;
	//  图像的宽和高
	int mTexWidth;
	int mTexHeight;
};

