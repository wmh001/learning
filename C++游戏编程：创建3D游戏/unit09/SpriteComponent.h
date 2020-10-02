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
	//  绘制
	virtual void Draw(class Shader* shader);
	//  设置图像
	virtual void SetTexture(class Texture* texture);
	//  访问参数
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }
protected:
	//  图像
	class Texture* mTexture;
	//  绘制顺序
	int mDrawOrder;
	//  图像的宽和高
	int mTexWidth;
	int mTexHeight;
	//  是否可见
	bool mVisible;
};

