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
	class Texture* GetTexture(const std::string& fileName);
	//  ������ʯ
	void AddAsteroid(class Asteroid* ast);
	//  �Ƴ���ʯ
	void RemoveAsteroid(class Asteroid* ast);
	//  ������ʯ
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
private:
	//  ���봦��
	void ProcessInput();
	//  ������Ϸ
	void UpdateGame();
	//  ���ͼ��
	void GenerateOutput();
    //  ������ɫ��
	bool LoadShaders();
	//  ������������
	void CreateSpriteVerts();
	//  ����ͼ��
	void LoadData();
	//  ɾ��ͼ��
	void UnloadData();
	//  ͼ�������
	std::unordered_map<std::string, class Texture*> mTextures;
	//  ��Ϸ�����н�ɫ������
	std::vector<class Actor*> mActors;
	//  �����ɫ����
	std::vector<class Actor*> mPendingActors;
	//  �������������
	std::vector<class SpriteComponent*> mSprites;
	//  ��ɫ��
	class Shader* mSpriteShader;
	//  ��������
	class VertexArray* mSpriteVerts;
	//  ��������
	SDL_Window* mWindow;
	//  opengl������
	SDL_GLContext mContext;
	//  ��¼�ӵ���SDL_Init������ʼ�ĺ�����
	Uint32 mTicksCount;
	//  �Ƿ�Ӧ�ü�������
	bool mIsRunning;
	//  �Ƿ����ڸ��½�ɫ
	bool mUpdatingActors;
	//  �ɴ�
	class Ship* mShip;
	//  ��ʯ������
	std::vector<class Asteroid*> mAsteroids;
};

