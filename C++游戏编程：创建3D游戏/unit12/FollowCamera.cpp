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
	//  根据弹簧常数计算阻尼
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	//  计算理想位置
	Vector3 idealPos = ComputeCameraPos();
	//  计算理想位置与实际位置的差
	Vector3 diff = mActualPos - idealPos;
	//  计算弹簧加速度
	Vector3 acel = -mSpringConstant * diff - dampening * mVelocity;
	//  更新速度
	mVelocity += acel * deltaTime;
	//  更新相机实际位置
	mActualPos += mVelocity * deltaTime;
	//  计算目标点
	Vector3 target = mOwner->GetPosition() + mOwner->GetForward() * mTargetDist;
	//  计算视图矩阵
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	//  设置视图矩阵
	SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	//  实际位置与理想位置重合
	mActualPos = ComputeCameraPos();
	//  速度初始化为零
	mVelocity = Vector3::Zero;
	//  计算目标点
	Vector3 target = mOwner->GetPosition() + mOwner->GetForward() * mTargetDist;
	//  计算视图矩阵
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	//  设置视图矩阵
	SetViewMatrix(view);
}

Vector3 FollowCamera::ComputeCameraPos() const
{
	//  计算相机位置
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}
