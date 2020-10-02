#pragma once
#include "Actor.h"

class PlaneActor :
    public Actor
{
public:
	PlaneActor(class Game* game);
	~PlaneActor();
	//  访问方盒组件
	class BoxComponent* GetBox() { return mBox; }
private:
	//  方盒组件
	class BoxComponent* mBox;
};

