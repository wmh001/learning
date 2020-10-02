#pragma once
#include "Component.h"

class MoveComponentL :
    public Component
{
public:
    //  ��С�ĸ���˳��ʹ���ڴ�������֮ǰ����
    MoveComponentL(class Actor* owner, int updateOrder = 10);
    //  ����
    void Update(float deltaTime) override;
    //  ���ʺ�����
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
    //  ���ٶ�
    float mAngularSpeed;
    //  ���ٶ�
    float mForwardSpeed;
};

