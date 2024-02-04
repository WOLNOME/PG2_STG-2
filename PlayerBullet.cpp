#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
	pos_ = { 0,0 };
	velocity_ = { 0,8 };
	rad_ = 4;
	color_ = 0xffffffff;
	isAlive_ = false;
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Init(Vector2 PlayerPos)
{
	pos_ = PlayerPos;
	isAlive_ = true;
}

void PlayerBullet::Update()
{
	//移動処理
	pos_.y -= velocity_.y;
}

void PlayerBullet::Draw()
{
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, color_, kFillModeSolid);
}
