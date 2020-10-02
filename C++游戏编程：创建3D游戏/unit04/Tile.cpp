#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(class Game* game)
	:Actor(game)
	, mParent(nullptr)
	, f(0.0f)
	, g(0.0f)
	, h(0.0f)
	, mBlocked(false)
	, mSprite(nullptr)
	, mTileState(EDefault)
	, mSelected(false)
{
	mSprite = new SpriteComponent(this);
	UpdateTexture();
}

void Tile::SetTileState(TileState state)
{
	mTileState = state;
	//  更新图像
	UpdateTexture();
}

void Tile::ToggleSelect()
{
	//  鼠标改选
	mSelected = !mSelected;
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	std::string text;
	switch (mTileState)
	{
	case EStart:
		text = "Assets/TileTan.png";
		break;
	case EBase:
		text = "Assets/TileGreen.png";
		break;
	case EPath:
		if (mSelected)
			text = "Assets/TileGreySelected.png";
		else
			text = "Assets/TileGrey.png";
		break;
	case EDefault:
	default:
		if (mSelected)
			text = "Assets/TileBrownSelected.png";
		else
			text = "Assets/TileBrown.png";
		break;
	}
	//  绘制图像
	mSprite->SetTexture(GetGame()->GetTexture(text));
}
