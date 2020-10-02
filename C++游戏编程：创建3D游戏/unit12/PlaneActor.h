#pragma once
#include "Actor.h"

class PlaneActor :
    public Actor
{
public:
	PlaneActor(class Game* game);
	~PlaneActor();
	//  ���ʷ������
	class BoxComponent* GetBox() { return mBox; }
private:
	//  �������
	class BoxComponent* mBox;
};

