#pragma once
#include "Actor.h"

//  ����
class Grid :
    public Actor
{
public:
	Grid(class Game* game);
	//  ���������
	void ProcessClick(int x, int y);
	//  ʹ��A*����Ѱ·
	bool FindPath(class Tile* start, class Tile* goal);
	//  ������
	void BuildTower();
	//  ����
	void DestroyTower();
	//  ���ʿ�ʼ����
	class Tile* GetStartTile();
	//  ���ʽ�������
	class Tile* GetEndTile();
	//  ���½�ɫ
	void UpdateActor(float deltaTime) override;
private:
	//  ѡ�񷽸�
	void SelectTile(size_t row, size_t col);
	//  ����·������
	void UpdatePathTiles(class Tile* start);
	//  ��ǰѡ��ķ���
	class Tile* mSelectedTile;
	//  ÿ�������λ��
	std::vector<std::vector<class Tile*>> mTiles;
	//  ��һ�����˲�����ʱ��
	float mNextEnemy;
	//  ���̵���������
	const size_t NumRows = 7;
	const size_t NumCols = 16;
	//  ���Ͻǵ���ʼλ��
	const float StartY = 192.0f;
	//  ����ı߳�
	const float TileSize = 64.0f;
	//  �������˵�ʱ����
	const float EnemyTime = 1.5f;
};

