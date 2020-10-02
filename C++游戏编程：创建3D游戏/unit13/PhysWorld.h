#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"

class PhysWorld
{
public:
	PhysWorld(class Game* game);
	//  ��ײ��Ϣ
	struct CollisionInfo
	{
		//  ����λ��
		Vector3 mPoint;
		//  ���㷨��
		Vector3 mNormal;
		//  ������ײ�ķ���
		class BoxComponent* mBox;
		//  ����������ɫ
		class Actor* mActor;
	};
	//  ���һ�߶������������з����Ƿ��ཻ
	bool SegmentCast(const LineSegment& l, CollisionInfo& outColl);
	//  ��ײ���
	void TestPairwise(std::function<void(class Actor*, class Actor*)> f);
	//  ɨ���޼��㷨
	void TestSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);
	//  ����/�Ƴ��������
	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);
private:
	//  ������Ϸ
	class Game* mGame;
	//  �������������
	std::vector<class BoxComponent*> mBoxes;
};

