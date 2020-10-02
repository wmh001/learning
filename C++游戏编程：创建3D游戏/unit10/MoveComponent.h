#pragma once
#include "Component.h"

class MoveComponent :
    public Component
{
public:
    //  ��С�ĸ���˳��ʹ���ڴ�������֮ǰ����
    MoveComponent(class Actor* owner, int updateOrder = 10);
    //  ����
    void Update(float deltaTime) override;
    //  ���ʺ��޸Ľ��ٶȡ����ٶȺ���ת�ٶ�ָ��
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    float GetStrafeSpeed() const { return mStrafeSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
private:
    //  ���ٶ�
    float mAngularSpeed;
    //  ���ٶ�
    float mForwardSpeed;
    //  �����ٶ�
    float mStrafeSpeed;
};

