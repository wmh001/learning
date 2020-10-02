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
	//  ������Ⱦ��
	Renderer* r = mGame->GetRenderer();
	//  ����ͼ��
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
	//  �������
	UIScreen::Update(deltaTime);
	//  ׼�Ǹ���
	UpdateCrosshair(deltaTime);
	//  �״����
	UpdateRadar(deltaTime);
}

void HUD::Draw(Shader* shader)
{
	//  ׼��
	Texture* cross = mTargetEnemy ? mCrosshairEnemy : mCrosshair;
	DrawTexture(shader, cross, Vector2::Zero, 2.0f);
	//  �״�
	const Vector2 cRadarPos(-390.0f, 275.0f);
	DrawTexture(shader, mRadar, cRadarPos, 1.0f);
	//  ���
	for (Vector2& blip : mBlips)
	{
		DrawTexture(shader, mBlipTex, cRadarPos + blip, 1.0f);
	}
	//  �״���������
	DrawTexture(shader, mRadarArrow, cRadarPos);
	// Health bar
	//DrawTexture(shader, mHealthBar, Vector2(-350.0f, -350.0f));
	//  ���Ӿ�
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
	//  ����
	mTargetEnemy = false;
	//  �����߶�
	const float cAimDist = 5000.0f;
	Vector3 start, dir;
	mGame->GetRenderer()->GetScreenDirection(start, dir);
	LineSegment l(start, start + dir * cAimDist);
	//  �ཻ���
	PhysWorld::CollisionInfo info;
	if (mGame->GetPhysWorld()->SegmentCast(l, info))
	{
		for (auto tc : mTargetComps)
		{
			//  �Ƿ�����׼
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
	//  �����һ���
	mBlips.clear();
	//  ��ȡ���λ��
	Vector3 playerPos = mGame->GetPlayer()->GetPosition();
	//  ת��Ϊ2D
	Vector2 playerPos2D(playerPos.y, playerPos.x);
	//  ��ȡǰ��
	Vector3 playerForward = mGame->GetPlayer()->GetForward();
	//  ת��Ϊ2D
	Vector2 playerForward2D(playerForward.x, playerForward.y);
	//  ����Ƕ�
	float angle = Math::Atan2(playerForward2D.y, playerForward2D.x);
	//  ת��Ϊ����
	Matrix3 rotMat = Matrix3::CreateRotation(angle);
	//  ������λ��
	for (auto tc : mTargetComps)
	{
		//  ��ȡĿ��λ��
		Vector3 targetPos = tc->GetOwner()->GetPosition();
		//  ת��Ϊ2D
		Vector2 actorPos2D(targetPos.y, targetPos.x);
		//  ��������
		Vector2 playerToTarget = actorPos2D - playerPos2D;
		//  �Ƿ��ڷ�Χ��
		if (playerToTarget.LengthSq() <= (mRadarRange * mRadarRange))
		{
			//  ����������״�����
			Vector2 blipPos = playerToTarget;
			blipPos *= mRadarRadius / mRadarRange;
			//  ��ת
			blipPos = Vector2::Transform(blipPos, rotMat);
			//  ��������
			mBlips.emplace_back(blipPos);
		}
	}
}
