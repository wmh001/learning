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
	//  沿移动方向建造线段
	//  长度
	const float segmentLength = 30.0f;
	//  起点
	Vector3 start = mOwner->GetPosition();
	//  方向
	Vector3 dir = mOwner->GetForward();
	//  终点
	Vector3 end = start + dir * segmentLength;
	//  创建线段
	LineSegment l(start, end);
	//  碰撞测试
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();
	PhysWorld::CollisionInfo info;
	//  是否碰撞
	if (phys->SegmentCast(l, info) && info.mActor != mPlayer)
	{
		//  角色反射向量
		dir = Vector3::Reflect(dir, info.mNormal);
		//  改变朝向
		mOwner->RotateToNewForward(dir);
		//  击中靶子
		TargetActor* target = dynamic_cast<TargetActor*>(info.mActor);
		if (target)
		{
			static_cast<BallActor*>(mOwner)->HitTarget();
		}
	}
	//  基类更新
	MoveComponent::Update(deltaTime);
}
