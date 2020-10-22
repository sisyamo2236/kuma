
#include "ability_bird.h"
#include "key_manager.h"

ability_bird::ability_bird() {



}


ability_bird:: ~ability_bird() {


}


//アクション
void ability_bird::Action(chichan* pChichan) {

	if (pChichan->GetisJump() && pChichan->GetVectorSpeed().y > 0) {//ジャンプしているかつ下降中
		if (KeyManager_Press(KM_ATTACK)) {//ボタンを押している間y方向速度が弱まる
			//pChichan->gravity_correct = 0.0f;
			pChichan->VectorSpeedY_Maltiplication(0.1f);
		}
		else {//ボタンを離したら戻る
			//pChichan->gravity_correct = 1.0f;
		}
	}
	else if (pChichan->GetVectorSpeed().y <= 0) {
		//pChichan->gravity_correct = 1.0f;
	}



}