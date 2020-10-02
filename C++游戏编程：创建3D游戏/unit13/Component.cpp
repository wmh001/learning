#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	: mOwner(owner)
	, mUpdateOrder(updateOrder)
{
	//  将组件加入角色的容器中
	mOwner->AddComponent(this);
}

Component::~Component()
{
	//  将组件从角色容器中移除
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{

}
