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
	void PlayerGravity();//playerに重力をかける
	bool isJump;
	D3DXVECTOR2 past_pos;
public:
	
	//コンストラクタ・デストラクタ
	player();
	player(D3DXVECTOR2 pos);
	virtual ~player();

	//ゲームの更新
	virtual void Update();

	//ゲームの描画
	virtual void Draw();

	//ゲッター
	int Getlife();
	D3DXVECTOR2 GetPos();
	D3DXVECTOR2 GetPastPos();
	D3DXVECTOR2 GetVectorSpeed();
	bool GetisJump();

	//移動処理
	void moveX(float num);
	void moveY(float num);

	//操作
	virtual void Player_Z_Action();

	//アクション
	void Jump();

	//コリジョン
	CircleCollision Player_GetCollision();

	//プレイヤーの移動変更関数
	void ChangePosX();
	void ChangePosY();

	//プレイヤーのジャンプ判定関数
	void JumpFlagOn();
	void JumpFlagOff();

	//パラメータ操作
	void LifeControll(int num);//lifeにnumで足し算する
	void VectorSpeedY_Maltiplication(float num);//vectorspeedにnumで掛け算する

	//パラメータ補正値
	float jump_correct;
	float gravity_correct;

};

#endif