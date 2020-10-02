#include "HUD.h"
#include "Texture.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "PhysWorld.h"
#include "FollowActor.h"
#include <algorithm>
#include "GBuffer.h"
#include "TargetComponent.h"

HUD::HUD(Game* game)
	: UIScreen(game)
	, mRadarRange(2000.0f)
	, mRadarRadius(92.0f)
	, mTargetEnemy(false)
{
	//  创建渲染器
	Renderer* r = mGame->GetRenderer();
	//  设置图像
	mHealthBar = r->GetTexture("Assets/HealthBar.png");
	mRadar = r->GetTexture("Assets/Radar.png");
	mCrosshair = r->GetTexture("Assets/Crosshair.png");
	mCrosshairEnemy = r->GetTexture("Assets/CrosshairRed.png");
	mBlipTex = r->GetTexture("Assets/Blip.png");
	mRadarArrow = r->GetTexture("Assets/RadarArrow.png");
}

HUD::~HUD()
{

}

void HUD::Update(float deltaTime)
{
	//  基类更新
	UIScreen::Update(deltaTime);
	//  准星更新
	UpdateCrosshair(deltaTime);
	//  雷达更新
	UpdateRadar(deltaTime);
}

void HUD::Draw(Shader* shader)
{
	//  准星
	Texture* cross = mTargetEnemy ? mCrosshairEnemy : mCrosshair;
	DrawTexture(shader, cross, Vector2::Zero, 2.0f);
	//  雷达
	const Vector2 cRadarPos(-390.0f, 275.0f);
	DrawTexture(shader, mRadar, cRadarPos, 1.0f);
	//  光点
	for (Vector2& blip : mBlips)
	{
		DrawTexture(shader, mBlipTex, cRadarPos + blip, 1.0f);
	}
	//  雷达中心三角
	DrawTexture(shader, mRadarArrow, cRadarPos);
	// Health bar
	//DrawTexture(shader, mHealthBar, Vector2(-350.0f, -350.0f));
	//  后视镜
	Texture* mirror = mGame->GetRenderer()->GetMirrorTexture();
	DrawTexture(shader, mirror, Vector2(-350.0f, -250.0f), 1.0f, true);
	//Texture* tex = mGame->GetRenderer()->GetGBuffer()->GetTexture(GBuffer::EDiffuse);
	//DrawTexture(shader, tex, Vector2::Zero, 1.0f, true);
}

void HUD::AddTargetComponent(TargetComponent* tc)
{
	mTargetComps.emplace_back(tc);
}

void HUD::RemoveTargetComponent(TargetComponent* tc)
{
	auto iter = std::find(mTargetComps.begin(), mTargetComps.end(), tc);
	mTargetComps.erase(iter);
}

void HUD::UpdateCrosshair(float deltaTime)
{
	//  重置
	mTargetEnemy = false;
	//  创建线段
	const float cAimDist = 5000.0f;
	Vector3 start, dir;
	mGame->GetRenderer()->GetScreenDirection(start, dir);
	LineSegment l(start, start + dir * cAimDist);
	//  相交检测
	PhysWorld::CollisionInfo info;
	if (mGame->GetPhysWorld()->SegmentCast(l, info))
	{
		for (auto tc : mTargetComps)
		{
			//  是否已瞄准
			if (tc->GetOwner() == info.mActor)
			{
				mTargetEnemy = true;
				break;
			}
		}
	}
}

void HUD::UpdateRadar(float deltaTime)
{
	//  清除上一光点
	mBlips.clear();
	//  获取玩家位置
	Vector3 playerPos = mGame->GetPlayer()->GetPosition();
	//  转换为2D
	Vector2 playerPos2D(playerPos.y, playerPos.x);
	//  获取前向
	Vector3 playerForward = mGame->GetPlayer()->GetForward();
	//  转换为2D
	Vector2 playerForward2D(playerForward.x, playerForward.y);
	//  计算角度
	float angle = Math::Atan2(playerForward2D.y, playerForward2D.x);
	//  转换为矩阵
	Matrix3 rotMat = Matrix3::CreateRotation(angle);
	//  计算光点位置
	for (auto tc : mTargetComps)
	{
		//  获取目标位置
		Vector3 targetPos = tc->GetOwner()->GetPosition();
		//  转换为2D
		Vector2 actorPos2D(targetPos.y, targetPos.x);
		//  计算向量
		Vector2 playerToTarget = actorPos2D - playerPos2D;
		//  是否在范围内
		if (playerToTarget.LengthSq() <= (mRadarRange * mRadarRange))
		{
			//  计算光点相对雷达坐标
			Vector2 blipPos = playerToTarget;
			blipPos *= mRadarRadius / mRadarRange;
			//  旋转
			blipPos = Vector2::Transform(blipPos, rotMat);
			//  进入容器
			mBlips.emplace_back(blipPos);
		}
	}
}
