#pragma once

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

#include "object.h"
#include "config.h"
#include "collision.h"


#define GRAVITY_SCALE (5.0f)
#define PLAYER_SIZE (100.0f)

class player:public object {

private:

protected:

	float speed;
	int life;
	void PlayerGravity();//player�ɏd�͂�������
	bool isJump;
	D3DXVECTOR2 past_pos;
public:
	
	//�R���X�g���N�^�E�f�X�g���N�^
	player();
	player(D3DXVECTOR2 pos);
	virtual ~player();

	//�Q�[���̍X�V
	virtual void Update();

	//�Q�[���̕`��
	virtual void Draw();

	//�Q�b�^�[
	int Getlife();
	D3DXVECTOR2 GetPos();
	D3DXVECTOR2 GetPastPos();
	D3DXVECTOR2 GetVectorSpeed();
	bool GetisJump();

	//�ړ�����
	void moveX(float num);
	void moveY(float num);

	//����
	virtual void Player_Z_Action();

	//�A�N�V����
	void Jump();

	//�R���W����
	CircleCollision Player_GetCollision();

	//�v���C���[�̈ړ��ύX�֐�
	void ChangePosX();
	void ChangePosY();

	//�v���C���[�̃W�����v����֐�
	void JumpFlagOn();
	void JumpFlagOff();

	//�p�����[�^����
	void LifeControll(int num);//life��num�ő����Z����
	void VectorSpeedY_Maltiplication(float num);//vectorspeed��num�Ŋ|���Z����

	//�p�����[�^�␳�l
	float jump_correct;
	float gravity_correct;

};

#endif