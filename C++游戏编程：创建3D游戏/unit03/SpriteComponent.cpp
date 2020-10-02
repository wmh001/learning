#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		//  按所有者的比例缩放宽度/高度
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		//  寻找中点
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		//  绘制
		SDL_RenderCopyEx(renderer,  //  渲染器
			mTexture,  //  图像
			nullptr,  //  图像需要旋转的矩形区域，null表示整个图像
			&r,  //  旋转后的图像绘制在背景上的矩形区域
			-Math::ToDegrees(mOwner->GetRotation()),  //  旋转的角度，单位圆正向与SDL正向相反
			nullptr,  //  围绕的点
			SDL_FLIP_NONE);  //  旋转的方式，其中SDL_FLIP_HORIZONTAL水平旋转,SDL_FLIP_VERTICAL垂直翻转,SDL_FLIP_NONE正常旋转
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//  设置高和宽
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
