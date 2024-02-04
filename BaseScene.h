#pragma once
#include "SceneManager.h"


class BaseScene
{
public:
	virtual ~BaseScene() = default;

	virtual void Init() = 0;
	virtual void Update(char* keys, char* preKeys) = 0;
	virtual void Draw() = 0;
public:
	virtual SCENE GetNextScene() = 0;
protected:
	SCENE NextScene;

};

