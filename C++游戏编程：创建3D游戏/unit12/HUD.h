#pragma once
#include "UIScreen.h"
#include <vector>

class HUD :
    public UIScreen
{
public:
	//  �ϵ͵Ļ�ͼ˳����Ϻ��˳�����Ӧ
	HUD(class Game* game);
	~HUD();
	//  ����
	void Update(float deltaTime) override;
	//  ����
	void Draw(class Shader* shader) override;
	//  ���Ŀ�����
	void AddTargetComponent(class TargetComponent* tc);
	//  ɾ��Ŀ�����
	void RemoveTargetComponent(class TargetComponent* tc);
protected:
	//  ����׼��
	void UpdateCrosshair(float deltaTime);
	//  �����״�
	void UpdateRadar(float deltaTime);
	//  Ѫ��
	class Texture* mHealthBar;
	//  �״�
	class Texture* mRadar;
	//  ��ͨ׼��
	class Texture* mCrosshair;
	//  ����׼׼��
	class Texture* mCrosshairEnemy;
	//  ���
	class Texture* mBlipTex;
	//  �״�����
	class Texture* mRadarArrow;
	//  Ŀ�����������
	std::vector<class TargetComponent*> mTargetComps;
	//  �״������λ������
	std::vector<Vector2> mBlips;
	//  �״ﷶΧ
	float mRadarRange;
	//  �״�뾶
	float mRadarRadius;
	//  �Ƿ���׼��Ŀ��
	bool mTargetEnemy;
};

