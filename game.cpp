#include <d3dx9.h>
#include "mydirect3d.h"
#include "game.h"
#include "texture.h"
#include "sprite.h"
#include <d3d9.h>
#include "debug_font.h"
#include "keyboard.h"
#include "key_manager.h"
#include "mouse.h"
#include "sound.h"
#include "fade.h"
#include "debug_primitive.h"
#include "block.h"
#include "chichan.h"
#include "doll.h"

	game::game() {



	}

	game::~game(){



	}

	void game::Game_Initilize() {

		//�e�N���X�̏�����
		pChichan = new chichan(D3DXVECTOR2(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 300));
		pJudge = new Judge();
		pBlock_manager = new block_manager();

		//�u���b�N���ݒu
		pBlock_manager->SetBlock(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
		pBlock_manager->SetBlock((SCREEN_WIDTH / 2)+100.0f, SCREEN_HEIGHT - 100);
	
		//pBlock_manager->SetBlock(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 350);
		pBlock_manager->SetBlock((SCREEN_WIDTH / 2) + 100.0f, SCREEN_HEIGHT - 350);
	

		//�A�r���e�B�֘A

		//�ꎞ�I�����@�A�r���e�B�擾�����ɂ��ύX
		for (int i = 0; i < DOLLTYPE_MAX; i++) {
			pDoll[i] = NULL;

		}
		pDoll[RABBIT] = new doll(D3DXVECTOR2(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 300), RABBIT);
		pDoll[BIRD] = new doll(D3DXVECTOR2(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 300), BIRD);


	}


	//�Q�[���̍X�V
	int game:: Game_Update() {

		//����
		if (KeyManager_Trigger(KM_ATTACK)) {//Z�L�[

			pChichan->Player_Z_Action();
		}
		else if (KeyManager_Trigger(KM_BOMB)) {//X�L�[		
			
		}
		else if (KeyManager_Trigger(KM_CHANGE)) {//C�L�[

		}

		if (KeyManager_Press(KM_RIGHT)) pChichan->moveX(1.0f);//�E�L�[
		if (KeyManager_Press(KM_LEFT))  pChichan->moveX(-1.0f);//���L�[
		//if (KeyManager_Press(KM_DOWN))  //��L�[
		//if (KeyManager_Press(KM_UP))    //���L�[

		//�I�u�W�F�N�g
		pChichan->Update();

		//�ꎞ�I�����@�A�r���e�B�擾�����ɂ��ύX
		for (int i = 0; i < DOLLTYPE_MAX; i++) {
			if (pDoll[i] != NULL) {
				pJudge->Judge_Update(pChichan, pBlock_manager, pDoll[i]);
			}
		}
		//pJudge->Judge_Update(pChichan, pBlock_manager,pDoll);



		return 0;
	}

	//�Q�[���̕`��
	void game:: Game_Draw() {

		sprite Sprite;

		//�I�u�W�F�N�g
		pChichan->Draw();
		pBlock_manager->Draw();




		//�ꎞ�I�����@�A�r���e�B�擾�����ɂ��ύX
		for (int i = 0; i < DOLLTYPE_MAX; i++) {
			if (pDoll[i] != NULL) {
				pDoll[i]->Draw();
			}
		}
	}
