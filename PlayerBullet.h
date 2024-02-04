#pragma once
#include <Novice.h>
#include "Vector2.h"
class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();
public:
	void Init(Vector2 PlayerPos);
	void Update();
	void Draw();
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
};

