
#include "chichan.h"
#include "texture.h"
#include "sprite.h"
#include "debug_font.h"
#include "ability_rabbit.h"

#include <stdio.h>
#include "game.h"

#define DEFAULT_LIFE (10) //�����Ȃ�


chichan::chichan(D3DXVECTOR2 set_pos) {

	texture Texture;

	//�V�X�e��
	TexId = Texture.Texture_SetTextureLoadFile("asset/chichan.png");
	if (Texture.Texture_Load() > 0) {
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s", "�G���[", MB_OK);
	}

	pos = set_pos;
	vector_speed.x = vector_speed.y = 0.0f;
	isJump = true;
	life = DEFAULT_LIFE;

	for (int i = 0; i < 4; i++) {
		AvailableAbility[i] = false;
		pAbility[i] = NULL;
	}
}

chichan::~chichan() {

	
}

///////////�A�r���e�B�̎擾�E��������//////////////////////
void chichan::GetAbility(int ability_num) {

	AvailableAbility[ability_num] = true;

	switch (ability_num)
	{

	case GORILLA:

		break;

	case RABBIT:

		pAbility[ability_num] = new ability_rabbit;

		break;

	case BIRD:

		break;

	}


}

void chichan::LostAbility(int ability_num) {

	AvailableAbility[ability_num] = false;

}

// ---------------------------------------------------------------------------
// �֐���:	void Draw( void )
// ����:	void
// �߂�l:  �Ȃ�
// ����:	�`��֐�
// ---------------------------------------------------------------------------
void chichan::Draw() {

	sprite Sprite;
	debug_font Debug_font;

	Sprite.Sprite_Draw(TexId, pos.x, pos.y, PLAYER_SIZE, PLAYER_SIZE);

	for (int i = 0; i < DOLLTYPE_MAX; i++) {
		char buf[64];
		sprintf(buf, "%d", AvailableAbility[i]);
		Debug_font.DebugFont_Draw(i*50, 0, buf);
	}
}

void chichan::Update() {


	past_pos = pos;

	//�d�͂ɂ�����
	PlayerGravity();

	//�ړ�
	pos += vector_speed;

	//�ړ��̕␳
	if (pos.y > DOWN_LIMIT) {
		pos.y = past_pos.y;

	}
	vector_speed.x = 0.0f;


}



