#pragma once
#include "BoneTransform.h"
#include <string>
#include <vector>

class Skeleton
{
public:
	//  ����
	struct Bone
	{
		//  λ�ú���̬
		BoneTransform mLocalBindPose;
		//  ����
		std::string mName;
		//  ������
		int mParent;
	};
	//  ����
	bool Load(const std::string& fileName);
	//  ��ȡ��������
	size_t GetNumBones() const { return mBones.size(); }
	//  ���ʹ���
	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	//  ���ʹ�������
	const std::vector<Bone>& GetBones() const { return mBones; }
	//  ����ȫ�ַ�������ƾ�������
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
protected:
	//  ����ÿ��������ȫ�ַ�������ƾ���
	void ComputeGlobalInvBindPose();
private:
	//  ����������
	std::vector<Bone> mBones;
	//  ȫ�ַ�������ƾ�������
	std::vector<Matrix4> mGlobalInvBindPoses;
};

