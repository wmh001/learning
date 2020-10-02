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
		//  �趨����ת������
		shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
		//  �趨���书��
		shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
		//  ��ȡͼ��
		Texture* t = mMesh->GetTexture(mTextureIndex);
		//  ����
		if (t)
		{
			t->SetActive();
		}
		//  ��ȡ��������
		VertexArray* va = mMesh->GetVertexArray();
		//  ����
		va->SetActive();
		//  ����
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
