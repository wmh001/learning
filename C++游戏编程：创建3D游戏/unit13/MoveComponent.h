#pragma once
#include "Component.h"

class MoveComponent :
    public Component
{
public:
    //  更小的更新顺序使其在大多数组件之前更新
    MoveComponent(class Actor* owner, int updateOrder = 10);
    //  更新
    void Update(float deltaTime) override;
    //  访问角速度
    float GetAngularSpeed() const { return mAngularSpeed; }
    //  访问线速度
    float GetForwardSpeed() const { return mForwardSpeed; }
    //  访问侧向速度
    float GetStrafeSpeed() const { return mStrafeSpeed; }
    //  修改角速度
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    //  修改线速度
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    //  修改侧向速度
    void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
private:
    //  角速度
    float mAngularSpeed;
    //  线速度
    float mForwardSpeed;
    //  侧向速度
    float mStrafeSpeed;
};

