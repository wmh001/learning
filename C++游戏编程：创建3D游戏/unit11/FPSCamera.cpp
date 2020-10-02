#include "FPSCamera.h"
#include "Actor.h"

FPSCamera::FPSCamera(Actor* owner)
	: CameraComponent(owner)
	, mPitchSpeed(0.0f)
	, mMaxPitch(Math::Pi / 3.0f)
	, mPitch(0.0f)
{

}

void FPSCamera::Update(float deltaTime)
{
	//  �������
	CameraComponent::Update(deltaTime);
	//  ���λ�õ��ڽ�ɫλ��
	Vector3 cameraPos = mOwner->GetPosition();
	//  ���㸩���Ƕ�
	mPitch += mPitchSpeed * deltaTime;
	//  �޶���Χ
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
	//  ������Ԫ��
	Quaternion q(mOwner->GetRight(), mPitch);
	//  ����ǰ��
	Vector3 viewForward = Vector3::Transform(mOwner->GetForward(), q);
	//  ����Ŀ�귽��
	Vector3 target = cameraPos + viewForward * 100.0f;
	//  �����Ϸ�
	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);
	//  ������ͼ����
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	//  ����
	SetViewMatrix(view);
}
