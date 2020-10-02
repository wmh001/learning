#pragma once
#include "CameraComponent.h"
#include <vector>

struct Spline
{
	//  ���Ƶ�����
	std::vector<Vector3> mControlPoints;
	//  �����������߶Σ�����startIdx=P1������tֵ����λ��
	Vector3 Compute(size_t startIdx, float t) const;
	//  ���Ƶ�����
	size_t GetNumPoints() const { return mControlPoints.size(); }
};

class SplineCamera :
    public CameraComponent
{
public:
	SplineCamera(class Actor* owner);
	//  ����
	void Update(float deltaTime) override;
	//  ����
	void Restart();
	//  �޸�
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetSpline(const Spline& spline) { mPath = spline; }
	void SetPaused(bool pause) { mPaused = pause; }
private:
	//  ��������
	Spline mPath;
	//  ��ǰ����
	size_t mIndex;
	//  tֵ
	float mT;
	//  t���ٶ�
	float mSpeed;
	//  �Ƿ��ƶ�
	bool mPaused;
};

