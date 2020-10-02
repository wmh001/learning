#include "MeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "glew.h"

MeshComponent::MeshComponent(Actor* owner, bool isSkeletal)
	: Component(owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, mVisible(true)
	, mIsSkeletal(isSkeletal)
{
	mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		//  设定世界转换矩阵
		shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
		//  设定反射功率
		shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
		//  获取图像
		Texture* t = mMesh->GetTexture(mTextureIndex);
		//  激活
		if (t)
		{
			t->SetActive();
		}
		//  获取顶点数组
		VertexArray* va = mMesh->GetVertexArray();
		//  激活
		va->SetActive();
		//  绘制
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
