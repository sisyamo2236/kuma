
#include "texture.h"
#include <d3dx9.h>
#include <string.h>
#include <stdio.h>
#include "mydirect3d.h"

////�\���̐錾
//�e�N�X�`���Ǘ��e�[�u���\����
typedef struct Texture_tag
{
	LPDIRECT3DTEXTURE9 pTexture;
	unsigned long width;
	unsigned long height;
	char filename[TEXTURE_FILENAME_MAX];

}Texture;

////�O���[�o���ϐ��錾
//�e�N�X�`���Ǘ��e�[�u��
static Texture g_Textures[TEXTURE_MAX];


//�e�N�X�`���Ǘ����W���[���̏�����
/*void Texture_Initialize() {

	for (int i = 0; i < TEXTURE_MAX; i++) {
		g_Textures[i].pTexture = NULL;
		g_Textures[i].width = 0;
		g_Textures[i].height = 0;
		g_Textures[i].filename[0] = 0;//'\0'�Ɠ��`

	}

}*/

texture::texture(bool init) {

	if (init) {
		for (int i = 0; i < TEXTURE_MAX; i++) {
			g_Textures[i].pTexture = NULL;
			g_Textures[i].width = 0;
			g_Textures[i].height = 0;
			g_Textures[i].filename[0] = 0;//'\0'�Ɠ��`

		}
	}
}

texture::texture() {

	static int init = Texture_Initialize();

}

texture::~texture() {



}

int texture::Texture_Initialize() {

	for (int i = 0; i < TEXTURE_MAX; i++) {
		g_Textures[i].pTexture = NULL;
		g_Textures[i].width = 0;
		g_Textures[i].height = 0;
		g_Textures[i].filename[0] = 0;//'\0'�Ɠ��`

	}

	return 0;
}

////�e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
//����:�t�@�C����
//�߂�l:�e�N�X�`���Ǘ��ԍ� 
//       �ő�Ǘ����𒴂��Ă����ꍇ��-1(INVALID_TEXTURE_ID)
int texture::Texture_SetTextureLoadFile(const char* pFileName) {


	//�t�@�C��������
	for (int i = 0; i < TEXTURE_MAX; i++) {
		////�e�[�u���̋󂫏󋵊m�F
		//�󂢂Ă���X�L�b�v
		if (g_Textures[i].filename[0] == 0) continue;

		//���Ɏw��̃t�@�C�����\�񂳂�Ă��邩
		if (strcmp(pFileName, g_Textures[i].filename) == 0) {
			//�\�񂳂�Ă���
			return i;

		}
	}


	//�V�K�\��
	for (int i = 0; i < TEXTURE_MAX; i++) {
		////�e�[�u���̋󂫏󋵊m�F
		//�g�p���Ȃ�X�L�b�v
		if (g_Textures[i].filename[0] != 0) continue;

		strcpy(g_Textures[i].filename,pFileName);


		char buf[64];
		sprintf(buf, "i = %d", i);
		OutputDebugString(buf);
		sprintf(buf, "name = %s", pFileName);
		OutputDebugString(buf);


		return i;
	}



	return TEXTURE_INVALID_ID;

}
//�e�N�X�`���̓ǂݍ���
//�\�񂳂�Ă���t�@�C����ǂݍ���
//�߂�l:�ǂݍ��߂Ȃ������t�@�C����
int texture::Texture_Load() {

	int err_count = 0;

	//Direct3D�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();
	if (!g_pDevice) return -1;


	for (int i = 0; i < TEXTURE_MAX; i++) {


		if (g_Textures[i].filename[0] == 0) {
			//��̃e�[�u��
			continue;
		}
		if (g_Textures[i].pTexture != NULL) {
			//���łɓǂݍ��܂�Ă���
			continue;
		}


		//�e�N�X�`���̓ǂݍ���
		HRESULT hr = D3DXCreateTextureFromFile(g_pDevice, g_Textures[i].filename, &g_Textures[i].pTexture);
		if (FAILED(hr)) {
			//�e�N�X�`���̓ǂݍ��݂Ɏ��s
			err_count++;
		}
		else {
			//�e�N�X�`���̉𑜓x(���E����)�̒���
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(g_Textures[i].filename,&info);
			g_Textures[i].width = info.Width;
			g_Textures[i].height = info.Height;

		}


		char buf[64];
		sprintf(buf, "i = %d", i);
		OutputDebugString(buf);
		sprintf(buf, "name = %s", g_Textures[i].filename);
		OutputDebugString(buf);


	}



	return err_count;

}
//�e�N�X�`���̕����J��
//����:textureIds[]...���������textureId��������int�^�z��̐擪�A�h���X
//     count       ...�������e�N�X�`���̐�

void texture::Texture_Release(int textureIds[], int count) {

	for (int i = 0; i < count; i++) {
		if (g_Textures[textureIds[i]].pTexture) {
			g_Textures[textureIds[i]].pTexture->Release();
			g_Textures[textureIds[i]].pTexture = NULL;
		}

		g_Textures[textureIds[i]].filename[0] = 0;
		g_Textures[textureIds[i]].width = 0;
		g_Textures[textureIds[i]].height = 0;

	}


}
//�e�N�X�`���̑S�J��
void texture::Texture_AllRelease() {



}
//�e�N�X�`���̕��̎擾
//����:�e�N�X�`���Ǘ��ԍ�
//�߂�l:�e�N�X�`���̕��E����
unsigned long texture::Texture_GetTextureWidth(int textureId) {
	
	return  g_Textures[textureId].width;
}

unsigned long texture::Texture_GetTextureHeight(int textureId) {

	return  g_Textures[textureId].height;
}

//�e�N�X�`���C���^�[�t�F�[�X�|�C���^�̎擾
//����:�e�N�X�`���Ǘ��ԍ�
//�߂�l:�e�N�X�`���C���^�[�t�F�[�X�|�C���^
//       �ǂݍ��߂Ă��Ȃ��܂��͕s���ȊǗ��ԍ��������ꍇNULL
LPDIRECT3DTEXTURE9 texture::Texture_GetTexture(int textureId) {

	return g_Textures[textureId].pTexture;

}