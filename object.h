#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <d3dx9.h>

class object
{
protected:
	D3DXVECTOR2 pos;
	D3DXVECTOR2 vector_speed;
	int TexId;
public:
	object() {};
	virtual ~object() {};
	//描画（純粋仮想関数）
	virtual void Draw() = 0;
	//更新（純粋仮想関数）
	virtual void Update() = 0;

};

#endif