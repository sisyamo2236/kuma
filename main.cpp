
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h> //�Z�p�n����������Ƃ��Ɏg�p
#include "config.h"
#include "mydirect3d.h"
#include "game.h"
#include "debug_font.h"
#include "system_timer.h"
#include <stdio.h>
#include "keyboard.h"
#include "key_manager.h"
#include "sound.h"
#include "debug_primitive.h"


////////////
//�萔��`
////////////

#define CLASS_NAME "GameWindow"
#define WINDOW_CAPTION "HEW"



///////////
//�v���g�^�C�v�錾
///////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�Q�[���̏����� �߂�l:�������Ɏ��s�����Ƃ�false
static bool Initialize(HWND hWnd,game* Game);
//�Q�[���̍X�V
static int Update(game* Game);
//�Q�[���̕`��
static void Draw(game* Game);
//�Q�[���̏I������
static void Finalize();

///////////
//�O���[�o���ϐ��錾
///////////
LPDIRECT3DDEVICE9 g_pDevice;
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0;
static double g_ReserveTime = 0.0;


/////////
//�\����
/////////



static LPDIRECT3DTEXTURE9 g_pTexture = NULL;//�e�N�X�`���C���^�[�t�F�[�X �e�N�X�`���P�ɂ��P�K�v
static LPDIRECT3DTEXTURE9 g_pTexture2 = NULL;//�e�N�X�`���C���^�[�t�F�[�X �e�N�X�`���P�ɂ��P�K�v
static LPDIRECT3DTEXTURE9 g_pTexture3[6] = {NULL,NULL,NULL,NULL,NULL,NULL};//�e�N�X�`���C���^�[�t�F�[�X �e�N�X�`���P�ɂ��P�K�v



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//�E�C���h�E�\���̂̐ݒ�
	WNDCLASS wc = {};//���g�ɂ��݂��c������ԂŐ錾���Ȃ��悤�ɁA��(0)�ɂ��悤
	wc.lpfnWndProc = WndProc; //�E�C���h�E�v���V�[�W���̓o�^
	wc.lpszClassName = CLASS_NAME;//�N���X���̐ݒ�
	wc.hInstance = hInstance;//�C���X�^���X�n���h���̎w��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//�}�E�X�J�[�\���̎w��
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);//�E�C���h�E�̔w�i�F��ݒ� (COLOR_BACKGROUND��+1�����l�����Ă�������(��)

	RegisterClass(&wc);//�V�X�e���ɃE�C���h�E�\���̂�o�^

	DWORD style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	//�s���̂����E�C���h�E�T�C�Y�̎Z�o
	RECT window_rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	AdjustWindowRect(&window_rect,style,FALSE);
	//�E�C���h�E�g���c������
	LONG ex_left = 0 - window_rect.left;
	LONG ex_top = 0 - window_rect.top;
	LONG ex_right = (window_rect.right - window_rect.left) - SCREEN_WIDTH - ex_left;
	LONG ex_bottom = (window_rect.bottom - window_rect.top) - SCREEN_HEIGHT - ex_top;

	RECT window_rect2 = { 0 + ex_left,0 + ex_top,SCREEN_WIDTH - ex_right,SCREEN_HEIGHT - ex_bottom};
	AdjustWindowRect(&window_rect2, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX), FALSE);

	//�\������E�C���h�E�̏ꏊ���Z�o����
	//�f�X�N�g�b�v(�N���C�A���g�̈�)�̎擾

	//API�𗘗p�����f�X�N�g�b�v�̕��A�����擾
	/*
	RECT desktop_rect;
	GetWindowRect(GetDesktopWindow(),&desktop_rect);
	*/

	//�f�o�C�X(�V�X�e��)���烂�j�^�[�𑜓x���擾
	//�v���C�}�����j�^�[�̉�ʉ𑜓x�擾
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	//���z��ʂ̉𑜓x�擾
	int virtual_desktop_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//���z��ʂ̉𑜓x�擾
	int virtual_desktop_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int virtual_desktop_y = GetSystemMetrics(SM_YVIRTUALSCREEN);

	//max �l�̑傫��������Ԃ�
	int tes = max(-500,0);

	////hWnd �E�C���h�E�n���h��
	//HWND hWnd = CreateWindow(
	//	CLASS_NAME,//�E�C���h�E�N���X�̓o�^
	//	WINDOW_CAPTION,//�^�C�g���̕�����
	//	style,//�E�C���h�E�X�^�C�� (�r�b�g�t���O)
	//	desktop_width/2 - (desktop_width / 2)/2,//�T�C�Y�ƈʒu (CW_USEDEFAULT�E�E�E�V�X�e���C��)
	//	desktop_height / 2 - (desktop_height / 2) / 2,//�E�C���h�E�̍���̈ʒu x//�E�C���h�E�̍���̈ʒu y
	//	desktop_width / 2,//�E�C���h�E��   �t���[���܂߂��S�̂̕��A����
	//	desktop_height / 2,//�E�C���h�E����
	//
	//	NULL,//�e�E�C���h�E�n���h��
	//	NULL,//���j���[�n���h��
	//	hInstance,//�C���X�^���X�n���h��
	//	NULL//�ǉ��̃A�v���P�[�V�����f�[�^(��
	//);

	//hWnd �E�C���h�E�n���h��
	HWND hWnd = CreateWindow(
		CLASS_NAME,//�E�C���h�E�N���X�̓o�^
		WINDOW_CAPTION,//�^�C�g���̕�����
		style,//�E�C���h�E�X�^�C�� (�r�b�g�t���O)
		20,//�T�C�Y�ƈʒu (CW_USEDEFAULT�E�E�E�V�X�e���C��)
		20,//�E�C���h�E�̍���̈ʒu x//�E�C���h�E�̍���̈ʒu y
		SCREEN_WIDTH,//�E�C���h�E��   �t���[���܂߂��S�̂̕��A����
		SCREEN_HEIGHT,//�E�C���h�E����

		NULL,//�e�E�C���h�E�n���h��
		NULL,//���j���[�n���h��
		hInstance,//�C���X�^���X�n���h��
		NULL//�ǉ��̃A�v���P�[�V�����f�[�^(��
	);

	if (hWnd == NULL) {
		//�E�C���h�E�n���h�������炩�̗��R�Ő����ł��Ȃ�����
		return 0;
	}

	//�E�C���h�E�̕\��
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);//�E�C���h�E�̍X�V

	//�Q�[���N���X�̐���
	game* Game = new game;


	//�Q�[���̏����� �����Ɏ��Ԃ������邽�߁A�u���ꏊ�͍l���悤
	if (!Initialize(hWnd,Game)) {
		//���b�Z�[�W�{�b�N�X�ŃQ�[���̏����������s�������߃A�v���P�[�V�������I���������Ƃ�`����
		MessageBox(hWnd, "���������s", "�Q�[���̏��������s", MB_OKCANCEL | MB_DEFBUTTON2);
		return 0;
	}

	MSG msg = {};
	

	Keyboard_Initialize();
 
	//windows�Q�[���p���[�v
	while (WM_QUIT != msg.message) {
		
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {//���b�Z�[�W�������Ă�����擾,�Ȃ��ꍇ0��Ԃ�
			TranslateMessage(&msg);//���b�Z�[�W�̖|��
			DispatchMessage(&msg);//���b�Z�[�W�ɑ΂��鏈�� �E�C���h�E�v���V�[�W���Ŏw�肵���֐����Ă΂��
		}
		else {
			//�������Q�[������
			
			double time = SystemTimer_GetTime();
			if ((time - g_ReserveTime) < 1.0 / 60.0f) {
				Sleep(0);
				continue;
			}
			g_ReserveTime = time;
			
			//�X�V�@����Ă�����update�ɖ߂�l�����ďI���ł���悤�ɂ��悤
			if (Update(Game) == GAMEEND) break;
			
			//�`��
			Draw(Game);
		}
	}

	//�Q�[���̏I������
	Finalize();

	DestroyWindow(hWnd);//hWnd��j��
	return (int)msg.wParam;

}

//����:�Ώۂ̃E�C���h�E�n���h��,���b�Z�[�W,�ǉ��p�����[�^�P,�ǉ��p�����[�^2
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {//�G�X�P�[�v�L�[�������ꂽ�Ƃ�
				SendMessage(hWnd, WM_CLOSE, 0, 0);//������WM_CLOSE�𑗂�
			}
		case WM_ACTIVATEAPP:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			Keyboard_ProcessMessage(uMsg, wParam, lParam);
			break;


		case WM_CLOSE://�E�C���h�E�~�{�^����
			if (MessageBox(hWnd, "�{���ɏI�����Ă���낵���ł���?", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
				DestroyWindow(hWnd);//hWnd��j��

			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);//WM_QUIT���b�Z�[�W�̑��M
			return 0;
	}
	
	//�ʏ�̃��b�Z�[�W�����͂��̊֐��ɔC���� �ǂ��Ɍv�炦
	//�I�����������͔C���Ă͂����Ȃ�(�v���Z�X���I�����Ȃ�����)
	return DefWindowProc(hWnd, uMsg, wParam,lParam);
}

bool Initialize(HWND hWnd,game* Game) {

	debug_font Debug_font;

	Keyboard_Initialize();

	KeyManager_Initilalize();

	//InitSound(hWnd);

	MYDirect3D_Initialize(hWnd);

	/*
	if (!Game_Initialize) {
		MessageBox(NULL,"sippai","error",MB_OK);
	}*/

	g_pDevice = MYDirect3D_GetDevice();
	HRESULT hr;


	g_ReserveTime = g_BaseTime = 0;//SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	SystemTimer_Initialize();

	DebugPrimitive_Initialize();

	Game->Game_Initilize();

	return true;
}


int Update(game* Game) {

	KeyManager_Update();


	//�v��
	double time = SystemTimer_GetTime();
	if (time - g_BaseTime > 1.0) {
		g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
		g_BaseTime = time;
		g_BaseFrame = g_FrameCount;

	}
	g_FrameCount++;

	return Game->Game_Update();

}

void Draw(game* Game) {


	//DirectX�̓|���S�����J�����ɑ΂��ĉE���ɗp�ӂ��Ȃ��ƕ\�ʂ��������������Ȃ����߁A�\������Ȃ�
	//OpenGL�͋t


	//��ʂ̃N���A�@����:��`�̐��A��`�A�h���X,�o�b�t�@�t���O,�o�b�t�@(�F,�[�x,�X�e���V��)
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(255, 200, 200, 255), 1.0f, 0);
	
	//�`��p�b�`���߂̊J�n
	  //�d�������߂�
	g_pDevice->BeginScene();


	//�f�o�b�O�`�揈���̎�t�J�n
	//DebugPrimitive_BatchBegin();

	////���̉��ɕ`�施�߂�����
	Game->Game_Draw();

	//FPS�\��
	
	//char buf[64];
	//sprintf(buf,"F = %.2f",g_FPS);
	//DebugFont_Draw(0,0,buf);

	//�f�o�C�X�̂e�u�e�ݒ�
	g_pDevice->SetFVF(FVF_VERTEX2D);
	
	

	//�f�o�b�O�`�揈���̎��s
	//DebugPrimitive_BatchRun();


	//�`��p�b�`���߂̏I��
	g_pDevice->EndScene();

	//�o�b�N�o�b�t�@���t���b�v(�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��)
	 //���߂��d�������s�@�P�t���[���ɂP��
	 //��ʂ̍X�V�i�������j�܂Ŏ~�܂�
	g_pDevice->Present(NULL, NULL, NULL, NULL);

}


void Finalize() {

	if (g_pTexture) {
		g_pTexture->Release();
		g_pTexture = NULL;
	}

	//DebugFont_Finalize();
	DebugPrimitive_Finalize();

	MYDirect3D_Finalize();

	KeyManager_Finalize();

	//UninitSound();
}

