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

	//�R���X�g���N�^�E�f�X�g���N�^
	block_manager();
	block_manager(D3DXVECTOR2 pos);
	~block_manager();

	//�u���b�N�̍X�V
	void Update();

	//�u���b�N�̐ݒu
	void SetBlock(float x, float y);

	//�u���b�N�̕`��
	void Draw();

	void Destroy(int index);

	bool IsEnable(int index);

	int GetCountMax(void);

	block *GetBlock(int num);
};

#endif

