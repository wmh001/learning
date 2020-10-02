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
	//  �޸İ�ť����
	void SetName(const std::string& name);
	//  ��������ͼ��
	class Texture* GetNameTex() { return mNameTex; }
	//  ����λ��
	const Vector2& GetPosition() const { return mPosition; }
	//  �޸İ�ť����
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	//  ��Χ��ť����
	bool GetHighlighted() const { return mHighlighted; }
	//  �Ƿ��ڷ�Χ��
	bool ContainsPoint(const Vector2& pt) const;
	//  �������
	void OnClick();
private:
	//  �ص�����
	std::function<void()> mOnClick;
	//  ����
	std::string mName;
	//  ����ͼ��
	class Texture* mNameTex;
	//  ����
	class Font* mFont;
	//  λ��
	Vector2 mPosition;
	//  �ߴ�
	Vector2 mDimensions;
	//  �Ƿ����
	bool mHighlighted;
};

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();
	//  ����
	virtual void Update(float deltaTime);
	//  ����
	virtual void Draw(class Shader* shader);
	//  ����
	virtual void ProcessInput(const uint8_t* keys);
	//  ���
	virtual void HandleKeyPress(int key);
	//  UI״̬
	enum UIState
	{
		EActive,  //  ��Ծ
		EClosing  //  �ر�
	};
	//  �ر�
	void Close();
	//  ����״̬
	UIState GetState() const { return mState; }
	//  �ı��������
	void SetTitle(const std::string& text, const Vector3& color = Color::White, int pointSize = 40);
	//  ��Ӱ�ť
	void AddButton(const std::string& name, std::function<void()> onClick);
protected:
	//  ����ͼ��
	void DrawTexture(class Shader* shader, class Texture* texture, const Vector2& offset = Vector2::Zero, float scale = 1.0f);
	//  ����������ģʽ
	void SetRelativeMouseMode(bool relative);
	//  ������Ϸ
	class Game* mGame;
	//  ����
	class Font* mFont;
	//  ����ͼ��
	class Texture* mTitle;
	//  ����ͼ��
	class Texture* mBackground;
	//  ��ѡ����ť��ͼ��
	class Texture* mButtonOn;
	//  ����ѡ����ť��ͼ��
	class Texture* mButtonOff;
	//  ����λ��
	Vector2 mTitlePos;
	//  ��һ����ťλ��
	Vector2 mNextButtonPos;
	//  ����λ��
	Vector2 mBGPos;
	//  ״̬
	UIState mState;
	// ��ť������
	std::vector<Button*> mButtons;
};

