#pragma once
#ifndef ABILITY_H
#define ABILITY_H

class chichan;

class ability {

private:

public:
	ability() {};
	virtual ~ability() {};
	//アクション
	virtual void Action(chichan* pChichan) {};
	
};



#endif