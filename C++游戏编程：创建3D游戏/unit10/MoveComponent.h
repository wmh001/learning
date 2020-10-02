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
    //  访问和修改角速度、线速度和旋转速度指数
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    float GetStrafeSpeed() const { return mStrafeSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
private:
    //  角速度
    float mAngularSpeed;
    //  线速度
    float mForwardSpeed;
    //  侧向速度
    float mStrafeSpeed;
};

