
#include "texture.h"
#include "sprite.h"
#include "game.h"
#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"

#if defined(_DEBUG) || defined(DEBUG)

typedef struct DebugVertex_tag {

	D3DXVECTOR4 position;
	D3DCOLOR color;

}DebugVertex;

#define FVF_DEBUG_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)


#define CIRCLE_VERTEX_COUNT (128)
#define CIRCLE_DRAW_MAX (2048)


static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

static int g_CircleCount = 0;
static DebugVertex* g_pDebugVertex = NULL;
static WORD* g_pDebugVertexIndex = NULL;

#endif

void DebugPrimitive_Initialize() {

#if defined(_DEBUG) || defined(DEBUG)

	//�e�O���[�o���ϐ��̏�����
	g_CircleCount = 0;
	g_pDebugVertex = NULL;
	g_pDebugVertexIndex = NULL;

	LPDIRECT3DDEVICE9 pDevice = MYDirect3D_GetDevice();

	pDevice->CreateVertexBuffer(
		sizeof(DebugVertex) * CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_DEBUG_VERTEX,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	pDevice->CreateIndexBuffer(
		sizeof(DebugVertex) * CIRCLE_VERTEX_COUNT * 2 * CIRCLE_DRAW_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);
#endif
}


void DebugPrimitive_Finalize() {

#if defined(_DEBUG) || defined(DEBUG)

	if (g_pIndexBuffer) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

#endif

}

void DebugPrimitive_BatchBegin() {

#if defined(_DEBUG) || defined(DEBUG)

	//���_�o�b�t�@�ƒ��_�C���f�b�N�X�o�b�t�@�����b�N����
	g_pVertexBuffer->Lock(0,0,(void**)&g_pDebugVertex,0);
	g_pIndexBuffer->Lock(0, 0, (void**)&g_pDebugVertexIndex, 0);


	//�ۂ̕`�施�ߐ���������
	g_CircleCount = 0;

#endif

}

void DebugPrimitive_BatchDrawCircle(float x, float y, float radius) {

#if defined(_DEBUG) || defined(DEBUG)
	//�w����W���~�̒��S�Ƃ����y�̒��_���W���v�Z���āA
	//���_�o�b�t�@�ƒ��_�C���f�b�N�X�o�b�t�@�ɏ�������


	//�z��̂ǂ����珑������邩
	int n = CIRCLE_VERTEX_COUNT * g_CircleCount;

	//�}�`�̊p����̊p�x(���W�A���p)
	float s = D3DX_PI * 2.0 / CIRCLE_VERTEX_COUNT;

	//���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�֏�����������
	for (int i = 0; i < CIRCLE_VERTEX_COUNT; i++) {
		g_pDebugVertex[n + i].position.x = cosf(s * i) * radius + x;
		g_pDebugVertex[n + i].position.y = sinf(s * i) * radius + y;
		g_pDebugVertex[n + i].position.z = 1.0f;
		g_pDebugVertex[n + i].position.w = 1.0f;
		g_pDebugVertex[n + i].color = D3DCOLOR_RGBA(0,0,192,255);
		
		g_pDebugVertexIndex[n * 2 + i * 2] = n + i;
		g_pDebugVertexIndex[n * 2 + i * 2 + 1] = n + (i + 1) % CIRCLE_VERTEX_COUNT;

	}

	//�ۂ̕`�施�ߐ����ꑝ�₷
	g_CircleCount++;

#endif

}

void DebugPrimitive_BatchRun() {

#if defined(_DEBUG) || defined(DEBUG)

	//���_�o�b�t�@�ƒ��_�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pVertexBuffer->Unlock();
	g_pIndexBuffer->Release();

	//�ۂ̕`�施�ߐ����̊ۂ�����
	LPDIRECT3DDEVICE9 pDevice = MYDirect3D_GetDevice();

	int vn = g_CircleCount * CIRCLE_VERTEX_COUNT;

	pDevice->SetFVF(FVF_DEBUG_VERTEX);
	pDevice->SetStreamSource(0,g_pVertexBuffer,0,sizeof(DebugVertex));
	pDevice->SetTexture(0,NULL);
	pDevice->DrawIndexedPrimitive(D3DPT_LINELIST,0,0,vn,0,vn);

#endif

}