#include "PhysWorld.h"
#include <algorithm>
#include "BoxComponent.h"
#include <SDL.h>

PhysWorld::PhysWorld(Game* game)
	: mGame(game)
{

}

bool PhysWorld::SegmentCast(const LineSegment& l, CollisionInfo& outColl)
{
	bool collided = false;
	//  初始化t为无穷大
	float closestT = Math::Infinity;
	//  法线
	Vector3 norm;
	//  相交测试
	for (auto box : mBoxes)
	{
		//  t值
		float t;
		//  是否相交
		if (Intersect(l, box->GetWorldBox(), t, norm))
		{
			//  选择t值最小的交点
			if (t < closestT)
			{
				outColl.mPoint = l.PointOnSegment(t);
				outColl.mNormal = norm;
				outColl.mBox = box;
				outColl.mActor = box->GetOwner();
				collided = true;
				closestT = t;
			}
		}
	}
	return collided;
}

void PhysWorld::TestPairwise(std::function<void(Actor*, Actor*)> f)
{
	//  O(n^2)
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			//  取组件
			BoxComponent* a = mBoxes[i];
			BoxComponent* b = mBoxes[j];
			//  碰撞检测
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				//  碰撞处理
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::TestSweepAndPrune(std::function<void(Actor*, Actor*)> f)
{
	//  min.x大小排序
	std::sort(mBoxes.begin(), mBoxes.end(),
	    [](BoxComponent* a, BoxComponent* b) {
			return a->GetWorldBox().mMin.x <
				b->GetWorldBox().mMin.x;
		});

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		//  获取当前方格的max.x
		BoxComponent* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxComponent* b = mBoxes[j];
			// AABB[j] min大于AABB[i] max则排除
			if (b->GetWorldBox().mMin.x > max)
			{
				break;
			}
			else if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				//  碰撞处理
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::AddBox(BoxComponent* box)
{
	mBoxes.emplace_back(box);
}

void PhysWorld::RemoveBox(BoxComponent* box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}
}
