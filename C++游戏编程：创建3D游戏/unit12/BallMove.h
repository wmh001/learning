#pragma once
#include "MoveComponent.h"

class BallMove :
    public MoveComponent
{
public:
	BallMove(class Actor* owner);
	//  设置玩家
	void SetPlayer(Actor* player) { mPlayer = player; }
	//  更新
	void Update(float deltaTime) override;
protected:
	//  玩家
	class Actor* mPlayer;
};

