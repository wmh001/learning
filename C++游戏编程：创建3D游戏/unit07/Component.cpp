#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	: mOwner(owner)
	, mUpdateOrder(updateOrder)
{
	//  ����������ɫ��������
	mOwner->AddComponent(this);
}

Component::~Component()
{
	//  ������ӽ�ɫ�������Ƴ�
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{

}
