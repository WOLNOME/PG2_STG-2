#include "SceneResult.h"

SceneResult::SceneResult()
{
	NextScene = RESULT;
	back = Novice::LoadTexture("./Resources/gameclear.png");
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
}

void SceneResult::Update(char* keys, char* preKeys)
{
	if (keys[DIK_TAB] && !preKeys[DIK_TAB]) {
		NextScene = TITLE;
	}
}

void SceneResult::Draw()
{
	Novice::DrawSprite(0, 0, back, 1, 1, 0.0f, 0xffffffff);
}
