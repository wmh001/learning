#include "DialogBox.h"
#include "Game.h"
#include "Renderer.h"
#include <SDL.h>

DialogBox::DialogBox(Game* game, const std::string& text, std::function<void()> onOK)
	: UIScreen(game)
{
	//  ����λ��
	mBGPos = Vector2(0.0f, 0.0f);
	//  ����λ��
	mTitlePos = Vector2(0.0f, 100.0f);
	//  ������һ����ťλ��
	mNextButtonPos = Vector2(0.0f, 0.0f);
	//  ��������ͼ��
	mBackground = mGame->GetRenderer()->GetTexture("Assets/DialogBG.png");
	//  ���ñ���
	SetTitle(text, Vector3::Zero, 30);
	//  ���ȷ�ϰ�ť
	AddButton("OKButton", [onOK]() {
		onOK();
		});
	//  ���ȡ����ť
	AddButton("CancelButton", [this]() {
		Close();
		});
}

DialogBox::~DialogBox()
{

}
