#include "Enemy.h"

#include "EnemyBullet.h"

Enemy::Enemy()
{
	pos_ = { 0,0 };
	velocity_ = { 0,4 };
	rad_ = 16;
	color_ = 0x00ff00ff;
	isAlive_ = false;
	ShotInterval = 0;
	type_ = A;

	//弾
	for (int i = 0; i < kEnemyBulletNum; i++) {
		bullet[i] = new EnemyBullet;
	}

}

Enemy::~Enemy()
{
	for (int i = 0; i < kEnemyBulletNum; i++) {
		delete bullet[i];
	}
}

void Enemy::Init(EnemyType type, int i)
{
	srand(unsigned int(time(NULL) + i * i * i * 100));
	pos_.x = float(rand() % (640 - (int)rad_ * 2) + rad_);
	pos_.y = float(rand() % 100 - (100 + rad_));
	isAlive_ = true;
	ShotInterval = kShotInterval;
	type_ = type;

	switch (type_)
	{
	case A:
		velocity_ = { 2,2 };
		break;
	case B:
		break;
	case C:
		break;
	case D:
		break;
	default:
		break;
	}
}

void Enemy::Update()
{
	//タイプごとの処理
	switch (type_)
	{
	case A:
		//移動
		pos_.x += velocity_.x;
		pos_.y += velocity_.y;
		//当たり判定処理
		if (pos_.x < 0 + rad_ || pos_.x > 640 - rad_) {
			//左右の壁に当たったら反転
			velocity_.x *= -1;
		}
		if (pos_.y > 720) {
			//一番下に行ったら消える
			isAlive_ = false;
		}
		break;
	case B:
		break;
	case C:
		break;
	case D:
		break;
	default:
		break;
	}
}

void Enemy::Draw()
{
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, color_, kFillModeSolid);
}

void Enemy::BulletProcess(Vector2 PlayerPos)
{
	//射撃
	if (isAlive_) {
		ShotInterval--;
		if (ShotInterval == 0) {
			ShotInterval = kShotInterval;
			for (int i = 0; i < kEnemyBulletNum; i++) {
				//弾が生きてるとき
				if (bullet[i]->GetIsAlive()) {
					///特になし///
				}
				//弾が死んでるとき
				else {
					//弾を生成
					bullet[i]->Init(pos_, PlayerPos);
					break;
				}
			}
		}
	}
	///更新処理
	//弾
	for (int i = 0; i < kEnemyBulletNum; i++) {
		//弾が生きてるとき
		if (bullet[i]->GetIsAlive()) {
			bullet[i]->Update();
		}
		//弾が死んでるとき
		else {

		}
	}
	//当たり判定
	//弾が画面外に行ったら死ぬ
	for (int i = 0; i < kEnemyBulletNum; i++) {
		if (bullet[i]->GetIsAlive())
		{
			if (bullet[i]->GetPos().x < 0 ||
				bullet[i]->GetPos().x>1280 ||
				bullet[i]->GetPos().y < 0 ||
				bullet[i]->GetPos().y>720)
			{
				bullet[i]->SetIsAlive(false);
			}
		}

	}
}

void Enemy::BulletDraw()
{
	//弾
	for (int i = 0; i < kEnemyBulletNum; i++) {
		//生きてる弾のインスタンスのみ描画
		if (bullet[i]->GetIsAlive()) {
			bullet[i]->Draw();
		}
	}
}
