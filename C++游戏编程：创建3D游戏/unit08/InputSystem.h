#pragma once
#include <SDL.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

//  按键状态
enum ButtonState
{
	ENone,  //  无变化
	EPressed,  //  被按下
	EReleased,  //  被释放
	EHeld  //  保持
};

//  键盘状态
class KeyboardState
{
public:
	//  声明友元类
	friend class InputSystem;
	//  获取键值
	bool GetKeyValue(SDL_Scancode keyCode) const;
	//  获取按键状态
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	//  当前状态的指针
	const Uint8* mCurrState;
	//  保存之前状态的数组
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

//  鼠标状态
class MouseState
{
public:
	//  声明友元类
	friend class InputSystem;
	//  获取鼠标位置
	const Vector2& GetPosition() const { return mMousePos; }
	//  获取滚动轮状态
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	//  是否启用相对运动状态
	bool IsRelative() const { return mIsRelative; }
	//  获取按键值
	bool GetButtonValue(int button) const;
	//  获取鼠标按键状态
	ButtonState GetButtonState(int button) const;
private:
	//  当前鼠标位置
	Vector2 mMousePos;
	//  滚动轮滚动
	Vector2 mScrollWheel;
	//  当前鼠标按键状态
	Uint32 mCurrButtons;
	//  之前鼠标按键状态
	Uint32 mPrevButtons;
	//  是否启用相对运动模式
	bool mIsRelative;
};

class ControllerState
{
public:
	//  声明友元类
	friend class InputSystem;
	//  获取按键值
	bool GetButtonValue(SDL_GameControllerButton button) const;
	//  获取按键状态
	ButtonState GetButtonState(SDL_GameControllerButton button) const;
	//  访问左/右摇杆
	const Vector2& GetLeftStick() const { return mLeftStick; }
	const Vector2& GetRightStick() const { return mRightStick; }
	//  访问左/右扳机
	float GetLeftTrigger() const { return mLeftTrigger; }
	float GetRightTrigger() const { return mRightTrigger; }
	//  查询是否连接
	bool GetIsConnected() const { return mIsConnected; }
private:
	//  当前按键状态
	Uint8 mCurrButtons[SDL_CONTROLLER_BUTTON_MAX];
	//  之前按键状态
	Uint8 mPrevButtons[SDL_CONTROLLER_BUTTON_MAX];
	// Left/right sticks
	Vector2 mLeftStick;
	Vector2 mRightStick;
	//  左右扳机
	float mLeftTrigger;
	float mRightTrigger;
	//  是否连接
	bool mIsConnected;
};

//  输入状态
struct InputState
{
	//  键盘状态
	KeyboardState Keyboard;
	//  鼠标状态
	MouseState Mouse;
	//  控制器状态
	ControllerState Controller;
};

class InputSystem
{
public:
	//  初始化
	bool Initialize();
	//  关闭
	void Shutdown();
	//  准备接收事件
	void PrepareForUpdate();
	//  更新
	void Update();
	//  滚动轮处理
	void ProcessEvent(union SDL_Event& event);
	//  访问状态
	const InputState& GetState() const { return mState; }
	//  启用/禁用相对运动状态
	void SetRelativeMouseMode(bool value);
private:
	//  过滤一维轴线数据
	float Filter1D(int input);
	//  过滤二维轴线数据
	Vector2 Filter2D(int inputX, int inputY);
	//  输入状态
	InputState mState;
	//  控制器
	SDL_GameController* mController;
};

