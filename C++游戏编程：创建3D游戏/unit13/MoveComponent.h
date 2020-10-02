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
    //  ���ʽ��ٶ�
    float GetAngularSpeed() const { return mAngularSpeed; }
    //  �������ٶ�
    float GetForwardSpeed() const { return mForwardSpeed; }
    //  ���ʲ����ٶ�
    float GetStrafeSpeed() const { return mStrafeSpeed; }
    //  �޸Ľ��ٶ�
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    //  �޸����ٶ�
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    //  �޸Ĳ����ٶ�
    void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
private:
    //  ���ٶ�
    float mAngularSpeed;
    //  ���ٶ�
    float mForwardSpeed;
    //  �����ٶ�
    float mStrafeSpeed;
};

