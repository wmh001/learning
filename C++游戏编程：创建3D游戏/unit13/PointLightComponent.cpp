#include "PointLightComponent.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "Actor.h"

PointLightComponent::PointLightComponent(Actor* owner)
	: Component(owner)
{
	owner->GetGame()->GetRenderer()->AddPointLight(this);
}

PointLightComponent::~PointLightComponent()
{
	mOwner->GetGame()->GetRenderer()->RemovePointLight(this);
}

void PointLightComponent::Draw(Shader* shader, Mesh* mesh)
{
	//  �������ž���
	Matrix4 scale = Matrix4::CreateScale(mOwner->GetScale() * mOuterRadius / mesh->GetRadius());
	//  ����ƽ�ƾ���
	Matrix4 trans = Matrix4::CreateTranslation(mOwner->GetPosition());
	//  ��������仯����
	Matrix4 worldTransform = scale * trans;
	//  ��������任����
	shader->SetMatrixUniform("uWorldTransform", worldTransform);
	//  ����λ��
	shader->SetVectorUniform("uPointLight.mWorldPos", mOwner->GetPosition());
	//  ������ɫ
	shader->SetVectorUniform("uPointLight.mDiffuseColor", mDiffuseColor);
	//  �����ڰ뾶
	shader->SetFloatUniform("uPointLight.mInnerRadius", mInnerRadius);
	//  ������뾶
	shader->SetFloatUniform("uPointLight.mOuterRadius", mOuterRadius);
	//  ������
	glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}
