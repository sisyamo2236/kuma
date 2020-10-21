#include "judge.h"
#include<stdio.h>


Judge::Judge() {



}

Judge::~Judge() {



}

void Judge::Judge_Initilize(void)
{
	
}

void Judge::Judge_Update(chichan* pPlayer, block_manager* pBlock_manager)
{
	
	JudgePlayerandBlock(pPlayer,pBlock_manager);

}

void Judge::Judge_Update(chichan* pPlayer,block_manager* pBlock_manager,doll* pDoll)
{

	JudgePlayerandBlock(pPlayer, pBlock_manager);
	JudgePlayerandDoll(pPlayer, pDoll);

}

void Judge::JudgePlayerandBlock(chichan* pPlayer, block_manager* pBlock_manager)
{
	block* pBlock;

	for (int i = 0; i < BLOCK_MAX; i++) {
		pBlock = pBlock_manager->GetBlock(i);

		if (pBlock == NULL) {
			continue;
		}
		//ブロックとプレイヤーの当たり判定条件式
		if (pBlock->GetPos().x <= pPlayer->GetPos().x + PLAYER_SIZE && pPlayer->GetPos().x <= pBlock->GetPos().x + (BLOCK_WIDTH)
			&& pBlock->GetPos().y <= pPlayer->GetPos().y + (PLAYER_SIZE) && pPlayer->GetPos().y <= pBlock->GetPos().y + (BLOCK_HEIGHT)) {

			//ブロックとの上で移動するための条件式
			if (pBlock->GetPos().y >= pPlayer->GetPos().y + (PLAYER_SIZE)) {

				pPlayer->ChangePosY();
				pPlayer->JumpFlagOn();
			}
			else if (pBlock->GetPos().y + (BLOCK_HEIGHT) <= pPlayer->GetPos().y + (PLAYER_SIZE))
			{
				pPlayer->ChangePosY();
				pPlayer->ChangePosX();
			}
			else
			{
				pPlayer->ChangePosX();
			}

		}
	}
}

void Judge::JudgePlayerandDoll(chichan* pPlayer, doll* pDoll)
{

	for (int i = 0; i < DOLL_MAX; i++) {
		//pBlock = pBlock_manager->GetBlock(i);

		if (pDoll == NULL) {
			continue;
		}
		//ブロックとプレイヤーの当たり判定条件式
		if (pDoll->GetPos().x <= pPlayer->GetPos().x + PLAYER_SIZE && pPlayer->GetPos().x <= pDoll->GetPos().x + (DOLL_WIDTH)
			&& pDoll->GetPos().y <= pPlayer->GetPos().y + (PLAYER_SIZE) && pPlayer->GetPos().y <= pDoll->GetPos().y + (DOLL_HEIGHT)) {

			//取得(仮)
			pPlayer->GetAbility(pDoll->GetDollType());

		}
	}
}