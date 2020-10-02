#include "SplineCamera.h"
#include "Actor.h"

Vector3 Spline::Compute(size_t startIdx, float t) const
{
	//  检查起始id是否不在范围内
	if (startIdx >= mControlPoints.size())
	{
		return mControlPoints.back();
	}
	else if (startIdx == 0)
	{
		return mControlPoints[startIdx];
	}
	else if (startIdx + 2 >= mControlPoints.size())
	{
		return mControlPoints[startIdx];
	}
	//  获取全部控制点
	Vector3 p0 = mControlPoints[startIdx - 1];
	Vector3 p1 = mControlPoints[startIdx];
	Vector3 p2 = mControlPoints[startIdx + 1];
	Vector3 p3 = mControlPoints[startIdx + 2];
	// 计算位置
	Vector3 position = 0.5f * ((2.0f * p1) + (-1.0f * p0 + p2) * t +
		(2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t +
		(-1.0f * p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t);
	return position;
}

SplineCamera::SplineCamera(Actor* owner)
	: CameraComponent(owner)
	, mIndex(1)
	, mT(0.0f)
	, mSpeed(0.5f)
	, mPaused(true)
{

}

void SplineCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	//  更新t值
	if (!mPaused)
	{
		mT += mSpeed * deltaTime;
		//  假设速度不是太快，跳过多个控制点
		if (mT >= 1.0f)
		{
			//  确保控制点足够
			if (mIndex < mPath.GetNumPoints() - 3)
			{
				mIndex++;
				mT = mT - 1.0f;
			}
			else
			{
				//  移动
				mPaused = true;
			}
		}
	}
	//  计算相机位置
	Vector3 cameraPos = mPath.Compute(mIndex, mT);
	//  目标点
	Vector3 target = mPath.Compute(mIndex, mT + 0.01f);
	//  获取上方向量
	const Vector3 up = Vector3::UnitZ;
	//  计算视图矩阵
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	//  设置视图矩阵
	SetViewMatrix(view);
}

void SplineCamera::Restart()
{
	//  重置
	mIndex = 1;
	mT = 0.0f;
	mPaused = false;
}
