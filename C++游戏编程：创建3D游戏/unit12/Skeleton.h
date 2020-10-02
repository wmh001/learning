#pragma once
#include "BoneTransform.h"
#include <string>
#include <vector>

class Skeleton
{
public:
	//  骨骼
	struct Bone
	{
		//  位置和姿态
		BoneTransform mLocalBindPose;
		//  名字
		std::string mName;
		//  父骨骼
		int mParent;
	};
	//  加载
	bool Load(const std::string& fileName);
	//  获取骨骼数量
	size_t GetNumBones() const { return mBones.size(); }
	//  访问骨骼
	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	//  访问骨骼容器
	const std::vector<Bone>& GetBones() const { return mBones; }
	//  访问全局反向绑定姿势矩阵容器
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
protected:
	//  计算每个骨骼的全局反向绑定姿势矩阵
	void ComputeGlobalInvBindPose();
private:
	//  骨骼的容器
	std::vector<Bone> mBones;
	//  全局反向绑定姿势矩阵容器
	std::vector<Matrix4> mGlobalInvBindPoses;
};

