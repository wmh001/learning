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
	//  ��ʼ��tΪ�����
	float closestT = Math::Infinity;
	//  ����
	Vector3 norm;
	//  �ཻ����
	for (auto box : mBoxes)
	{
		//  tֵ
		float t;
		//  �Ƿ��ཻ
		if (Intersect(l, box->GetWorldBox(), t, norm))
		{
			//  ѡ��tֵ��С�Ľ���
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
			//  ȡ���
			BoxComponent* a = mBoxes[i];
			BoxComponent* b = mBoxes[j];
			//  ��ײ���
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				//  ��ײ����
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::TestSweepAndPrune(std::function<void(Actor*, Actor*)> f)
{
	//  min.x��С����
	std::sort(mBoxes.begin(), mBoxes.end(),
	    [](BoxComponent* a, BoxComponent* b) {
			return a->GetWorldBox().mMin.x <
				b->GetWorldBox().mMin.x;
		});

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		//  ��ȡ��ǰ�����max.x
		BoxComponent* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxComponent* b = mBoxes[j];
			// AABB[j] min����AABB[i] max���ų�
			if (b->GetWorldBox().mMin.x > max)
			{
				break;
			}
			else if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				//  ��ײ����
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
