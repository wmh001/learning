#include "FollowCamera.h"
#include "Actor.h"

FollowCamera::FollowCamera(Actor* owner)
	: CameraComponent(owner)
	, mHorzDist(350.0f)
	, mVertDist(150.0f)
	, mTargetDist(100.0f)
	, mSpringConstant(128.0f)
{

}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	//  ���ݵ��ɳ�����������
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	//  ��������λ��
	Vector3 idealPos = ComputeCameraPos();
	//  ��������λ����ʵ��λ�õĲ�
	Vector3 diff = mActualPos - idealPos;
	//  ���㵯�ɼ��ٶ�
	Vector3 acel = -mSpringConstant * diff - dampening * mVelocity;
	//  �����ٶ�
	mVelocity += acel * deltaTime;
	//  �������ʵ��λ��
	mActualPos += mVelocity * deltaTime;
	//  ����Ŀ���
	Vector3 target = mOwner->GetPosition() + mOwner->GetForward() * mTargetDist;
	//  ������ͼ����
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	//  ������ͼ����
	SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	//  ʵ��λ��������λ���غ�
	mActualPos = ComputeCameraPos();
	//  �ٶȳ�ʼ��Ϊ��
	mVelocity = Vector3::Zero;
	//  ����Ŀ���
	Vector3 target = mOwner->GetPosition() + mOwner->GetForward() * mTargetDist;
	//  ������ͼ����
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	//  ������ͼ����
	SetViewMatrix(view);
}

Vector3 FollowCamera::ComputeCameraPos() const
{
	//  �������λ��
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}
