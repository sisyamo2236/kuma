#pragma once
#ifndef DEBUG_FONT_H
#define DEBUG_FONT_H

class debug_font{

private:
	static int g_TextureId;
	texture Texture;
	sprite Sprite;
public: 

	debug_font();
	~debug_font();


	void DebugFont_Draw(float dx, float dy,const char* pString);

	void DebugFont_Draw(float dx, float dy, float size_x, float size_y, const char* pString);

	void DebugFont_Uninit();
};

#endif