#pragma once
#include <SDL.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

//  ����״̬
enum ButtonState
{
	ENone,  //  �ޱ仯
	EPressed,  //  ������
	EReleased,  //  ���ͷ�
	EHeld  //  ����
};

//  ����״̬
class KeyboardState
{
public:
	//  ������Ԫ��
	friend class InputSystem;
	//  ��ȡ��ֵ
	bool GetKeyValue(SDL_Scancode keyCode) const;
	//  ��ȡ����״̬
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	//  ��ǰ״̬��ָ��
	const Uint8* mCurrState;
	//  ����֮ǰ״̬������
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

//  ���״̬
class MouseState
{
public:
	//  ������Ԫ��
	friend class InputSystem;
	//  ��ȡ���λ��
	const Vector2& GetPosition() const { return mMousePos; }
	//  ��ȡ������״̬
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	//  �Ƿ���������˶�״̬
	bool IsRelative() const { return mIsRelative; }
	//  ��ȡ����ֵ
	bool GetButtonValue(int button) const;
	//  ��ȡ��갴��״̬
	ButtonState GetButtonState(int button) const;
private:
	//  ��ǰ���λ��
	Vector2 mMousePos;
	//  �����ֹ���
	Vector2 mScrollWheel;
	//  ��ǰ��갴��״̬
	Uint32 mCurrButtons;
	//  ֮ǰ��갴��״̬
	Uint32 mPrevButtons;
	//  �Ƿ���������˶�ģʽ
	bool mIsRelative;
};

class ControllerState
{
public:
	//  ������Ԫ��
	friend class InputSystem;
	//  ��ȡ����ֵ
	bool GetButtonValue(SDL_GameControllerButton button) const;
	//  ��ȡ����״̬
	ButtonState GetButtonState(SDL_GameControllerButton button) const;
	//  ������/��ҡ��
	const Vector2& GetLeftStick() const { return mLeftStick; }
	const Vector2& GetRightStick() const { return mRightStick; }
	//  ������/�Ұ��
	float GetLeftTrigger() const { return mLeftTrigger; }
	float GetRightTrigger() const { return mRightTrigger; }
	//  ��ѯ�Ƿ�����
	bool GetIsConnected() const { return mIsConnected; }
private:
	//  ��ǰ����״̬
	Uint8 mCurrButtons[SDL_CONTROLLER_BUTTON_MAX];
	//  ֮ǰ����״̬
	Uint8 mPrevButtons[SDL_CONTROLLER_BUTTON_MAX];
	// Left/right sticks
	Vector2 mLeftStick;
	Vector2 mRightStick;
	//  ���Ұ��
	float mLeftTrigger;
	float mRightTrigger;
	//  �Ƿ�����
	bool mIsConnected;
};

//  ����״̬
struct InputState
{
	//  ����״̬
	KeyboardState Keyboard;
	//  ���״̬
	MouseState Mouse;
	//  ������״̬
	ControllerState Controller;
};

class InputSystem
{
public:
	//  ��ʼ��
	bool Initialize();
	//  �ر�
	void Shutdown();
	//  ׼�������¼�
	void PrepareForUpdate();
	//  ����
	void Update();
	//  �����ִ���
	void ProcessEvent(union SDL_Event& event);
	//  ����״̬
	const InputState& GetState() const { return mState; }
	//  ����/��������˶�״̬
	void SetRelativeMouseMode(bool value);
private:
	//  ����һά��������
	float Filter1D(int input);
	//  ���˶�ά��������
	Vector2 Filter2D(int inputX, int inputY);
	//  ����״̬
	InputState mState;
	//  ������
	SDL_GameController* mController;
};

