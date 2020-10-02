#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"

class Game
{
public:
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
	//  ��������ϵͳ
	class AudioSystem* GetAudioSystem() { return mAudioSystem; }
	//
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }
	//
	void AddPlane(class PlaneActor* plane);
	//
	void RemovePlane(class PlaneActor* plane);
	//
	std::vector<class PlaneActor*>& GetPlanes() { return mPlanes; }
private:
	//  ���봦��
	void ProcessInput();
	//  ���ֱ�����
	void HandleKeyPress(int key);
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
	//  ����ϵͳ
	class AudioSystem* mAudioSystem;
	//
	class PhysWorld* mPhysWorld;
	//  ��¼�ӵ���SDL_Init������ʼ�ĺ�����
	Uint32 mTicksCount;
	//  �Ƿ�Ӧ�ü�������
	bool mIsRunning;
	//  �Ƿ����ڸ��½�ɫ
	bool mUpdatingActors;
	//
	std::vector<class PlaneActor*> mPlanes;
	//  FPS���
	class FPSActor* mFPSActor;
	//  ׼��
	class SpriteComponent* mCrosshair;
	//  �����¼�
	SoundEvent mMusicEvent;
};

