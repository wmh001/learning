#include "OrbitCamera.h"
#include "Actor.h"

OrbitCamera::OrbitCamera(Actor* owner)
	:CameraComponent(owner)
	, mOffset(-400.0f, 0.0f, 0.0f)
	, mUp(Vector3::UnitZ)
	, mPitchSpeed(0.0f)
	, mYawSpeed(0.0f)
{

}

void OrbitCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	//  ƫ����Ԫ��
	Quaternion yaw(Vector3::UnitZ, mYawSpeed * deltaTime);
	//  ����ƫ����
	mOffset = Vector3::Transform(mOffset, yaw);
	//  �����Ϸ�����
	mUp = Vector3::Transform(mUp, yaw);
	//  ����ǰ�������
	Vector3 forward = -1.0f * mOffset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(mUp, forward);
	right.Normalize();
	//  ������Ԫ��
	Quaternion pitch(right, mPitchSpeed * deltaTime);
	// ����ƫ����
	mOffset = Vector3::Transform(mOffset, pitch);
	//  �����Ϸ�����
	mUp = Vector3::Transform(mUp, pitch);
	//  Ŀ��λ��
	Vector3 target = mOwner->GetPosition();
	//  ���λ��
	Vector3 cameraPos = target + mOffset;
	//  ������ͼ����
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, mUp);
	//  ������ͼ����
	SetViewMatrix(view);
}
