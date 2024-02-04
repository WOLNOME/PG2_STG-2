#include "Player.h"

#include "PlayerBullet.h"

Player::Player()
{
	pos_ = { 320,360 };
	velocity_ = { 4,4 };
	rad_ = 16;
	color_ = 0xff0000ff;
	hp_ = 3;
	isDamage_ = false;
	isInvisible_ = false;
	InvisibleTimer_ = kInvisibleTimer;

	//弾のインスタンス生成
	for (int i = 0; i < kPlayerBulletNum; i++) {
		bullet[i] = new PlayerBullet;
	}
}

Player::~Player()
{
	for (int i = 0; i < kPlayerBulletNum; i++) {
		delete bullet[i];
	}
}

void Player::Init()
{
}

void Player::Update(char* keys, char* preKeys)
{
	///キー入力
	//移動
	if (keys[DIK_W]) {
		pos_.y -= velocity_.y;
	}
	if (keys[DIK_A]) {
		pos_.x -= velocity_.x;
	}
	if (keys[DIK_S]) {
		pos_.y += velocity_.y;
	}
	if (keys[DIK_D]) {
		pos_.x += velocity_.x;
	}
	//射撃
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		for (int i = 0; i < kPlayerBulletNum; i++) {
			//弾が生きてるとき
			if (bullet[i]->GetIsAlive()) {
				///特になし///
			}
			//弾が死んでるとき
			else {
				//弾を生成
				bullet[i]->Init(pos_);
				break;
			}
		}
	}
	///更新処理
	//射撃
	for (int i = 0; i < kPlayerBulletNum; i++) {
		//弾が生きてるとき
		if (bullet[i]->GetIsAlive()) {
			bullet[i]->Update();
		}
		//弾が死んでるとき
		else {

		}
	}
	///当たり判定処理
	//プレイヤーが壁に当たると止まる
	if (pos_.x < 0 + rad_) {
		pos_.x = 0 + rad_;
	}
	if (pos_.x > 640 - rad_) {
		pos_.x = 640 - rad_;
	}
	if (pos_.y < 0 + rad_) {
		pos_.y = 0 + rad_;
	}
	if (pos_.y > 720 - rad_) {
		pos_.y = 720 - rad_;
	}
	//弾が画面外に行ったら死ぬ
	for (int i = 0; i < kPlayerBulletNum; i++) {
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
	//敵の攻撃が自機に当たった時ダメージ受ける処理
	if (isDamage_&&!isInvisible_) {
		hp_--;
		isInvisible_ = true;
	}
	//無敵時間処理
	if (isInvisible_) {
		//無敵時間中
		InvisibleTimer_--;
		color_ = 0xffff00ff;
		//無敵時間切れたとき
		if (InvisibleTimer_ == 0) {
			isInvisible_ = false;
			isDamage_ = false;
			InvisibleTimer_ = kInvisibleTimer;
			color_ = 0xff0000ff;
		}
	}
}

void Player::Draw()
{
	//弾
	for (int i = 0; i < kPlayerBulletNum; i++) {
		//生きてる弾のインスタンスのみ描画
		if (bullet[i]->GetIsAlive()) {
			bullet[i]->Draw();
		}
	}
	//自機
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, color_, kFillModeSolid);

	Novice::ScreenPrintf(0, 60, "HP:%d", hp_);
}
