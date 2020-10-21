#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include<d3dx9.h>
#include "object.h"
#include "config.h"
#include "collision.h"

// -----------------------------------------------------------
// �}�N����`
// -----------------------------------------------------------
#define BLOCK_WIDTH (100.0f)
#define BLOCK_HEIGHT (100.0f)


class block :public object {

private:
	

protected:

	

public:

	//�R���X�g���N�^�E�f�X�g���N�^
	block();
	block(D3DXVECTOR2 pos);
	virtual ~block();

	//�u���b�N�̍X�V
	virtual void Update();



	//�u���b�N�̕`��
	virtual void Draw();

	//�Q�b�^�[
	D3DXVECTOR2 GetPos();

	//�u���b�N�̃R���W�����擾
	CircleCollision Block_GetCollision(void);

};

#endif
