#pragma once

const int kAnimationFrame = 20;

enum SCENE {
	TITLE,
	GAME,
	GAMEOVER,
	RESULT
};

class Fade;
class BaseScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void ChangeScene();//シーンを変える関数
	void Update(char* keys, char* preKeys);//現在シーンの更新関数
	void Draw();//現在シーンの描画関数
private:
	int AnimationFrame_;
	bool isInNow_;
	bool isOutNow_;
private:
	BaseScene* m_pScene;
	Fade* fade;
	SCENE CurrentScene_;
	SCENE NextScene_;
};

