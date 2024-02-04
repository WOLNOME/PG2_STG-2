#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
	pos_ = { 0,0 };
	velocity_ = { 0,0 };
	speed_ = 5;
	rad_ = 4;
	color_ = 0xff00ffff;
	isAlive_ = false;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Init(Vector2 EnemyPos, Vector2 PlayerPos)
{
	Vector2 dist;
	float d;

	pos_ = EnemyPos;
	dist.x = PlayerPos.x - pos_.x;
	dist.y = PlayerPos.y - pos_.y;
	d = sqrtf(dist.x * dist.x + dist.y * dist.y);

	velocity_.x = dist.x / d * speed_;
	velocity_.y = dist.y / d * speed_;
	isAlive_ = true;
}

void EnemyBullet::Update()
{
	//移動処理
	pos_.x += velocity_.x;
	pos_.y += velocity_.y;
}

void EnemyBullet::Draw()
{
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, color_, kFillModeSolid);
}

