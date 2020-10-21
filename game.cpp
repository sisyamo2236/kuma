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

		//各クラスの初期化
		pChichan = new chichan(D3DXVECTOR2(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 300));
		pJudge = new Judge();
		pBlock_manager = new block_manager();
		pDoll = new doll(D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT - 300),RABBIT);


		//ブロック仮設置
		pBlock_manager->SetBlock(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
		pBlock_manager->SetBlock((SCREEN_WIDTH / 2)+100.0f, SCREEN_HEIGHT - 100);
	
		//pBlock_manager->SetBlock(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 350);
		pBlock_manager->SetBlock((SCREEN_WIDTH / 2) + 100.0f, SCREEN_HEIGHT - 350);
	
	}


	//ゲームの更新
	int game:: Game_Update() {

		//操作
		if (KeyManager_Trigger(KM_ATTACK)) {//Zキー

			pChichan->Player_Z_Action();
		}
		else if (KeyManager_Trigger(KM_BOMB)) {//Xキー		
			
		}
		else if (KeyManager_Trigger(KM_CHANGE)) {//Cキー

		}

		if (KeyManager_Press(KM_RIGHT)) pChichan->moveX(1.0f);//右キー
		if (KeyManager_Press(KM_LEFT))  pChichan->moveX(-1.0f);//左キー
		//if (KeyManager_Press(KM_DOWN))  //上キー
		//if (KeyManager_Press(KM_UP))    //下キー

		//オブジェクト
		pChichan->Update();
		pJudge->Judge_Update(pChichan, pBlock_manager,pDoll);

		return 0;
	}

	//ゲームの描画
	void game:: Game_Draw() {

		sprite Sprite;

		//オブジェクト
		pChichan->Draw();
		pBlock_manager->Draw();
		pDoll->Draw();

	}
