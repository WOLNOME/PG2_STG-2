#include "SceneGameover.h"

SceneGameover::SceneGameover()
{
	NextScene = GAMEOVER;
	back = Novice::LoadTexture("./Resources/gameover.png");
}

SceneGameover::~SceneGameover()
{
}

void SceneGameover::Init()
{
}

void SceneGameover::Update(char* keys, char* preKeys)
{
	if (keys[DIK_TAB] && !preKeys[DIK_TAB]) {
		NextScene = TITLE;
	}
}

void SceneGameover::Draw()
{
	Novice::DrawSprite(0, 0, back, 1, 1, 0.0f, 0xffffffff);
}
