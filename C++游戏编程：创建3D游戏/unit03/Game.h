#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

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

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	//  �õ�����
	SDL_Texture* GetTexture(const std::string& fileName);
	//  ��Ϸ���ԣ�����/�Ƴ���ʯ��
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	//  �õ���ʯ����
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
private:
	//  ���봦��
	void ProcessInput();
	//  ������Ϸ
	void UpdateGame();
	//  ���ͼ��
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//  ��Ϸ�����н�ɫ������
	std::vector<class Actor*> mActors;
	//  �����ɫ����
	std::vector<class Actor*> mPendingActors;
	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;
	//  ��������
	SDL_Window* mWindow;
	//  ������Ⱦ��
	SDL_Renderer* mRenderer;
	//  ��¼�ӵ���SDL_Init������ʼ�ĺ�����
	Uint32 mTicksCount;
	//  �Ƿ�Ӧ�ü�������
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	//  �ɴ�
	class Ship* mShip;
	//  ��ʯ������
	std::vector<class Asteroid*> mAsteroids;
};

