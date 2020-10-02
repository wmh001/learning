#pragma once
#include "Actor.h"

class Tile :
    public Actor
{
public:
	//  ����
	friend class Grid;
	//  ����״̬
	enum TileState
	{
		//  Ĭ��
		EDefault,
		//  ·��
		EPath,
		//  ��ʼ
		EStart,
		//  ����
		EBase
	};
	//  ����
	Tile(class Game* game);
	//  �޸������
	void SetTileState(TileState state);
	TileState GetTileState() const { return mTileState; }
	//  ����ѡ
	void ToggleSelect();
	//  �õ���һ���ڵ�
	const Tile* GetParent() const { return mParent; }
private:
	//  ���ڵ�
	std::vector<Tile*> mAdjacent;
	//  ���ڵ�
	Tile* mParent;
	//  f(x)
	float f;
	//  ʵ��·���ɱ�
	float g;
	//  heuristic����
	float h;
	//  �Ƿ��ڿ�����
	bool mInOpenSet;
	//  �Ƿ��ڱռ���
	bool mInClosedSet;
	//  �Ƿ�Ϊ�ϰ�
	bool mBlocked;
	//  ����ͼ��
	void UpdateTexture();
	//  �������
	class SpriteComponent* mSprite;
	//  ״̬
	TileState mTileState;
	//  �Ƿ�ѡ��
	bool mSelected;
};

