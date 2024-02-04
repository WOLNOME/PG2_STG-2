#pragma once
#include <Novice.h>
#include "Vector2.h"
#include "const.h"

enum KindAni {
	ADMISSION,
	EXIT
};

class Fade
{
public:
	Fade();
	~Fade();

	void Init(KindAni which);
	void Update(int AnimationFrame,int kAnimationFrame);
	void Draw();
private:
	Vector2 pos_;
	Vector2 size_;
	unsigned int color_;

	KindAni which_;
};

