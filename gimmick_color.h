
#ifndef SELECT_COLOR_H
#define SELECT_COLOR_H

#include "object.h"
#include "config.h"


enum C_color
{
   RED,
   BULE,
   GREEN,
   COLOR_MAX,
};


typedef struct Select_Color{

	int Current_Color;//色の選択
	int Have_Color;//持っている色

}Select_Color;


class gimmick_color {

private:
	
	Select_Color S_color[COLOR_MAX];
	int Select;

protected:



public:

	void change_color();

	gimmick_color();
	virtual ~gimmick_color();

	void Use_Color();
	
	void gimmick_color_Draw();
	
};


#endif // SELECT_COLOR_H


