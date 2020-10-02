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
	//  ������Ⱦ��
	class Renderer* GetRenderer() { return mRenderer; }
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
	//  ��Ϸ�����н�ɫ������
	std::vector<class Actor*> mActors;
	//  �����ɫ����
	std::vector<class Actor*> mPendingActors;
	//  ��Ⱦ��
	class Renderer* mRenderer;
	//  ��¼�ӵ���SDL_Init������ʼ�ĺ�����
	Uint32 mTicksCount;
	//  �Ƿ�Ӧ�ü�������
	bool mIsRunning;
	//  �Ƿ����ڸ��½�ɫ
	bool mUpdatingActors;
	//
	class CameraActor* mCameraActor;
};

