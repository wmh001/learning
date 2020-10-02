#pragma once
#include "Actor.h"

class BallActor :
    public Actor
{
public:
	BallActor(class Game* game);
	//  更新角色
	void UpdateActor(float deltaTime) override;
	//  修改玩家
	void SetPlayer(Actor* player);
	//  中靶
	void HitTarget();
private:
	//  声音组件
	class AudioComponent* mAudioComp;
	//  球移动组件
	class BallMove* mMyMove;
	//  生活时间
	float mLifeSpan;
};

