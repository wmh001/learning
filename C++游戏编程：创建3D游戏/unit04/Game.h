#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	//  ���캯��
	Game();
	//  ��ʼ��
	bool Initialize();
	//  ѭ��
	void RunLoop();
	//  ����
	void Shutdown();
	//  �����ɫ
	void AddActor(class Actor* actor);
	//  �Ƴ���ɫ
	void RemoveActor(class Actor* actor);
	//  ���뾫��
	void AddSprite(class SpriteComponent* sprite);
	//  �Ƴ�����
	void RemoveSprite(class SpriteComponent* sprite);
	//  �õ�ͼ��
	SDL_Texture* GetTexture(const std::string& fileName);
	class Grid* GetGrid() { return mGrid; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	std::vector<class Tower*>& GetTowers() { return mTowers; }
	class Enemy* GetNearestEnemy(const Vector2& pos);
private:
	//  ���봦��
	void ProcessInput();
	//  ������Ϸ
	void UpdateGame();
	//  ���ͼ��
	void GenerateOutput();
	//  ����ͼ��
	void LoadData();
	//  ɾ��ͼ��
	void UnloadData();
	//  ͼ�������
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	//  ��Ϸ�����н�ɫ������
	std::vector<class Actor*> mActors;
	//  �����ɫ����
	std::vector<class Actor*> mPendingActors;
	//  �������������
	std::vector<class SpriteComponent*> mSprites;
	//  ��������
	SDL_Window* mWindow;
	//  ������Ⱦ��
	SDL_Renderer* mRenderer;
	//  ��¼�ӵ���SDL_Init������ʼ�ĺ�����
	Uint32 mTicksCount;
	//  �Ƿ�Ӧ�ü�������
	bool mIsRunning;
	//  �Ƿ����ڸ��½�ɫ
	bool mUpdatingActors;
	//  ��������
	std::vector<class Enemy*> mEnemies;
	//  ������
	std::vector<class Tower*> mTowers;
	//  ����
	class Grid* mGrid;
	//  ��һ������
	float mNextEnemy;
};

