#pragma once
#pragma once

#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include<d3dx9.h>
#include "config.h"
#include "collision.h"
#include "block.h"

#define BLOCK_MAX (10)


class block_manager {

private:
	block *pblock[BLOCK_MAX];

protected:



public:

	//コンストラクタ・デストラクタ
	block_manager();
	block_manager(D3DXVECTOR2 pos);
	~block_manager();

	//ブロックの更新
	void Update();

	//ブロックの設置
	void SetBlock(float x, float y);

	//ブロックの描画
	void Draw();

	void Destroy(int index);

	bool IsEnable(int index);

	int GetCountMax(void);

	block *GetBlock(int num);
};

#endif

