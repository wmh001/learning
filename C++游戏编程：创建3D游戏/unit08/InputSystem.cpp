#include "InputSystem.h"
#include <SDL.h>
#include <cstring>

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
    //  按键是否按下
	return mCurrState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (mPrevState[keyCode] == 0)
	{
		//  无变化
		if (mCurrState[keyCode] == 0)
		{
			return ENone;
		}
		//  被按下
		else
		{
			return EPressed;
		}
	}
	else
	{
		//  被释放
		if (mCurrState[keyCode] == 0)
		{
			return EReleased;
		}
		//  保持
		else
		{
			return EHeld;
		}
	}
}

bool MouseState::GetButtonValue(int button) const
{
	//  是否按下
	return (SDL_BUTTON(button) & mCurrButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
	//  获取按键状态
	int mask = SDL_BUTTON(button);
	if ((mask & mPrevButtons) == 0)
	{
		//  无变化
		if ((mask & mCurrButtons) == 0)
		{
			return ENone;
		}
		//  被按下
		else
		{
			return EPressed;
		}
	}
	else
	{
		//  被释放
		if ((mask & mCurrButtons) == 0)
		{
			return EReleased;
		}
		//  保持
		else
		{
			return EHeld;
		}
	}
}

bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
	//  是否按下
	return mCurrButtons[button] == 1;
}

ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
	if (mPrevButtons[button] == 0)
	{
		//  无变化
		if (mCurrButtons[button] == 0)
		{
			return ENone;
		}
		//  被按下
		else
		{
			return EPressed;
		}
	}
	else
	{
		//  被释放
		if (mCurrButtons[button] == 0)
		{
			return EReleased;
		}
		//  保持
		else
		{
			return EHeld;
		}
	}
}

bool InputSystem::Initialize()
{
	//  键盘
	//  获取当前键盘状态
	mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	//  清除先前键盘状态内存
	memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);
	//  初始化鼠标状态
	mState.Mouse.mCurrButtons = 0;
	mState.Mouse.mPrevButtons = 0;
	//  打开控制器0
	mController = SDL_GameControllerOpen(0);
	//  控制器是否连接
	mState.Controller.mIsConnected = (mController != nullptr);
	//  清除当前控制器状态内存
	memset(mState.Controller.mCurrButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
	//  清除之前控制器状态内存
	memset(mState.Controller.mPrevButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
	return true;
}

void InputSystem::Shutdown()
{

}

void InputSystem::PrepareForUpdate()
{
	//  当前键盘状态复制到先前键盘状态
	memcpy(mState.Keyboard.mPrevState,
		mState.Keyboard.mCurrState,
		SDL_NUM_SCANCODES);
	//  当前鼠标按键状态复制到先前鼠标按键状态
	mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
	//  关闭相对运动状态
	mState.Mouse.mIsRelative = false;
	//  重置滚动轮状态
	mState.Mouse.mScrollWheel = Vector2::Zero;
	//  当前控制器状态复制到先前控制器状态
	memcpy(mState.Controller.mPrevButtons,
		mState.Controller.mCurrButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

void InputSystem::Update()
{
	//  鼠标
	int x = 0, y = 0;
	if (mState.Mouse.mIsRelative)
	{
		//  相对运动模式下获取鼠标坐标
		mState.Mouse.mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		//  获取鼠标坐标
		mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
	}
	//  获取位置
	mState.Mouse.mMousePos.x = static_cast<float>(x);
	mState.Mouse.mMousePos.y = static_cast<float>(y);
	//  控制器
	//  按键状态
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		//  获取控制器按键状态
		mState.Controller.mCurrButtons[i] =
			SDL_GameControllerGetButton(mController,
				SDL_GameControllerButton(i));
	}

	//  扳机
	//  读入左/右扳机输入值并过滤
	mState.Controller.mLeftTrigger =
		Filter1D(SDL_GameControllerGetAxis(mController,
			SDL_CONTROLLER_AXIS_TRIGGERLEFT));
	mState.Controller.mRightTrigger =
		Filter1D(SDL_GameControllerGetAxis(mController,
			SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

	//  摇杆
	//  读入左/右摇杆输入值并过滤
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
		//  获取滚动轮xy坐标
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
	//  启用/禁用相对运动模式
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	mState.Mouse.mIsRelative = value;
}

float InputSystem::Filter1D(int input)
{
	//  死区
	const int deadZone = 250;
	//  输入数据最大值
	const int maxValue = 30000;
	//  当前值
	float retVal = 0.0f;
	//  获取绝对值
	int absValue = input > 0 ? input : -input;
	//  忽略死区内的值
	if (absValue > deadZone)
	{
		//  计算分数值
		retVal = static_cast<float>(absValue - deadZone) / (maxValue - deadZone);
		//  加符号
		retVal = input > 0 ? retVal : -1.0f * retVal;
		// 夹在-1.0f和1.0f之间
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}
	return retVal;
}

Vector2 InputSystem::Filter2D(int inputX, int inputY)
{
	//  死区
	const float deadZone = 8000.0f;
	//  输入数据最大值
	const float maxValue = 30000.0f;
	//  转换为向量
	Vector2 dir;
	dir.x = static_cast<float>(inputX);
	dir.y = static_cast<float>(inputY);
	//  计算长度
	float length = dir.Length();
	//  忽略死区内的值
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		//  计算分数值
		float f = (length - deadZone) / (maxValue - deadZone);
		// 夹在-1.0f和1.0f之间
		f = Math::Clamp(f, 0.0f, 1.0f);
		//  比例变换
		dir *= f / length;
	}
	return dir;
}

