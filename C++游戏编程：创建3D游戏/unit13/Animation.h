#pragma once
#include "BoneTransform.h"
#include <vector>
#include <string>

class Animation
{
public:
	//  加载
	bool Load(const std::string& fileName);
	//  访问骨骼数量
	size_t GetNumBones() const { return mNumBones; }
	//  访问动画中的帧数
	size_t GetNumFrames() const { return mNumFrames; }
	//  访问动画的持续时间
	float GetDuration() const { return mDuration; }
	//  访问动画中每个帧的持续时间
	float GetFrameDuration() const { return mFrameDuration; }
	//  计算每个骨骼的全局姿势矩阵
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;
private:
	//  骨骼数量
	size_t mNumBones;
	//  动画中的帧数
	size_t mNumFrames;
	//  动画的持续时间
	float mDuration;
	//  动画中每个帧的持续时间
	float mFrameDuration;
	//  每个骨骼姿势组成的轨道
	std::vector<std::vector<BoneTransform>> mTracks;
};

