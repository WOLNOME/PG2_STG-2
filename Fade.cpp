#include "Fade.h"

Fade::Fade()
{
}

Fade::~Fade()
{
}

void Fade::Init(KindAni which)
{
	which_ = which;
	color_ = 0x333333ff;
	switch (which_)
	{
	case ADMISSION:
		pos_ = { 0,0 };
		size_ = { 0,kWindowHeight };
		break;
	case EXIT:
		pos_ = { 0,0 };
		size_ = { kWindowWidth,kWindowHeight };
		break;
	default:
		break;
	}
}

void Fade::Update(int AnimationFrame, int kAnimationFrame)
{
	float normalize;
	switch (which_)
	{
	case ADMISSION:
		normalize = (float)AnimationFrame / kAnimationFrame;

		size_.x = kWindowWidth * normalize;

		break;
	case EXIT:
		normalize = (float)AnimationFrame / kAnimationFrame;

		size_.x = kWindowWidth+1 - kWindowWidth * normalize;
		pos_.x = kWindowWidth * normalize;

		break;
	default:
		break;
	}
}

void Fade::Draw()
{
	Novice::DrawBox((int)pos_.x, (int)pos_.y, (int)size_.x, (int)size_.y, 0.0f, color_, kFillModeSolid);
}
