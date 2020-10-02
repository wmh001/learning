#pragma once
#include "BoneTransform.h"
#include <vector>
#include <string>

class Animation
{
public:
	//  ����
	bool Load(const std::string& fileName);
	//  ���ʹ�������
	size_t GetNumBones() const { return mNumBones; }
	//  ���ʶ����е�֡��
	size_t GetNumFrames() const { return mNumFrames; }
	//  ���ʶ����ĳ���ʱ��
	float GetDuration() const { return mDuration; }
	//  ���ʶ�����ÿ��֡�ĳ���ʱ��
	float GetFrameDuration() const { return mFrameDuration; }
	//  ����ÿ��������ȫ�����ƾ���
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;
private:
	//  ��������
	size_t mNumBones;
	//  �����е�֡��
	size_t mNumFrames;
	//  �����ĳ���ʱ��
	float mDuration;
	//  ������ÿ��֡�ĳ���ʱ��
	float mFrameDuration;
	//  ÿ������������ɵĹ��
	std::vector<std::vector<BoneTransform>> mTracks;
};

