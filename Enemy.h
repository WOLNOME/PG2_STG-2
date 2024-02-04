#pragma once
#include <Novice.h>
#include <time.h>
#include "Vector2.h"

const int kEnemyBulletNum = 100;
const int kShotInterval = 120;

enum EnemyType {
	A = 10,
	B,
	C,
	D
};

class EnemyBullet;

class Enemy
{
public:
	Enemy();
	~Enemy();
public:
	void Init(EnemyType type, int i);
	void Update();
	void Draw();
public:
	void BulletProcess(Vector2 PlayerPos);
	void BulletDraw();
public:
	Vector2 GetPos() { return pos_; }
	float GetRad() { return rad_; }
	bool GetIsAlive() { return isAlive_; }
public:
	void SetIsAlive(bool flag) { isAlive_ = flag; }
private:
	Vector2 pos_;
	Vector2 velocity_;
	float rad_;
	unsigned int color_;
	bool isAlive_;
	int ShotInterval;

	EnemyType type_;
public:
	EnemyBullet* bullet[kEnemyBulletNum];
};

