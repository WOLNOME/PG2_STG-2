#pragma once
#include <Novice.h>
#include "BaseScene.h"
class SceneGameover :public BaseScene
{
public:
	SceneGameover();
	~SceneGameover()override;
public:
	void Init()override;
	void Update(char* keys, char* preKeys)override;
	void Draw()override;
public:
	SCENE GetNextScene()override { return NextScene; }
private:
	int back;
};

