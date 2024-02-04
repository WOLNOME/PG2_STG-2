#pragma once
#include <Novice.h>
#include "BaseScene.h"
class SceneResult :public BaseScene
{
public:
	SceneResult();
	~SceneResult()override;
public:
	void Init()override;
	void Update(char* keys, char* preKeys)override;
	void Draw()override;
public:
	SCENE GetNextScene()override { return NextScene; }
private:
	int back;
};

