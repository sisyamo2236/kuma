
#include "ability_bird.h"
#include "key_manager.h"

ability_bird::ability_bird() {



}


ability_bird:: ~ability_bird() {


}


//�A�N�V����
void ability_bird::Action(chichan* pChichan) {

	if (pChichan->GetisJump() && pChichan->GetVectorSpeed().y > 0) {//�W�����v���Ă��邩���~��
		if (KeyManager_Press(KM_ATTACK)) {//�{�^���������Ă����y�������x����܂�
			//pChichan->gravity_correct = 0.0f;
			pChichan->VectorSpeedY_Maltiplication(0.1f);
		}
		else {//�{�^���𗣂�����߂�
			//pChichan->gravity_correct = 1.0f;
		}
	}
	else if (pChichan->GetVectorSpeed().y <= 0) {
		//pChichan->gravity_correct = 1.0f;
	}



}