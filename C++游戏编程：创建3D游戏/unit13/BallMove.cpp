#include "BallMove.h"
#include "Actor.h"
#include "Game.h"
#include "PhysWorld.h"
#include "TargetActor.h"
#include "BallActor.h"

BallMove::BallMove(Actor* owner)
	: MoveComponent(owner)
	, mPlayer(nullptr)
{

}

void BallMove::Update(float deltaTime)
{
	//  ���ƶ��������߶�
	//  ����
	const float segmentLength = 30.0f;
	//  ���
	Vector3 start = mOwner->GetPosition();
	//  ����
	Vector3 dir = mOwner->GetForward();
	//  �յ�
	Vector3 end = start + dir * segmentLength;
	//  �����߶�
	LineSegment l(start, end);
	//  ��ײ����
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();
	PhysWorld::CollisionInfo info;
	//  �Ƿ���ײ
	if (phys->SegmentCast(l, info) && info.mActor != mPlayer)
	{
		//  ��ɫ��������
		dir = Vector3::Reflect(dir, info.mNormal);
		//  �ı䳯��
		mOwner->RotateToNewForward(dir);
		//  ���а���
		TargetActor* target = dynamic_cast<TargetActor*>(info.mActor);
		if (target)
		{
			static_cast<BallActor*>(mOwner)->HitTarget();
		}
	}
	//  �������
	MoveComponent::Update(deltaTime);
}
