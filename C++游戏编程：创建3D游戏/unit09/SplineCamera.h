#pragma once
#include "CameraComponent.h"
#include <vector>

struct Spline
{
	//  控制点容器
	std::vector<Vector3> mControlPoints;
	//  给定样条曲线段，其中startIdx=P1，根据t值计算位置
	Vector3 Compute(size_t startIdx, float t) const;
	//  控制点数量
	size_t GetNumPoints() const { return mControlPoints.size(); }
};

class SplineCamera :
    public CameraComponent
{
public:
	SplineCamera(class Actor* owner);
	//  更新
	void Update(float deltaTime) override;
	//  重启
	void Restart();
	//  修改
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetSpline(const Spline& spline) { mPath = spline; }
	void SetPaused(bool pause) { mPaused = pause; }
private:
	//  样条曲线
	Spline mPath;
	//  当前索引
	size_t mIndex;
	//  t值
	float mT;
	//  t的速度
	float mSpeed;
	//  是否移动
	bool mPaused;
};

