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
	//  偏航四元数
	Quaternion yaw(Vector3::UnitZ, mYawSpeed * deltaTime);
	//  更新偏移量
	mOffset = Vector3::Transform(mOffset, yaw);
	//  更新上方向量
	mUp = Vector3::Transform(mUp, yaw);
	//  计算前向和右向
	Vector3 forward = -1.0f * mOffset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(mUp, forward);
	right.Normalize();
	//  俯仰四元数
	Quaternion pitch(right, mPitchSpeed * deltaTime);
	// 更新偏移量
	mOffset = Vector3::Transform(mOffset, pitch);
	//  更新上方向量
	mUp = Vector3::Transform(mUp, pitch);
	//  目标位置
	Vector3 target = mOwner->GetPosition();
	//  相机位置
	Vector3 cameraPos = target + mOffset;
	//  计算视图矩阵
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, mUp);
	//  设置视图矩阵
	SetViewMatrix(view);
}
