#pragma once
#ifndef FADE_H
#define FADE_H
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>

typedef enum FadeMode_tag {
	FADE_NONE,
	FADE_IN,
	FADE_OUT

}FadeMode;

class fade{

private:
	texture Texture;
	sprite Sprite;

	FadeMode g_FadeMode;
	D3DXCOLOR g_Color;
	float g_Prop;
	int g_FadeFrame;
	int g_FrameCount;
	int g_FadeStartFrame;
	int g_TextureId;
public:
	fade();
	~fade();

	//初期化
	//void Fade_Initialize();

	//更新
	void Fade_Update();

	//描画
	void Fade_Draw();

	//終了処理
	//void Fade_Finalize();

	void Fade_Start(FadeMode mode,float r, float g, float b,int frame);
	bool Fade_IsFade();

};
#endif