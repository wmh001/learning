#pragma once
#include "Component.h"

class MoveComponentL :
    public Component
{
public:
    //  更小的更新顺序使其在大多数组件之前更新
    MoveComponentL(class Actor* owner, int updateOrder = 10);
    //  更新
    void Update(float deltaTime) override;
    //  访问和设置
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
    //  角速度
    float mAngularSpeed;
    //  线速度
    float mForwardSpeed;
};

