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
	//  组件更新
	CameraComponent::Update(deltaTime);
	//  相机位置等于角色位置
	Vector3 cameraPos = mOwner->GetPosition();
	//  计算俯仰角度
	mPitch += mPitchSpeed * deltaTime;
	//  限定范围
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
	//  计算四元数
	Quaternion q(mOwner->GetRight(), mPitch);
	//  计算前方
	Vector3 viewForward = Vector3::Transform(mOwner->GetForward(), q);
	//  计算目标方向
	Vector3 target = cameraPos + viewForward * 100.0f;
	//  计算上方
	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);
	//  计算视图矩阵
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	//  设置
	SetViewMatrix(view);
}
