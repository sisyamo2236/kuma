
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"
#include<stdio.h>


/////////////////////////�u���b�N���N���X///////////////////////////

block::block() {

	//�e�N�X�`���Ǎ�
	texture Texture;

	TexId = Texture.Texture_SetTextureLoadFile("asset/white.png");
	if (Texture.Texture_Load() > 0) {
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s", "�G���[", MB_OK);
	}

	pos.x = (SCREEN_WIDTH / 2) - 200.0f;
	pos.y = SCREEN_HEIGHT - 100;

	//�u���b�N�̐ݒu



}

block::block(D3DXVECTOR2 setpos) {

	texture Texture;

	//�V�X�e��
	TexId = Texture.Texture_SetTextureLoadFile("asset/white.png");
	if (Texture.Texture_Load() > 0) {
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s", "�G���[", MB_OK);
	}
	pos= setpos;


}

block::~block() {


}


//�u���b�N�̍X�V
void block::Update() {

	



}



//�u���b�N�̕`��
void block::Draw() {

	sprite Sprite;

	//�u���b�N�̐F
	Sprite.Sprite_SetColor(D3DCOLOR_RGBA(50, 50, 50, 255));
	//�u���b�N�̕`��
	Sprite.Sprite_Draw(TexId, pos.x, pos.y, BLOCK_WIDTH, BLOCK_HEIGHT);
	//�u���b�N�̐F������
	Sprite.Sprite_SetColorDefault();


}

//�u���b�N�̃|�W�V�����̃Q�b�^�[
D3DXVECTOR2 block::GetPos() {

	return pos;

}

//�u���b�N�̃R���W����
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


