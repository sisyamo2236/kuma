#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d9.h>

//�}�N����`
#define TEXTURE_INVALID_ID (-1) //�����ȃe�N�X�`���Ǘ��ԍ�
#define TEXTURE_FILENAME_MAX (64)//�e�N�X�`���t�@�C�����ő啶����
#define TEXTURE_MAX (1024)//�e�N�X�`���Ǘ��ő吔


class texture{

public:
	texture(bool init);
	texture();
	~texture();

	//�e�N�X�`���Ǘ����W���[���̏�����
	int Texture_Initialize();

	//�e�N�X�`���Ǘ����W���[���̏I������
	//void Texture_Finalize();

	////�e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
	//����:�t�@�C����
	//�߂�l:�e�N�X�`���Ǘ��ԍ� 
	//       �ő�Ǘ����𒴂��Ă����ꍇ��-1(INVALID_TEXTURE_ID)
	int Texture_SetTextureLoadFile(const char* pFileName);

	//�e�N�X�`���̓ǂݍ���
	//�\�񂳂�Ă���t�@�C����ǂݍ���
	//�߂�l:�ǂݍ��߂Ȃ������t�@�C����
	int Texture_Load();

	//�e�N�X�`���̕����J��
	//����:textureIds[]...���������textureId��������int�^�z��̐擪�A�h���X
	//     count       ...�������e�N�X�`���̐�

	void Texture_Release(int textureIds[], int count);

	//�e�N�X�`���̑S�J��
	void Texture_AllRelease();

	//�e�N�X�`���̕��̎擾
	//����:�e�N�X�`���Ǘ��ԍ�
	//�߂�l:�e�N�X�`���̕��E����
	unsigned long Texture_GetTextureWidth(int textureId);
	unsigned long Texture_GetTextureHeight(int textureId);

	//�e�N�X�`���C���^�[�t�F�[�X�|�C���^�̎擾
	//����:�e�N�X�`���Ǘ��ԍ�
	//�߂�l:�e�N�X�`���C���^�[�t�F�[�X�|�C���^
	//       �ǂݍ��߂Ă��Ȃ��܂��͕s���ȊǗ��ԍ��������ꍇNULL
	LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId);


};

#endif