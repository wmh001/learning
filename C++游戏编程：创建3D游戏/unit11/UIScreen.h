#pragma once
#include "Math.h"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>

class Button
{
public:
	Button(const std::string& name, class Font* font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims);
	~Button();
	//  修改按钮名字
	void SetName(const std::string& name);
	//  访问名字图像
	class Texture* GetNameTex() { return mNameTex; }
	//  访问位置
	const Vector2& GetPosition() const { return mPosition; }
	//  修改按钮高亮
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	//  范围按钮高亮
	bool GetHighlighted() const { return mHighlighted; }
	//  是否在范围内
	bool ContainsPoint(const Vector2& pt) const;
	//  点击处理
	void OnClick();
private:
	//  回调函数
	std::function<void()> mOnClick;
	//  名字
	std::string mName;
	//  名字图像
	class Texture* mNameTex;
	//  字体
	class Font* mFont;
	//  位置
	Vector2 mPosition;
	//  尺寸
	Vector2 mDimensions;
	//  是否高亮
	bool mHighlighted;
};

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();
	//  更新
	virtual void Update(float deltaTime);
	//  绘制
	virtual void Draw(class Shader* shader);
	//  输入
	virtual void ProcessInput(const uint8_t* keys);
	//  鼠标
	virtual void HandleKeyPress(int key);
	//  UI状态
	enum UIState
	{
		EActive,  //  活跃
		EClosing  //  关闭
	};
	//  关闭
	void Close();
	//  访问状态
	UIState GetState() const { return mState; }
	//  改变标题内容
	void SetTitle(const std::string& text, const Vector3& color = Color::White, int pointSize = 40);
	//  添加按钮
	void AddButton(const std::string& name, std::function<void()> onClick);
protected:
	//  绘制图像
	void DrawTexture(class Shader* shader, class Texture* texture, const Vector2& offset = Vector2::Zero, float scale = 1.0f);
	//  设置鼠标相对模式
	void SetRelativeMouseMode(bool relative);
	//  所属游戏
	class Game* mGame;
	//  字体
	class Font* mFont;
	//  标题图像
	class Texture* mTitle;
	//  背景图像
	class Texture* mBackground;
	//  被选定按钮的图像
	class Texture* mButtonOn;
	//  不被选定按钮的图像
	class Texture* mButtonOff;
	//  标题位置
	Vector2 mTitlePos;
	//  下一个按钮位置
	Vector2 mNextButtonPos;
	//  背景位置
	Vector2 mBGPos;
	//  状态
	UIState mState;
	// 按钮的容器
	std::vector<Button*> mButtons;
};

