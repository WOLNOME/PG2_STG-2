#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	NextScene = TITLE;
	back = Novice::LoadTexture("./Resources/title.png");
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::Update(char* keys, char* preKeys)
{
	if (keys[DIK_TAB] && !preKeys[DIK_TAB]) {
		NextScene = GAME;
	}
}

void SceneTitle::Draw()
{
	Novice::DrawSprite(0, 0, back, 1, 1, 0.0f, 0xffffffff);
}
