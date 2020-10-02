#include "PlaneActor.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"

PlaneActor::PlaneActor(Game* game)
	: Actor(game)
{
	//  设置比例
	SetScale(10.0f);
	//  创建网格组件
	MeshComponent* mc = new MeshComponent(this);
	//  定义网格
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh");
	//  设置网格
	mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
	//  创建方盒组件
	mBox = new BoxComponent(this);
	//  设置方盒
	mBox->SetObjectBox(mesh->GetBox());
	//  添加角色
	game->AddPlane(this);
}

PlaneActor::~PlaneActor()
{
	//  移除角色
	GetGame()->RemovePlane(this);
}
