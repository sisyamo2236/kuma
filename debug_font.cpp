
#include <d3dx9.h>
#include "mydirect3d.h"
#include "game.h"
#include "texture.h"
#include "sprite.h"
#include "debug_font.h"
#include <string.h>
#include <d3d9.h>

#define DEBUG_FONT_WIDTH (32)
#define DEBUG_FONT_HEIGHT (64)
#define DEBUG_FONT_START_CHARCODE (32)

	int debug_font::g_TextureId;

	debug_font::debug_font() {
		g_TextureId = Texture.Texture_SetTextureLoadFile("asset/debug_font_32x64.png");

		
		if (Texture.Texture_Load() > 0) {
			MessageBox(NULL, "テクスチャの読み込みに失敗", "エラー", MB_OK);
		}

		//char buf[64];
		//sprintf(buf, "damage = %d", damage);
		//OutputDebugString("bbb");

	}


	debug_font::~debug_font() {

		

	}

	//デバッグフォントモジュールの表示
	//引数:描画座標,文字列へのポインタ
	void debug_font::DebugFont_Draw(float dx, float dy, const char* pString) {

		for (int i = 0; i < strlen(pString); i++) {

			int tcx = (pString[i] % 16) * DEBUG_FONT_WIDTH;
			int tcy = ((pString[i] - 32) / 16) * DEBUG_FONT_HEIGHT;

			Sprite.Sprite_Draw(g_TextureId, dx + i * DEBUG_FONT_WIDTH, dy, 32, 64, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);

		}

	}

	void debug_font::DebugFont_Draw(float dx, float dy, float size_x, float size_y, const char* pString) {

		for (int i = 0; i < strlen(pString); i++) {

			int tcx = (pString[i] % 16) * DEBUG_FONT_WIDTH;
			int tcy = ((pString[i] - 32) / 16) * DEBUG_FONT_HEIGHT;

			Sprite.Sprite_Draw(g_TextureId, dx + i * size_x, dy, size_x, size_y, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);

		}

	}


	void debug_font::DebugFont_Uninit() {

		Texture.Texture_Release(&g_TextureId, 1);

	}