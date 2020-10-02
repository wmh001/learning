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
		//  �������ž���
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		//  ��������任����
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		//  ��������任����
		shader->SetMatrixUniform("uWorldTransform", world);
		//  ����
		mTexture->SetActive();
		//  ����
		glDrawElements(GL_TRIANGLES  //  ���ڻ��Ƶ�Ԫ������
			, 6  //  ������������������
			, GL_UNSIGNED_INT  //  ������������
			, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	//  ���øߺͿ�
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}
