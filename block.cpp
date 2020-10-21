
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"
#include<stdio.h>


/////////////////////////ブロック基底クラス///////////////////////////

block::block() {

	//テクスチャ読込
	texture Texture;

	TexId = Texture.Texture_SetTextureLoadFile("asset/white.png");
	if (Texture.Texture_Load() > 0) {
		MessageBox(NULL, "テクスチャの読み込みに失敗", "エラー", MB_OK);
	}

	pos.x = (SCREEN_WIDTH / 2) - 200.0f;
	pos.y = SCREEN_HEIGHT - 100;

	//ブロックの設置



}

block::block(D3DXVECTOR2 setpos) {

	texture Texture;

	//システム
	TexId = Texture.Texture_SetTextureLoadFile("asset/white.png");
	if (Texture.Texture_Load() > 0) {
		MessageBox(NULL, "テクスチャの読み込みに失敗", "エラー", MB_OK);
	}
	pos= setpos;


}

block::~block() {


}


//ブロックの更新
void block::Update() {

	



}



//ブロックの描画
void block::Draw() {

	sprite Sprite;

	//ブロックの色
	Sprite.Sprite_SetColor(D3DCOLOR_RGBA(50, 50, 50, 255));
	//ブロックの描画
	Sprite.Sprite_Draw(TexId, pos.x, pos.y, BLOCK_WIDTH, BLOCK_HEIGHT);
	//ブロックの色初期化
	Sprite.Sprite_SetColorDefault();


}

//ブロックのポジションのゲッター
D3DXVECTOR2 block::GetPos() {

	return pos;

}

//ブロックのコリジョン
CircleCollision  block::Block_GetCollision(void)
{

	CircleCollision c = {
		{
			pos.x + BLOCK_WIDTH * 0.5f,
			pos.y + BLOCK_HEIGHT * 0.5f
		},
		BLOCK_WIDTH * 0.5f

	};
	return c;

}


