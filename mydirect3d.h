#pragma once
//
//
#include <d3d9.h>

#ifndef MY_DIRECT3D_H
#define MY_DIRECT3D_H

//Direct3D9�̏����� �߂�l:���s������false
bool MYDirect3D_Initialize(HWND hWnd);

//Direct3D9�̏I��
void MYDirect3D_Finalize();

//Direct3D�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 MYDirect3D_GetDevice(void);//�A�N�Z�T�[(�Q�b�^�[�E�Z�b�^�[)

#endif //MY_DIRECT3D_H