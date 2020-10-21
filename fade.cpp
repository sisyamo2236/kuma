#include "fade.h"
#include "texture.h"
#include "sprite.h"
#include "config.h"
#include <d3dx9.h>
#include <stdio.h>


fade::fade() {

	g_FadeMode = FADE_NONE;
	g_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Prop = 0.0f;
	g_FadeFrame = 0;
	g_FrameCount = 0;
	g_FadeStartFrame = 0;
	g_TextureId = TEXTURE_INVALID_ID;

	g_TextureId = Texture.Texture_SetTextureLoadFile("asset/white.png");

	if (Texture.Texture_Load() > 0) {
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s", "�G���[", MB_OK);
	}
	//char buf[64];
	//sprintf(buf, "damage = %d", damage);
	OutputDebugString("www");
}

fade::~fade() {
	//Texture.Texture_Release(&g_TextureId, 1);

}

//�X�V
void fade::Fade_Update() {

	g_FrameCount++;

	//�t�F�[�h���ĂȂ�������I���
	if (g_FadeMode == FADE_NONE) return;

	int frame = g_FrameCount - g_FadeStartFrame;

	//�i�s�����̎Z�o
	g_Prop = (float)frame / g_FadeFrame;

	if (g_Prop > 1.0f) {

		g_FadeMode = FADE_NONE;
		g_Prop = 0;

		OutputDebugString("tyu");
	}


}

//�`��
void fade::Fade_Draw() {

	g_Color.a = g_FadeMode == FADE_IN ? 1 - g_Prop : g_Prop;

	//�قړ����Ȃ̂ŕ`�悵�Ȃ�
	if (g_Color.a <= 0.0001f) return;

	Sprite.Sprite_SetColor(g_Color);
	Sprite.Sprite_Draw(g_TextureId,0.0f,0.0f,SCREEN_WIDTH,SCREEN_HEIGHT,0,0,8,8);

	Sprite.Sprite_SetColorDefault();

}


void fade::Fade_Start(FadeMode mode, float r, float g, float b, int frame) {

	g_FadeMode = mode;
	g_Color = D3DXCOLOR(r, g, b, 0.0f);
	g_Prop = 0.0f;
	g_FadeFrame = frame;
	g_FadeStartFrame = g_FrameCount;
	

}

bool fade::Fade_IsFade() {

	return g_FadeMode != FADE_NONE;
}