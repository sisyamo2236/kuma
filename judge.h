#ifndef JUDGE_H
#define JUDGE_H

#include "collision.h"

#include "player.h"
#include "block.h"
#include "block_manager.h"
#include "doll.h"
#include "chichan.h"

class Judge {

private:

	player* pPlayer;
	block_manager* pBlock_manager;

public:

	Judge();
	~Judge();

	void Judge_Initilize();

	//�Q�[���̍X�V
	void Judge_Update(chichan* pPlayer, block_manager* pBlock_manager);
	void Judge_Update(chichan* pPlayer, block_manager* pBlock_manager,doll* pDoll);

	void JudgePlayerandBlock(chichan* pPlayer, block_manager* pBlock_manager);//player��block�̓����蔻�菈��
	void JudgePlayerandDoll(chichan* pPlayer,doll* pDoll);//player��doll�̓����蔻�菈��

};



#endif // !GAME_UDGMENT_H
