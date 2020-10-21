
#include "doll.h"
#include "texture.h"
#include "sprite.h"



doll::doll(D3DXVECTOR2 set_pos, int set_dolltype) {

	DollTexSet(set_dolltype);
	dolltype = set_dolltype;
	pos = set_pos;
	vector_speed.x = vector_speed.y = 0.0f;

}


doll::~doll() {




}

//更新
void doll::Update() {



}

//描画
void doll::Draw() {

	sprite Sprite;

	//ブロックの描画
	Sprite.Sprite_Draw(TexId, pos.x, pos.y, DOLL_WIDTH, DOLL_HEIGHT);


}

//ゲッター
D3DXVECTOR2 doll::GetPos() {

	return  pos;

}

int doll::GetDollType() {

	return  dolltype;

}

//テクスチャのセット
void doll::DollTexSet(int num) {

	texture Texture;

	switch (num) {

	case GORILLA:
		TexId = Texture.Texture_SetTextureLoadFile("asset/gollira.png");
		if (Texture.Texture_Load() > 0) {
			MessageBox(NULL, "テクスチャの読み込みに失敗", "エラー", MB_OK);
		}
		break;
	case RABBIT:
		TexId = Texture.Texture_SetTextureLoadFile("asset/rabbit.png");
		if (Texture.Texture_Load() > 0) {
			MessageBox(NULL, "テクスチャの読み込みに失敗", "エラー", MB_OK);
		}
		break;
	case BIRD:
		TexId = Texture.Texture_SetTextureLoadFile("asset/bird.png");
		if (Texture.Texture_Load() > 0) {
			MessageBox(NULL, "テクスチャの読み込みに失敗", "エラー", MB_OK);
		}
		break;




	}

}
