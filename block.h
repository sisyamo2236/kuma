#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include<d3dx9.h>
#include "object.h"
#include "config.h"
#include "collision.h"

// -----------------------------------------------------------
// マクロ定義
// -----------------------------------------------------------
#define BLOCK_WIDTH (100.0f)
#define BLOCK_HEIGHT (100.0f)


class block :public object {

private:
	

protected:

	

public:

	//コンストラクタ・デストラクタ
	block();
	block(D3DXVECTOR2 pos);
	virtual ~block();

	//ブロックの更新
	virtual void Update();



	//ブロックの描画
	virtual void Draw();

	//ゲッター
	D3DXVECTOR2 GetPos();

	//ブロックのコリジョン取得
	CircleCollision Block_GetCollision(void);

};

#endif
