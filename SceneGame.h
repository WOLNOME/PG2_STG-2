#pragma once
#include "BaseScene.h"

#include <math.h>
#include "Vector2.h"
#include "const.h"

const int kEnemyNum = 10;

class Player;
class Enemy;

class SceneGame :public BaseScene
{
public:
	SceneGame();
	~SceneGame()override;
public:
	void Init()override;
	void Update(char* keys, char* preKeys)override;
	void Draw()override;
private:
	bool CollisionCheck(Vector2 pos1, Vector2 pos2, float rad_1, float rad_2);
public:
	SCENE GetNextScene()override { return NextScene; }
private:
	int timer_;
	int seconds_;
	int ecount_;

	int back;
	int move_;
private:
	Player* player;
	Enemy* enemy[kEnemyNum];
};

