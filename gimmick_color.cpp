#include "gimmick_color.h"
#include "texture.h"
#include "sprite.h"
#include "keyboard.h"
#include "key_manager.h"
#include "game.h"

//初期化
gimmick_color::gimmick_color() {

	Select = 0;
	S_color[RED].Have_Color = 5;
	S_color[BULE].Have_Color = 5;
	S_color[GREEN].Have_Color = 5;

	

};

gimmick_color::~gimmick_color() {



};

//色を変える
void gimmick_color::change_color() {

	
	Select++; //色が足されていく

	if (COLOR_MAX <= Select)
	{
		Select = 0;
	}

};


void gimmick_color::Use_Color() {

	//使用した色の所持数を減少させる
	S_color[Select].Have_Color--;

	if (0> S_color[Select].Have_Color)
	{
		S_color[Select].Have_Color = 0;
	}
}

void gimmick_color::gimmick_color_Draw()
{
	debug_font D_font;

	
	if (Select == RED)
	{
		D_font.DebugFont_Draw(0, 0, "RED");
	}
	else if(Select == BULE)
	{
		D_font.DebugFont_Draw(0, 0, "BULE");
	}
	else if(Select == GREEN)
	{
		D_font.DebugFont_Draw(0, 0, "GREEN");
    }

	S_color[Select].Have_Color;

	int RED,BULE,GREEN = 1;
	char R[64];
	sprintf(R, "%d", S_color[Select].Have_Color);
	
	D_font.DebugFont_Draw(200, 0, R);

}	