#include "SceneManager.h"

#include <Novice.h>

#include "BaseScene.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneGameover.h"
#include "SceneResult.h"
#include "Fade.h"

SceneManager::SceneManager()
{
	m_pScene = new SceneTitle();
	fade = new Fade();
	CurrentScene_ = TITLE;
	NextScene_ = TITLE;

	AnimationFrame_ = 0;
	isInNow_ = false;
	isOutNow_ = false;
}

SceneManager::~SceneManager()
{

}

void SceneManager::ChangeScene()
{
	//シーン切り替えアニメーションとか作るならこの関数に書く

	//もしNextSceneが入力されているならシーンを切り替える
	if (!isInNow_ && !isOutNow_ && NextScene_ != CurrentScene_) {
		isInNow_ = true;
		fade->Init(ADMISSION);
	}

	//インアニメーション
	if (isInNow_ && !isOutNow_) {
		AnimationFrame_++;

		//アニメーション処理
		fade->Update(AnimationFrame_,kAnimationFrame);
		//アニメーション終わった時の処理
		if (AnimationFrame_ == kAnimationFrame) {
			isInNow_ = false;
			isOutNow_ = true;
			AnimationFrame_ = 0;
		}
	}

	//インアニメーション終わったら
	if (!isInNow_ && isOutNow_ && NextScene_ != CurrentScene_) {
		//現在のシーンの削除
		if (m_pScene != NULL) {
			delete m_pScene;
		}
		//次のシーンの挿入
		switch (NextScene_) {          //引数のシーン
		case SCENE::TITLE:
			m_pScene = new SceneTitle();      //タイトルシーンを現在のシーンにする
			CurrentScene_ = NextScene_;
			break;
		case SCENE::GAME:
			m_pScene = new SceneGame();       //ゲームシーンを現在のシーンにする
			CurrentScene_ = NextScene_;
			break;
		case SCENE::GAMEOVER:
			m_pScene = new SceneGameover();       //ゲームオーバーシーンを現在のシーンにする
			CurrentScene_ = NextScene_;
			break;
		case SCENE::RESULT:
			m_pScene = new SceneResult();     //リザルトシーンを現在のシーンにする
			CurrentScene_ = NextScene_;
			break;
		default:
			break;
		}
		//アニメーションの初期化
		fade->Init(EXIT);
	}

	//アウトアニメーション
	if (!isInNow_ && isOutNow_ && NextScene_ == CurrentScene_) {
		AnimationFrame_++;

		//アニメーション処理
		fade->Update(AnimationFrame_, kAnimationFrame);
		//アニメーション終わった時の処理
		if (AnimationFrame_ == kAnimationFrame) {
			isInNow_ = false;
			isOutNow_ = false;
			AnimationFrame_ = 0;
		}
	}



}

void SceneManager::Update(char* keys, char* preKeys)
{
	//シーン毎の更新処理
	if (!isInNow_ && !isOutNow_) {
		m_pScene->Update(keys, preKeys);
	}
	//シーンの更新処理
	NextScene_ = m_pScene->GetNextScene();
	//シーンの切り替え処理
	ChangeScene();

}

void SceneManager::Draw()
{
	m_pScene->Draw();
	fade->Draw();
}
