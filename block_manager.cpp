#include "block_manager.h"
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"



/////////////////////////�u���b�N���N���X///////////////////////////

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


//�u���b�N�̍X�V
void block_manager::Update() {







}

//�u���b�N�̐ݒu
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

//�u���b�N�̕`��
void block_manager::Draw() {


	for (int i = 0; i < BLOCK_MAX; i++) {
		if (pblock[i] == NULL)
		{
			continue;

		}
		pblock[i]->Draw();

	}


}

//�u���b�N�̃|�W�V�����̃Q�b�^�[
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

