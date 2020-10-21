#pragma once

#ifndef CHICHAN_H
#define CHICHAN_H

#include "player.h"
#include "config.h"
#include "doll.h"
#include "ability.h"

#define GRAVITY_SCALE (5.0f)
#define PLAYER_SIZE (100.0f)

class chichan :public player {

private:
	bool AvailableAbility[DOLLTYPE_MAX];//使用可能アビリティ
	ability* pAbility[DOLLTYPE_MAX];

	void AbilityAction();

public:


	//chichan();
	chichan(D3DXVECTOR2 set_pos);
	~chichan();

	void Draw();
	void Update();

	void GetAbility(int ability_num);
	void LostAbility(int ability_num);


};

#endif