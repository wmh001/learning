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
		//  �������ߵı������ſ��/�߶�
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		//  Ѱ���е�
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		//  ����
		SDL_RenderCopyEx(renderer,  //  ��Ⱦ��
			mTexture,  //  ͼ��
			nullptr,  //  ͼ����Ҫ��ת�ľ�������null��ʾ����ͼ��
			&r,  //  ��ת���ͼ������ڱ����ϵľ�������
			-Math::ToDegrees(mOwner->GetRotation()),  //  ��ת�ĽǶȣ���λԲ������SDL�����෴
			nullptr,  //  Χ�Ƶĵ�
			SDL_FLIP_NONE);  //  ��ת�ķ�ʽ������SDL_FLIP_HORIZONTALˮƽ��ת,SDL_FLIP_VERTICAL��ֱ��ת,SDL_FLIP_NONE������ת
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//  ���øߺͿ�
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
