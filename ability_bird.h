#pragma once
#ifndef ABILITY_BIRD_H
#define ABILITY_BIRD_H

#include "ability.h"
#include "chichan.h"

class ability_bird : public ability {

private:


public:
	ability_bird();
	~ability_bird();
	//ƒAƒNƒVƒ‡ƒ“
	void Action(chichan* pChichan);
};



#endif