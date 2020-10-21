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

	//ƒQ[ƒ€‚ÌXV
	void Judge_Update(chichan* pPlayer, block_manager* pBlock_manager);
	void Judge_Update(chichan* pPlayer, block_manager* pBlock_manager,doll* pDoll);

	void JudgePlayerandBlock(chichan* pPlayer, block_manager* pBlock_manager);//player‚Æblock‚Ì“–‚½‚è”»’èˆ—
	void JudgePlayerandDoll(chichan* pPlayer,doll* pDoll);//player‚Ædoll‚Ì“–‚½‚è”»’èˆ—

};



#endif // !GAME_UDGMENT_H
