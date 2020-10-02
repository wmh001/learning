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
	//  创建缩放矩阵
	Matrix4 scale = Matrix4::CreateScale(mOwner->GetScale() * mOuterRadius / mesh->GetRadius());
	//  创建平移矩阵
	Matrix4 trans = Matrix4::CreateTranslation(mOwner->GetPosition());
	//  计算世界变化矩阵
	Matrix4 worldTransform = scale * trans;
	//  设置世界变换矩阵
	shader->SetMatrixUniform("uWorldTransform", worldTransform);
	//  设置位置
	shader->SetVectorUniform("uPointLight.mWorldPos", mOwner->GetPosition());
	//  设置颜色
	shader->SetVectorUniform("uPointLight.mDiffuseColor", mDiffuseColor);
	//  设置内半径
	shader->SetFloatUniform("uPointLight.mInnerRadius", mInnerRadius);
	//  设置外半径
	shader->SetFloatUniform("uPointLight.mOuterRadius", mOuterRadius);
	//  绘制球
	glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}
