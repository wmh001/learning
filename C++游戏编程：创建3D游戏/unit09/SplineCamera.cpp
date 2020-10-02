#include "SplineCamera.h"
#include "Actor.h"

Vector3 Spline::Compute(size_t startIdx, float t) const
{
	//  �����ʼid�Ƿ��ڷ�Χ��
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
	//  ��ȡȫ�����Ƶ�
	Vector3 p0 = mControlPoints[startIdx - 1];
	Vector3 p1 = mControlPoints[startIdx];
	Vector3 p2 = mControlPoints[startIdx + 1];
	Vector3 p3 = mControlPoints[startIdx + 2];
	// ����λ��
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
	//  ����tֵ
	if (!mPaused)
	{
		mT += mSpeed * deltaTime;
		//  �����ٶȲ���̫�죬����������Ƶ�
		if (mT >= 1.0f)
		{
			//  ȷ�����Ƶ��㹻
			if (mIndex < mPath.GetNumPoints() - 3)
			{
				mIndex++;
				mT = mT - 1.0f;
			}
			else
			{
				//  �ƶ�
				mPaused = true;
			}
		}
	}
	//  �������λ��
	Vector3 cameraPos = mPath.Compute(mIndex, mT);
	//  Ŀ���
	Vector3 target = mPath.Compute(mIndex, mT + 0.01f);
	//  ��ȡ�Ϸ�����
	const Vector3 up = Vector3::UnitZ;
	//  ������ͼ����
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	//  ������ͼ����
	SetViewMatrix(view);
}

void SplineCamera::Restart()
{
	//  ����
	mIndex = 1;
	mT = 0.0f;
	mPaused = false;
}
