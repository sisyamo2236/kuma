#pragma once
#ifndef ABILITY_H
#define ABILITY_H



class ability {

private:


public:
	ability() {};
	virtual ~ability() {};
	//アクション（純粋仮想関数）
	virtual void Action() = 0;
	
};



#endif