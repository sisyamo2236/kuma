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


	game::game() {



	}

	game::~game(){



	}

	void game::Game_Initilize() {

		//�e�N���X�̏�����
		pChichan = new chichan(D3DXVECTOR2(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 300));
		pJudge = new Judge();
		pBlock_manager = new block_manager();
		pDoll = new doll(D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT - 300),RABBIT);


		//�u���b�N���ݒu
		pBlock_manager->SetBlock(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
		pBlock_manager->SetBlock((SCREEN_WIDTH / 2)+100.0f, SCREEN_HEIGHT - 100);
	
		//pBlock_manager->SetBlock(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 350);
		pBlock_manager->SetBlock((SCREEN_WIDTH / 2) + 100.0f, SCREEN_HEIGHT - 350);
	
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
		pJudge->Judge_Update(pChichan, pBlock_manager,pDoll);

		return 0;
	}

	//�Q�[���̕`��
	void game:: Game_Draw() {

		sprite Sprite;

		//�I�u�W�F�N�g
		pChichan->Draw();
		pBlock_manager->Draw();
		pDoll->Draw();

	}
