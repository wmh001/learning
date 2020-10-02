#include "DialogBox.h"
#include "Game.h"
#include "Renderer.h"
#include <SDL.h>

DialogBox::DialogBox(Game* game, const std::string& text, std::function<void()> onOK)
	: UIScreen(game)
{
	//  背景位置
	mBGPos = Vector2(0.0f, 0.0f);
	//  标题位置
	mTitlePos = Vector2(0.0f, 100.0f);
	//  重置下一个按钮位置
	mNextButtonPos = Vector2(0.0f, 0.0f);
	//  创建背景图像
	mBackground = mGame->GetRenderer()->GetTexture("Assets/DialogBG.png");
	//  设置标题
	SetTitle(text, Vector3::Zero, 30);
	//  添加确认按钮
	AddButton("OKButton", [onOK]() {
		onOK();
		});
	//  添加取消按钮
	AddButton("CancelButton", [this]() {
		Close();
		});
}

DialogBox::~DialogBox()
{

}
