#include "mydirect3d.h"
#include "game.h"
#include "texture.h"
#include <d3dx9.h>
#include <d3d9.h>

//�O���[�o���ϐ�
static LPDIRECT3DTEXTURE9 g_pTexture3[6] = { NULL,NULL,NULL,NULL,NULL,NULL };//�e�N�X�`���C���^�[�t�F�[�X �e�N�X�`���P�ɂ��P�K�v
static float f = 0.0f;

static float move_x = 0.0f;
bool turn = false;

// FVF ...�@�t���L�V�u���o�[�e�b�N�X�t�H�[�}�b�g
// ���W�ϊ��ςݒ��_ RHW = 1

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;//���_�o�b�t�@�C���^�[�t�F�[�X
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;//�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X
static D3DCOLOR g_Color = 0xffffffff;

texture Texture(true);

void sprite:: Sprite_Initialize(void) {

	LPDIRECT3DDEVICE9 pDevice = MYDirect3D_GetDevice();
	if (!pDevice) {

		return;
	}

	//���_�o�b�t�@�o�C�g��,�g����,FVF,�������̊Ǘ����@,�擾�����C���^�[�t�F�[�X�̃A�h���X���L�^����|�C���^,��
	pDevice->CreateVertexBuffer(sizeof(Vertex2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX2D,D3DPOOL_MANAGED,&g_pVertexBuffer,NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD)*6,D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

}

void sprite::Sprite_Finalize(void) {

	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pIndexBuffer) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

//�X�v���C�g�|���S���J���[�ݒ�
void sprite::Sprite_SetColor(D3DCOLOR color) {

	g_Color = color;
}

void sprite::Sprite_SetColor(int r, int g, int b, int a) {

	g_Color = (a << 24) + (r << 16) + (g << 8) + (b);
}

//�J���[������
void sprite::Sprite_SetColorDefault() {

	g_Color = 0xffffffff;
}



void sprite::Sprite_Draw_test3(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch) {

	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX2D);

	g_pDevice->SetTexture(0, Texture.Texture_GetTexture(textureId));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture.Texture_GetTextureWidth(textureId);
	int h = Texture.Texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	Vertex2D v[] = {
		{D3DXVECTOR4(dx - 0.5f		,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + dw	,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f		,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx - 0.5f + dw	,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u1,v1)},
	};



	//���_�o�b�t�@�̃��b�N�ƃf�[�^�̏�������
	Vertex2D* pV;	
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);//�������݂̊m��

	memcpy(pV, v, sizeof(v));

	g_pVertexBuffer->Unlock();//�������݂̏I��


	//�C���f�b�N�X�o�b�t�@�̃��b�N�Ə�������
	WORD* pI;

	g_pIndexBuffer->Lock(0,0,(void**)&pI,0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 3;
	pI[3] = 0;
	pI[4] = 3;
	pI[5] = 2;
	g_pIndexBuffer->Unlock();

	//�f�o�C�X�̒��_�o�b�t�@��ݒ�
	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	//�f�o�C�X�ɃC���f�b�N�X�o�b�t�@��ݒ�
	g_pDevice->SetIndices(g_pIndexBuffer);
	////���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�𗘗p�����v���~�e�B�u�`��
	//�`�����A�ŏ��C���f�b�N�X,�ŏ��C���f�b�N�X,���_�̐�,�ŏ��̂�A�}�`�̐�
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2);
}


//dx �E�E�E�`����W
//dy �E�E�E�`����W
//dw �E�E�E�|���S���T�C�Y��
//dh �E�E�E�|���S���T�C�Y����
//tcx �E�E�E�`����W
//tcy �E�E�E�`����W
//tcw �E�E�E
//tch �E�E�E
void sprite::Sprite_Draw_test2(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch) {

	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX2D);

	g_pDevice->SetTexture(0, Texture.Texture_GetTexture(textureId));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture.Texture_GetTextureWidth(textureId);
	int h = Texture.Texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	Vertex2D v[] = {
		{D3DXVECTOR4(dx - 0.5f		,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + dw	,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f		,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx - 0.5f + dw	,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u1,v1)},
	};

	//���_�o�b�t�@�̃��b�N�ƃf�[�^�̏�������
	Vertex2D* pV;

	////���ꂪ���
	//���� ���b�N����擪 0�͐擪�A���b�N���钷�� 0�͑S��
	g_pVertexBuffer->Lock(0,0,(void**)&pV,0);//�������݂̊m��

	memcpy(pV,v,sizeof(v));

	g_pVertexBuffer->Unlock();//�������݂̏I��

	//���_�o�b�t�@�̎w��
	g_pDevice->SetStreamSource(0,g_pVertexBuffer,0,sizeof(Vertex2D));
	
	//�v���~�e�B�u�`��
	//���� �`�����@�X�^�[�g�n�_ �����`����
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);

}

void sprite::Sprite_Draw_test(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch) {

	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX2D);

	g_pDevice->SetTexture(0, Texture.Texture_GetTexture(textureId));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture.Texture_GetTextureWidth(textureId);
	int h = Texture.Texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	Vertex2D v[] = {
		{D3DXVECTOR4(dx - 0.5f		,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + dw	,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f		,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx - 0.5f + dw	,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u1,v1)},
	};

	//�C���f�b�N�X�f�[�^
	unsigned short index[] = { 0,1,3,0,3,2 };





	// �ŏ��̃C���f�b�N�X�l,�g�����_�A�}�`�̐�,�C���f�b�N�X�f�[�^�̐擪�A�h���X,�t�H�[�}�b�g,���_�f�[�^,�ׂ̒��_�܂ł̃o�C�g��
	g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));

	//�|���S��������(�ȈՔ�)
	//���� �`��^�C�v�A���A�擪�A�h���X,�ׂ̒��_�܂ŉ��o�C�g
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, v, sizeof(Vertex2D));
}

void sprite::Sprite_Draw(int textureId, float dx, float dy, float dw, float dh) {

	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX2D);

	g_pDevice->SetTexture(0, Texture.Texture_GetTexture(textureId));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture.Texture_GetTextureWidth(textureId);
	int h = Texture.Texture_GetTextureHeight(textureId);

	Vertex2D v[] = {
		{D3DXVECTOR4(dx - 0.5f,dy - 0.5f,1.0f,1.0f)				,g_Color,D3DXVECTOR2(0,0)},
		{D3DXVECTOR4(dx - 0.5f + dw,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(1,0)},
		{D3DXVECTOR4(dx - 0.5f,dy - 0.5f + dh,1.0f,1.0f)		,g_Color,D3DXVECTOR2(0,1)},
		{D3DXVECTOR4(dx - 0.5f + dw,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(1,1)},
	};
	//�|���S��������(�ȈՔ�)
	//���� �`��^�C�v�A���A�擪�A�h���X,�ׂ̒��_�܂ŉ��o�C�g
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}

void sprite::Sprite_Draw(int textureId, float dx, float dy,float dw,float dh,int tcx,int tcy,int tcw, int tch) {

	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX2D);

	g_pDevice->SetTexture(0, Texture.Texture_GetTexture(textureId));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture.Texture_GetTextureWidth(textureId);
	int h = Texture.Texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	Vertex2D v[] = {
		{D3DXVECTOR4(dx - 0.5f,dy - 0.5f,1.0f,1.0f)				,g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + dw,dy - 0.5f,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f,dy - 0.5f + dh,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx - 0.5f + dw,dy - 0.5f + dh,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u1,v1)},
	};
	//�|���S��������(�ȈՔ�)
	//���� �`��^�C�v�A���A�擪�A�h���X,�ׂ̒��_�܂ŉ��o�C�g
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}

//cx.cy ��]�g��̒��S���W
//angle �|���S���̉�]�p�x

void sprite::Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, float cx, float cy, float angle) {

	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX2D);

	g_pDevice->SetTexture(0, Texture.Texture_GetTexture(textureId));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture.Texture_GetTextureWidth(textureId);
	int h = Texture.Texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	Vertex2D v[] = {
		{D3DXVECTOR4(	- 0.5f,		 - 0.5f		,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(	- 0.5f + dw, - 0.5f		,1.0f,1.0f)		,g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(	- 0.5f,		 - 0.5f + dh	,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(	- 0.5f + dw, - 0.5f + dh	,1.0f,1.0f)	,g_Color,D3DXVECTOR2(u1,v1)},
	};

	//���s�ړ��s��
	D3DXMATRIX mtxTranslationC;//���ɖ߂�
	D3DXMatrixTranslation(&mtxTranslationC,-cx,-cy,0.0f);
	
	D3DXMATRIX mtxTranslationI;//�ړ�������
	D3DXMatrixTranslation(&mtxTranslationI, cx + dx, cy + dx, 0.0f);


	//��]�s��
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation,angle);

	//�g��s��
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale,1.0f,1.0f,1.0f);

	////�g�債�ĉ�]���ĕ��s�ړ�
	//�s��̍���
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation * mtxTranslationI;


	
	//���W�ϊ�
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].Position,&v[i].Position,&mtxWorld);
	}


	//�|���S��������(�ȈՔ�)
	//���� �`��^�C�v�A���A�擪�A�h���X,�ׂ̒��_�܂ŉ��o�C�g
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}

void sprite::Sprite_Draw_Turn(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, float cx, float cy, float angle) {

	LPDIRECT3DDEVICE9 g_pDevice = MYDirect3D_GetDevice();

	g_pDevice->SetFVF(FVF_VERTEX2D);

	g_pDevice->SetTexture(0, Texture.Texture_GetTexture(textureId));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture.Texture_GetTextureWidth(textureId);
	int h = Texture.Texture_GetTextureHeight(textureId);

	//�e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	Vertex2D v[] = {
		{D3DXVECTOR4(-0.5f,		 -0.5f		,1.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(-0.5f + dw, -0.5f		,1.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(-0.5f,		 -0.5f + dh	,1.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1)},
		{D3DXVECTOR4(-0.5f + dw, -0.5f + dh	,1.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1)},
	};

	//���s�ړ��s��
	D3DXMATRIX mtxTranslationC;//���ɖ߂�
	D3DXMatrixTranslation(&mtxTranslationC, -cx, -cy, 0.0f);

	D3DXMATRIX mtxTranslationI;//�ړ�������
	D3DXMatrixTranslation(&mtxTranslationI, cx + dx, cy + dy, 0.0f);


	//��]�s��
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	//�g��s��
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);

	////�g�債�ĉ�]���ĕ��s�ړ�
	//�s��̍���
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation * mtxTranslationI;



	//���W�ϊ�
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}


	//�|���S��������(�ȈՔ�)
	//���� �`��^�C�v�A���A�擪�A�h���X,�ׂ̒��_�܂ŉ��o�C�g
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}