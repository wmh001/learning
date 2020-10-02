#include "InputSystem.h"
#include <SDL.h>
#include <cstring>

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
    //  �����Ƿ���
	return mCurrState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (mPrevState[keyCode] == 0)
	{
		//  �ޱ仯
		if (mCurrState[keyCode] == 0)
		{
			return ENone;
		}
		//  ������
		else
		{
			return EPressed;
		}
	}
	else
	{
		//  ���ͷ�
		if (mCurrState[keyCode] == 0)
		{
			return EReleased;
		}
		//  ����
		else
		{
			return EHeld;
		}
	}
}

bool MouseState::GetButtonValue(int button) const
{
	//  �Ƿ���
	return (SDL_BUTTON(button) & mCurrButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
	//  ��ȡ����״̬
	int mask = SDL_BUTTON(button);
	if ((mask & mPrevButtons) == 0)
	{
		//  �ޱ仯
		if ((mask & mCurrButtons) == 0)
		{
			return ENone;
		}
		//  ������
		else
		{
			return EPressed;
		}
	}
	else
	{
		//  ���ͷ�
		if ((mask & mCurrButtons) == 0)
		{
			return EReleased;
		}
		//  ����
		else
		{
			return EHeld;
		}
	}
}

bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
	//  �Ƿ���
	return mCurrButtons[button] == 1;
}

ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
	if (mPrevButtons[button] == 0)
	{
		//  �ޱ仯
		if (mCurrButtons[button] == 0)
		{
			return ENone;
		}
		//  ������
		else
		{
			return EPressed;
		}
	}
	else
	{
		//  ���ͷ�
		if (mCurrButtons[button] == 0)
		{
			return EReleased;
		}
		//  ����
		else
		{
			return EHeld;
		}
	}
}

bool InputSystem::Initialize()
{
	//  ����
	//  ��ȡ��ǰ����״̬
	mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	//  �����ǰ����״̬�ڴ�
	memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);
	//  ��ʼ�����״̬
	mState.Mouse.mCurrButtons = 0;
	mState.Mouse.mPrevButtons = 0;
	//  �򿪿�����0
	mController = SDL_GameControllerOpen(0);
	//  �������Ƿ�����
	mState.Controller.mIsConnected = (mController != nullptr);
	//  �����ǰ������״̬�ڴ�
	memset(mState.Controller.mCurrButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
	//  ���֮ǰ������״̬�ڴ�
	memset(mState.Controller.mPrevButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
	return true;
}

void InputSystem::Shutdown()
{

}

void InputSystem::PrepareForUpdate()
{
	//  ��ǰ����״̬���Ƶ���ǰ����״̬
	memcpy(mState.Keyboard.mPrevState,
		mState.Keyboard.mCurrState,
		SDL_NUM_SCANCODES);
	//  ��ǰ��갴��״̬���Ƶ���ǰ��갴��״̬
	mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
	//  �ر�����˶�״̬
	mState.Mouse.mIsRelative = false;
	//  ���ù�����״̬
	mState.Mouse.mScrollWheel = Vector2::Zero;
	//  ��ǰ������״̬���Ƶ���ǰ������״̬
	memcpy(mState.Controller.mPrevButtons,
		mState.Controller.mCurrButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

void InputSystem::Update()
{
	//  ���
	int x = 0, y = 0;
	if (mState.Mouse.mIsRelative)
	{
		//  ����˶�ģʽ�»�ȡ�������
		mState.Mouse.mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		//  ��ȡ�������
		mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
	}
	//  ��ȡλ��
	mState.Mouse.mMousePos.x = static_cast<float>(x);
	mState.Mouse.mMousePos.y = static_cast<float>(y);
	//  ������
	//  ����״̬
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		//  ��ȡ����������״̬
		mState.Controller.mCurrButtons[i] =
			SDL_GameControllerGetButton(mController,
				SDL_GameControllerButton(i));
	}

	//  ���
	//  ������/�Ұ������ֵ������
	mState.Controller.mLeftTrigger =
		Filter1D(SDL_GameControllerGetAxis(mController,
			SDL_CONTROLLER_AXIS_TRIGGERLEFT));
	mState.Controller.mRightTrigger =
		Filter1D(SDL_GameControllerGetAxis(mController,
			SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

	//  ҡ��
	//  ������/��ҡ������ֵ������
	x = SDL_GameControllerGetAxis(mController,
		SDL_CONTROLLER_AXIS_LEFTX);
	y = -SDL_GameControllerGetAxis(mController,
		SDL_CONTROLLER_AXIS_LEFTY);
	mState.Controller.mLeftStick = Filter2D(x, y);
	x = SDL_GameControllerGetAxis(mController,
		SDL_CONTROLLER_AXIS_RIGHTX);
	y = -SDL_GameControllerGetAxis(mController,
		SDL_CONTROLLER_AXIS_RIGHTY);
	mState.Controller.mRightStick = Filter2D(x, y);
}

void InputSystem::ProcessEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEWHEEL:
		//  ��ȡ������xy����
		mState.Mouse.mScrollWheel = Vector2(
			static_cast<float>(event.wheel.x),
			static_cast<float>(event.wheel.y));
		break;
	default:
		break;
	}
}

void InputSystem::SetRelativeMouseMode(bool value)
{
	//  ����/��������˶�ģʽ
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	mState.Mouse.mIsRelative = value;
}

float InputSystem::Filter1D(int input)
{
	//  ����
	const int deadZone = 250;
	//  �����������ֵ
	const int maxValue = 30000;
	//  ��ǰֵ
	float retVal = 0.0f;
	//  ��ȡ����ֵ
	int absValue = input > 0 ? input : -input;
	//  ���������ڵ�ֵ
	if (absValue > deadZone)
	{
		//  �������ֵ
		retVal = static_cast<float>(absValue - deadZone) / (maxValue - deadZone);
		//  �ӷ���
		retVal = input > 0 ? retVal : -1.0f * retVal;
		// ����-1.0f��1.0f֮��
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}
	return retVal;
}

Vector2 InputSystem::Filter2D(int inputX, int inputY)
{
	//  ����
	const float deadZone = 8000.0f;
	//  �����������ֵ
	const float maxValue = 30000.0f;
	//  ת��Ϊ����
	Vector2 dir;
	dir.x = static_cast<float>(inputX);
	dir.y = static_cast<float>(inputY);
	//  ���㳤��
	float length = dir.Length();
	//  ���������ڵ�ֵ
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		//  �������ֵ
		float f = (length - deadZone) / (maxValue - deadZone);
		// ����-1.0f��1.0f֮��
		f = Math::Clamp(f, 0.0f, 1.0f);
		//  �����任
		dir *= f / length;
	}
	return dir;
}

