#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"

class PhysWorld
{
public:
	PhysWorld(class Game* game);
	//  碰撞信息
	struct CollisionInfo
	{
		//  交点位置
		Vector3 mPoint;
		//  交点法线
		Vector3 mNormal;
		//  发生碰撞的方盒
		class BoxComponent* mBox;
		//  方盒所属角色
		class Actor* mActor;
	};
	//  检测一线段与世界中所有方盒是否相交
	bool SegmentCast(const LineSegment& l, CollisionInfo& outColl);
	//  碰撞检测
	void TestPairwise(std::function<void(class Actor*, class Actor*)> f);
	//  扫描修剪算法
	void TestSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);
	//  加入/移除方盒组件
	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);
private:
	//  所属游戏
	class Game* mGame;
	//  方盒组件的容器
	std::vector<class BoxComponent*> mBoxes;
};

