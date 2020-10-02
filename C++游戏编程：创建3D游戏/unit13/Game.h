#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"
#include <SDL_types.h>

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
	//  ������ײϵͳ
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }
	//  ����ƽ����ʾ��
	class HUD* GetHUD() { return mHUD; }
	//  �����û�������Ļջ
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	//  ��ջ
	void PushUI(class UIScreen* screen);
	//  �������
	class FollowActor* GetPlayer() { return mFollowActor; }
	//  ��Ϸ״̬
	enum GameState
	{
		EGameplay,  //  ����
		EPaused,  //  ��ͣ
		EQuit  //  �˳�
	};
	//  ������Ϸ״̬
	GameState GetState() const { return mGameState; }
	//  �޸���Ϸ״̬
	void SetState(GameState state) { mGameState = state; }
	//  ��������
	class Font* GetFont(const std::string& fileName);
	//  ����gptext�ļ�����ӵ�ӳ����
	void LoadText(const std::string& fileName);
	//  ���ݼ�ֵ�����ַ���
	const std::string& GetText(const std::string& key);
	//  ���ݼ�ֵ������Ƥ����
	class Skeleton* GetSkeleton(const std::string& fileName);
	//  ���ݼ�ֵ���ʶ�������
	class Animation* GetAnimation(const std::string& fileName);
	//  ���ǽ
	void AddPlane(class PlaneActor* plane);
	//  �Ƴ�ǽ
	void RemovePlane(class PlaneActor* plane);
	//  ����ǽ
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
	//  ��������
	void LoadData();
	//  ɾ������
	void UnloadData();
	//  ��Ϸ�����н�ɫ������
	std::vector<class Actor*> mActors;
	//  �û�������Ļջ
	std::vector<class UIScreen*> mUIStack;
	//  �ļ����������ӳ��
	std::unordered_map<std::string, class Font*> mFonts;
	//  �ļ�������Ƥ������ӳ��
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	//  �ļ������������ݵ�ӳ��
	std::unordered_map<std::string, class Animation*> mAnims;
	//  Ӣ���ַ����������ַ�����ӳ��
	std::unordered_map<std::string, std::string> mText;
	//  �����ɫ����
	std::vector<class Actor*> mPendingActors;
	//  ��Ⱦ��
	class Renderer* mRenderer;
	//  ����ϵͳ
	class AudioSystem* mAudioSystem;
	//  ��ײϵͳ
	class PhysWorld* mPhysWorld;
	//  ƽ����ʾ��
	class HUD* mHUD;
	//  ��¼�ӵ���SDL_Init������ʼ�ĺ�����
	Uint32 mTicksCount;
	//  ��Ϸ״̬
	GameState mGameState;
	//  �Ƿ����ڸ��½�ɫ
	bool mUpdatingActors;
	//  ǽ����
	std::vector<class PlaneActor*> mPlanes;
	//  �������
	class FollowActor* mFollowActor;
	//  ׼��
	class SpriteComponent* mCrosshair;
	//  �����¼�
	SoundEvent mMusicEvent;
};

