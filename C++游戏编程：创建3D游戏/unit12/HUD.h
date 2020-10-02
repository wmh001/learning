#pragma once
#include "UIScreen.h"
#include <vector>

class HUD :
    public UIScreen
{
public:
	//  较低的绘图顺序与较后的顺序相对应
	HUD(class Game* game);
	~HUD();
	//  更新
	void Update(float deltaTime) override;
	//  绘制
	void Draw(class Shader* shader) override;
	//  添加目标组件
	void AddTargetComponent(class TargetComponent* tc);
	//  删除目标组件
	void RemoveTargetComponent(class TargetComponent* tc);
protected:
	//  更新准星
	void UpdateCrosshair(float deltaTime);
	//  更新雷达
	void UpdateRadar(float deltaTime);
	//  血条
	class Texture* mHealthBar;
	//  雷达
	class Texture* mRadar;
	//  普通准星
	class Texture* mCrosshair;
	//  已瞄准准星
	class Texture* mCrosshairEnemy;
	//  光点
	class Texture* mBlipTex;
	//  雷达中心
	class Texture* mRadarArrow;
	//  目标组件的容器
	std::vector<class TargetComponent*> mTargetComps;
	//  雷达光点相对位置容器
	std::vector<Vector2> mBlips;
	//  雷达范围
	float mRadarRange;
	//  雷达半径
	float mRadarRadius;
	//  是否瞄准了目标
	bool mTargetEnemy;
};

