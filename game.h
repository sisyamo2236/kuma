/////////////////////////////////////
//ゲームモジュール
/////////////////////////////////////

#pragma once

#ifndef GAME_H
#define GAME_H

#include <d3dx9.h>
#include "config.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "debug_font.h"
#include "player.h"
#include "block.h"
#include "judge.h"
#include "collision.h"
#include "block_manager.h"
#include "doll.h"
#include "chichan.h"

enum scene {
	TITLE,
	GAME,
	GAMEOVER,
	GAMEEND,
	RESULT,
	SCENE_MAX
};

typedef struct Vertex2D_tag {
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 Texcoord;

}Vertex2D;


#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define RIGHT_LIMIT (SCREEN_WIDTH - 250.0f) //ゲーム画面右端
#define LEFT_LIMIT (0.0f) //ゲーム画面左端
#define UP_LIMIT (0.0f) //ゲーム画面上端
#define DOWN_LIMIT (SCREEN_HEIGHT - 100) //ゲーム画面下端


class game{

private:
	debug_font Debug_font;
	//player* pPlayer;
	chichan* pChichan;
	block_manager* pBlock_manager;
	Judge* pJudge;
	doll* pDoll[DOLLTYPE_MAX];

public:

	game();
	~game();

	void Game_Initilize();

	//ゲームの更新
	int Game_Update();

	//ゲームの描画
	void Game_Draw();

};

#endif