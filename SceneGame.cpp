#include "SceneGame.h"

#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"

SceneGame::SceneGame()
{
	NextScene = GAME;
	player = new Player;
	for (int i = 0; i < kEnemyNum; i++) {
		enemy[i] = new Enemy;
	}

	timer_ = 0;
	seconds_ = 0;
	ecount_ = 0;

	back = Novice::LoadTexture("./Resources/back.png");
	move_ = 0;
}

SceneGame::~SceneGame()
{
	delete player;
	for (int i = 0; i < kEnemyNum; i++) {
		delete enemy[i];
	}
}

void SceneGame::Init()
{
}

void SceneGame::Update(char* keys, char* preKeys)
{
	//タイマーの処理
	timer_++;
	if (timer_ == 60) {
		seconds_++;
		timer_ = 0;
	}

	//エネミーの生成処理
	if (seconds_ != 0 && (seconds_ + 5) % 10 == 0 && timer_ == 0) {
		for (int i = 0; i < kEnemyNum; i++) {
			if (!enemy[i]->GetIsAlive()) {
				//敵が死んでたら生成
				enemy[i]->Init(A, i);
			}
			ecount_++;
			if (ecount_ == 5) {
				ecount_ = 0;
				break;
			}
		}
	}


	//プレイヤーの更新処理
	player->Update(keys, preKeys);
	//エネミーの更新処理
	for (int i = 0; i < kEnemyNum; i++) {
		if (enemy[i]->GetIsAlive()) {
			enemy[i]->Update();
		}
		enemy[i]->BulletProcess(player->GetPos());
	}

	//当たり判定処理
	//自機→敵
	for (int i = 0; i < kPlayerBulletNum; i++) {
		for (int j = 0; j < kEnemyNum; j++) {
			if (player->bullet[i]->GetIsAlive() && enemy[j]->GetIsAlive()) {
				if (CollisionCheck(player->bullet[i]->GetPos(), enemy[j]->GetPos(), player->bullet[i]->GetRad(), enemy[j]->GetRad())) {
					//自機の弾と敵の当たり判定
					player->bullet[i]->SetIsAlive(false);
					enemy[j]->SetIsAlive(false);
				}
			}
			for (int k = 0; k < kEnemyBulletNum; k++) {
				if (player->bullet[i]->GetIsAlive() && enemy[j]->bullet[k]->GetIsAlive()) {
					if (CollisionCheck(player->bullet[i]->GetPos(), enemy[j]->bullet[k]->GetPos(), player->bullet[i]->GetRad(), enemy[j]->bullet[k]->GetRad())) {
						//自機の弾と敵の弾の当たり判定
						player->bullet[i]->SetIsAlive(false);
						enemy[j]->bullet[k]->SetIsAlive(false);
					}
				}
			}
		}
	}
	//敵→自機
	for (int i = 0; i < kEnemyNum; i++) {
		if (enemy[i]->GetIsAlive()) {
			if (CollisionCheck(player->GetPos(), enemy[i]->GetPos(), player->GetRad(), enemy[i]->GetRad())) {
				//自機と敵の当たり判定
				player->SetIsDamage(true);
			}
		}
		for (int j = 0; j < kEnemyBulletNum; j++) {
			if (enemy[i]->bullet[j]->GetIsAlive()) {
				if (CollisionCheck(player->GetPos(), enemy[i]->bullet[j]->GetPos(), player->GetRad(), enemy[i]->bullet[j]->GetRad())) {
					//自機と敵の弾の当たり判定
					player->SetIsDamage(true);
				}
			}
		}
	}

	//背景動かす処理
	move_++;
	if (move_ > kWindowHeight) {
		move_ = 0;
	}

	//タイマーが30秒たったら終了→リザルトへ
	if (seconds_ == 30 && timer_ == 0) {
		NextScene = RESULT;
	}

	//自機の体力が0になったらゲームオーバー
	if (player->GetHp() == 0) {
		NextScene = GAMEOVER;
	}


}

void SceneGame::Draw()
{
	//背景
	Novice::DrawSprite(0, 0 + move_, back, 1, 1, 0.0f, 0xffffffff);
	Novice::DrawSprite(0, -kWindowHeight + move_, back, 1, 1, 0.0f, 0xffffffff);
	//敵関連
	for (int i = 0; i < kEnemyNum; i++) {
		enemy[i]->BulletDraw();
		if (enemy[i]->GetIsAlive()) {
			enemy[i]->Draw();
		}
	}
	//プレイヤー関連
	player->Draw();
	Novice::ScreenPrintf(0, 0, "sec:%d", 30 - seconds_);
}

bool SceneGame::CollisionCheck(Vector2 pos1, Vector2 pos2, float rad_1, float rad_2)
{
	Vector2 dist;
	float d;

	dist.x = pos1.x - pos2.x;
	dist.y = pos1.y - pos2.y;
	d = sqrtf(dist.x * dist.x + dist.y * dist.y);

	if (d < rad_1 + rad_2) {
		return true;
	}
	else {
		return false;
	}
}

