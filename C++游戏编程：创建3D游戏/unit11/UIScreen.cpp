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
	//  �����û�������Ļջ
	mGame->PushUI(this);
	//  ��������
	mFont = mGame->GetFont("Assets/Carlito-Regular.ttf");
	//  ����ͼ��
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
	//  ɾ����ť
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
	//  ���Ʊ���
	if (mBackground)
	{
		DrawTexture(shader, mBackground, mBGPos);
	}
	//  ������Ŀ
	if (mTitle)
	{
		DrawTexture(shader, mTitle, mTitlePos);
	}
	//  ���ư�ť
	for (auto b : mButtons)
	{
		//  ���ư�ť��ɫ
		Texture* tex = b->GetHighlighted() ? mButtonOn : mButtonOff;
		DrawTexture(shader, tex, b->GetPosition());
		//  ��������
		DrawTexture(shader, b->GetNameTex(), b->GetPosition());
	}
	// Override in subclasses to draw any textures
}

void UIScreen::ProcessInput(const uint8_t* keys)
{
	//  �Ƿ��а�ť
	if (!mButtons.empty())
	{
		//  ��ȡ���λ��
		int x, y;
		SDL_GetMouseState(&x, &y);
		//  ת������
		Vector2 mousePos(static_cast<float>(x), static_cast<float>(y));
		mousePos.x -= mGame->GetRenderer()->GetScreenWidth() * 0.5f;
		mousePos.y = mGame->GetRenderer()->GetScreenHeight() * 0.5f - mousePos.y;
		//  ������ť
		for (auto b : mButtons)
		{
			//  �ڷ�Χ�ڸ���
			if (b->ContainsPoint(mousePos))
			{
				b->SetHighlighted(true);
			}
			//  ���ڷ�Χ�ڲ�����
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
	//  �������
	case SDL_BUTTON_LEFT:
		if (!mButtons.empty())
		{
			for (auto b : mButtons)
			{
				//  �������
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
	//  ״̬�ı�
	mState = EClosing;
}

void UIScreen::SetTitle(const std::string& text, const Vector3& color, int pointSize)
{
	//  ���ͼ��
	if (mTitle)
	{
		mTitle->Unload();
		delete mTitle;
		mTitle = nullptr;
	}
	//  ������ͼ��
	mTitle = mFont->RenderText(text, color, pointSize);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
{
	//  ����ߴ�
	Vector2 dims(static_cast<float>(mButtonOn->GetWidth()), static_cast<float>(mButtonOn->GetHeight()));
	//  ������ť
	Button* b = new Button(name, mFont, onClick, mNextButtonPos, dims);
	//  ��������
	mButtons.emplace_back(b);
	//  ������һ����ť��λ��
	mNextButtonPos.y -= mButtonOff->GetHeight() + 20.0f;
}

void UIScreen::DrawTexture(class Shader* shader, class Texture* texture,
	const Vector2& offset, float scale)
{
	//  �������ž���
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale,
		static_cast<float>(texture->GetHeight()) * scale,
		1.0f);
	//  ת������Ļ�ϵ�λ��
	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(offset.x, offset.y, 0.0f));
	//  ��������任����
	Matrix4 world = scaleMat * transMat;
	//  ��������任����
	shader->SetMatrixUniform("uWorldTransform", world);
	//  ����
	texture->SetActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void UIScreen::SetRelativeMouseMode(bool relative)
{
	if (relative)
	{
		//  ����
		SDL_SetRelativeMouseMode(SDL_TRUE);
		//  ��ʼ��
		SDL_GetRelativeMouseState(nullptr, nullptr);
	}
	else
	{
		//  ����
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
	//  ��������
	mName = name;
	//  ��������ͼ��
	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
		mNameTex = nullptr;
	}
	//  ��������
	mNameTex = mFont->RenderText(mName);
}

bool Button::ContainsPoint(const Vector2& pt) const
{
	//  �ж�λ��
	bool no = pt.x < (mPosition.x - mDimensions.x / 2.0f) ||
		pt.x >(mPosition.x + mDimensions.x / 2.0f) ||
		pt.y < (mPosition.y - mDimensions.y / 2.0f) ||
		pt.y >(mPosition.y + mDimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	//  ���ø��ӵĴ������
	if (mOnClick)
	{
		mOnClick();
	}
}
