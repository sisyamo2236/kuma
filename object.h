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
	//�`��i�������z�֐��j
	virtual void Draw() = 0;
	//�X�V�i�������z�֐��j
	virtual void Update() = 0;

};

#endif