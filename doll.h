#pragma once
#ifndef DOLL_H
#define DOLL_H

#include <d3dx9.h>
#include "object.h"
#include "config.h"
#include "collision.h"

enum DOLLTYPE {
	GORILLA,
	RABBIT,
	BIRD,
	DOLLTYPE_MAX
};


// -----------------------------------------------------------
// マクロ定義
// -----------------------------------------------------------
#define DOLL_MAX (1)
#define DOLL_HEIGHT (100)
#define DOLL_WIDTH (100)

class doll :public object {

private:
	int dolltype;
	void DollTexSet(int num);

protected:



public:

	//コンストラクタ・デストラクタ
	doll(D3DXVECTOR2 set_pos,int set_dolltype);
	~doll();

	//更新
	void Update();

	//描画
	void Draw();

	//ゲッター
	D3DXVECTOR2 GetPos();
	int GetDollType();

	void DollDestroy();
};

#endif