#include "UIScreen.h"
#include "Texture.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "Font.h"

UIScreen::UIScreen(Game* game)
	: mGame(game)
	, mTitle(nullptr)
	, mBackground(nullptr)
	, mTitlePos(0.0f, 300.0f)
	, mNextButtonPos(0.0f, 200.0f)
	, mBGPos(0.0f, 250.0f)
	, mState(EActive)
{
	//  加入用户界面屏幕栈
	mGame->PushUI(this);
	//  设置字体
	mFont = mGame->GetFont("Assets/Carlito-Regular.ttf");
	//  设置图像
	mButtonOn = mGame->GetRenderer()->GetTexture("Assets/ButtonYellow.png");
	mButtonOff = mGame->GetRenderer()->GetTexture("Assets/ButtonBlue.png");
}

UIScreen::~UIScreen()
{
	if (mTitle)
	{
		mTitle->Unload();
		delete mTitle;
	}
	//  删除按钮
	for (auto b : mButtons)
	{
		delete b;
	}
	mButtons.clear();
}

void UIScreen::Update(float deltaTime)
{

}

void UIScreen::Draw(Shader* shader)
{
	//  绘制背景
	if (mBackground)
	{
		DrawTexture(shader, mBackground, mBGPos);
	}
	//  绘制题目
	if (mTitle)
	{
		DrawTexture(shader, mTitle, mTitlePos);
	}
	//  绘制按钮
	for (auto b : mButtons)
	{
		//  绘制按钮基色
		Texture* tex = b->GetHighlighted() ? mButtonOn : mButtonOff;
		DrawTexture(shader, tex, b->GetPosition());
		//  绘制文字
		DrawTexture(shader, b->GetNameTex(), b->GetPosition());
	}
	// Override in subclasses to draw any textures
}

void UIScreen::ProcessInput(const uint8_t* keys)
{
	//  是否有按钮
	if (!mButtons.empty())
	{
		//  获取鼠标位置
		int x, y;
		SDL_GetMouseState(&x, &y);
		//  转换坐标
		Vector2 mousePos(static_cast<float>(x), static_cast<float>(y));
		mousePos.x -= mGame->GetRenderer()->GetScreenWidth() * 0.5f;
		mousePos.y = mGame->GetRenderer()->GetScreenHeight() * 0.5f - mousePos.y;
		//  遍历按钮
		for (auto b : mButtons)
		{
			//  在范围内高亮
			if (b->ContainsPoint(mousePos))
			{
				b->SetHighlighted(true);
			}
			//  不在范围内不高亮
			else
			{
				b->SetHighlighted(false);
			}
		}
	}
}

void UIScreen::HandleKeyPress(int key)
{
	switch (key)
	{
	//  单击左键
	case SDL_BUTTON_LEFT:
		if (!mButtons.empty())
		{
			for (auto b : mButtons)
			{
				//  点击处理
				if (b->GetHighlighted())
				{
					b->OnClick();
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void UIScreen::Close()
{
	//  状态改变
	mState = EClosing;
}

void UIScreen::SetTitle(const std::string& text, const Vector3& color, int pointSize)
{
	//  清除图像
	if (mTitle)
	{
		mTitle->Unload();
		delete mTitle;
		mTitle = nullptr;
	}
	//  绘制新图像
	mTitle = mFont->RenderText(text, color, pointSize);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
{
	//  计算尺寸
	Vector2 dims(static_cast<float>(mButtonOn->GetWidth()), static_cast<float>(mButtonOn->GetHeight()));
	//  创建按钮
	Button* b = new Button(name, mFont, onClick, mNextButtonPos, dims);
	//  进入容器
	mButtons.emplace_back(b);
	//  更新下一个按钮的位置
	mNextButtonPos.y -= mButtonOff->GetHeight() + 20.0f;
}

void UIScreen::DrawTexture(class Shader* shader, class Texture* texture,
	const Vector2& offset, float scale)
{
	//  创建缩放矩阵
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale,
		static_cast<float>(texture->GetHeight()) * scale,
		1.0f);
	//  转换到屏幕上的位置
	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(offset.x, offset.y, 0.0f));
	//  计算世界变换矩阵
	Matrix4 world = scaleMat * transMat;
	//  传输世界变换矩阵
	shader->SetMatrixUniform("uWorldTransform", world);
	//  激活
	texture->SetActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void UIScreen::SetRelativeMouseMode(bool relative)
{
	if (relative)
	{
		//  启用
		SDL_SetRelativeMouseMode(SDL_TRUE);
		//  初始化
		SDL_GetRelativeMouseState(nullptr, nullptr);
	}
	else
	{
		//  禁用
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}

Button::Button(const std::string& name, Font* font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims)
	: mOnClick(onClick)
	, mNameTex(nullptr)
	, mFont(font)
	, mPosition(pos)
	, mDimensions(dims)
	, mHighlighted(false)
{
	SetName(name);
}

Button::~Button()
{
	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
	}
}

void Button::SetName(const std::string& name)
{
	//  设置名字
	mName = name;
	//  重置名字图像
	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
		mNameTex = nullptr;
	}
	//  绘制文字
	mNameTex = mFont->RenderText(mName);
}

bool Button::ContainsPoint(const Vector2& pt) const
{
	//  判断位置
	bool no = pt.x < (mPosition.x - mDimensions.x / 2.0f) ||
		pt.x >(mPosition.x + mDimensions.x / 2.0f) ||
		pt.y < (mPosition.y - mDimensions.y / 2.0f) ||
		pt.y >(mPosition.y + mDimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	//  调用附加的处理程序
	if (mOnClick)
	{
		mOnClick();
	}
}
