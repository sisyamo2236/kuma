#include "block_manager.h"
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"



/////////////////////////ブロック基底クラス///////////////////////////

block_manager::block_manager() {


	for (int i = 0; i < BLOCK_MAX; i++) {

		pblock[i] = NULL;
	}
}

block_manager::block_manager(D3DXVECTOR2 pos) {

	for (int i = 0; i < BLOCK_MAX; i++) {

		pblock[i] = NULL;
	}
}

block_manager::~block_manager() {

	for (int i = 0; i < BLOCK_MAX; i++) {

		delete pblock[i];
		pblock[i] = NULL;
	}
}


//ブロックの更新
void block_manager::Update() {







}

//ブロックの設置
void block_manager::SetBlock(float x, float y) {

	for (int i = 0; i < BLOCK_MAX; i++) {
		if (pblock[i] != NULL)
		{
			continue;

		}
		pblock[i] = new block(D3DXVECTOR2(x,y));

		break;
	}


}

//ブロックの描画
void block_manager::Draw() {


	for (int i = 0; i < BLOCK_MAX; i++) {
		if (pblock[i] == NULL)
		{
			continue;

		}
		pblock[i]->Draw();

	}


}

//ブロックのポジションのゲッター
block *block_manager::GetBlock(int num) {


	return pblock[num];

}

//void block_manager::Destroy(int index) {
//
//
//}
//
//bool block_manager::IsEnable(int index) {
//
//
//}
//
//
//int block_manager::GetCountMax(void) {
//
//
//}
//
//

