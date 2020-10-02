#include "TargetActor.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"

TargetActor::TargetActor(Game* game)
	: Actor(game)
{
	//SetScale(10.0f);
	//  设置角度
	SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	//  创建网格组件
	MeshComponent* mc = new MeshComponent(this);
	//  设置网格
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Target.gpmesh");
	mc->SetMesh(mesh);
	//  创建方格组件
	BoxComponent* bc = new BoxComponent(this);
	//  设置方格
	bc->SetObjectBox(mesh->GetBox());
}