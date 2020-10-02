#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "glew.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		//  创建缩放矩阵
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		//  计算世界变换矩阵
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		//  传输世界变换矩阵
		shader->SetMatrixUniform("uWorldTransform", world);
		//  激活
		mTexture->SetActive();
		//  绘制
		glDrawElements(GL_TRIANGLES  //  正在绘制的元素类型
			, 6  //  索引缓冲区索引数量
			, GL_UNSIGNED_INT  //  索引数据类型
			, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	//  设置高和宽
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}
