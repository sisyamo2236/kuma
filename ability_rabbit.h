#pragma once
#ifndef ABILITY_RABBIT_H
#define ABILITY_RABBIT_H

#include "ability.h"
#include "chichan.h"

class ability_rabbit : public ability {

private:


public:
	ability_rabbit();
	~ability_rabbit();
	//アクション
	void Action(chichan* pChichan);
};



#endif