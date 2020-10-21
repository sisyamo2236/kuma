#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h> //�Z�p�n����������Ƃ��Ɏg�p
#include "config.h"

///////////
//�v���g�^�C�v�錾
///////////





///////////
//�O���[�o���ϐ��錾
///////////
//�C���^�[�t�F�[�X�@�֐��ւ̑���
static LPDIRECT3D9 g_pD3D = NULL;//Direct3D�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3D�f�o�C�X�C���^�[�t�F�[�X


//Direct3D9�̏����� �߂�l:���s������false
bool MYDirect3D_Initialize(HWND hWnd) {

	//Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		//Direct3D�C���^�[�t�F�[�X�̎擾�Ɏ��s
		MessageBox(NULL, "���s���܂���", "�G���[", MB_OK);
		return false;
	}


	////Direct3D�f�o�C�X�̎擾 

	//�f�o�C�X�̎擾�ɕK�v�ȏ��\���̂̍쐬
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�o�b�N�o�b�t�@�̉���
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�o�b�N�o�b�t�@�̏c��
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//�o�b�N�o�b�t�@�̃t�H�[�}�b�g�@�F�炵���@UNKNOWN�ɂ��Ă����΃f�X�N�g�b�v�����ɂȂ�炵��
	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�X���b�v���@�̐ݒ�@�o�b�t�@���ǂ����������Ő؂�ւ��邩�@�ς���K�v�͂Ȃ��炵��
	d3dpp.Windowed = TRUE;//�E�C���h�E or �t���X�N���[��
	d3dpp.EnableAutoDepthStencil = TRUE;//�[�x�o�b�t�@�E�X�e���V���o�b�t�@�̎g�p
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�[�x�o�b�t�@�E�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//�t���X�N���[�����̃��t���b�V�����[�g�̎w��@�E�C���h�E���[�h�̓f�X�N�g�b�v����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//���t���b�V�����[�g��Present�����̊֌W

	////Direct3D�f�o�C�X�̎擾
	//����(�g�p����A�_�v�^�[,3D�v�Z���\�t�g�ł�邩�n�[�h�ł�邩,,���_���\�t�g�ł�邩�n�[�h�ł�邩,�擾����\����,�擾������������)
	HRESULT hr;//�������s�Ƃ����s�̗��R�Ƃ�
	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);

	//HRESULT�^�͐����⎸�s���l�Ƃ��ē����Ă���̂�,���s�␬���������肷��ꍇ�̓}�N���𗘗p����
	//FAILED(hr) SUCCEEDE(hr)
	if (FAILED(hr)) {
		//�f�o�C�X�̎擾�Ɏ��s
		MessageBox(NULL, "Direct3D�f�o�C�X�̎擾�Ɏ��s", "�G���[", MB_OK);
		return false;
	}


	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);




	//�A���t�@�u�����h

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//���u�����h��L���ɂ���
	//������...�`��F = ������`�悷��RGB * ������`�悷��a + ��ʂ�RGB * (1 - ������`�悷��a);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//
	

	//UV�A�h���b�V���O���[�h�̐ݒ� �f�t�H���g�F�_�u�����b�v �J��Ԃ� CLAMP:�Ō�̃s�N�Z����L�΂� MIRROR:����
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(128,128,255,0));


	//����������
	return true;

}


//Direct3D9�̏I��
void MYDirect3D_Finalize() {

	if (g_pDevice) {
		g_pDevice->Release();
		g_pDevice = NULL;
	}

	if (g_pD3D) {
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

LPDIRECT3DDEVICE9 MYDirect3D_GetDevice(void) {

	return g_pDevice;
}