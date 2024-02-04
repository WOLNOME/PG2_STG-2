#pragma once
#include <Novice.h>
#include "Vector2.h"

const int kPlayerBulletNum = 5;
const int kInvisibleTimer = 120;

class PlayerBullet;

class Player
{
public:
	Player();
	~Player();
public:
	void Init();
	void Update(char* keys, char* preKeys);
	void Draw();
public:
	Vector2 GetPos() { return pos_; }
	int GetHp() { return hp_; }
	float GetRad() { return rad_; }
public:
	void SetIsDamage(bool flag) { isDamage_ = flag; }
private:
	Vector2 pos_;
	Vector2 velocity_;
	float rad_;
	unsigned int color_;
	int hp_;

	bool isDamage_;
	bool isInvisible_;
	int InvisibleTimer_;

public:
	PlayerBullet* bullet[kPlayerBulletNum];
};

