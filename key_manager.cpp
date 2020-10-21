#include "key_manager.h"
#include "keyboard.h"


//�L�[�̐��ɍ��킹�Č^�ݒ�
static unsigned char g_CurrentData = 0;
static unsigned char g_PrevData = 0;
static unsigned char g_TriggerData = 0;
static unsigned char g_ReleaseData = 0;

static int g_KeyManagerMode = 0;
static unsigned char* g_pRecordCurrentData = NULL;//�^���L�[�Ǘ��ƍ��킹��
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;

//�L�[�{�[�h�Ƃ̕ϊ��\
static Keyboard_Keys g_KKs[KM_MAX]{
	KK_UP,
	KK_DOWN,
	KK_LEFT,
	KK_RIGHT,
	KK_Z,
	KK_X,
	KK_C

};



void KeyManager_Initilalize() {

	g_CurrentData = g_PrevData = 0;
	g_TriggerData = 0;
	g_ReleaseData = 0;
	g_KeyManagerMode = 0;
	g_pRecordCurrentData = NULL;
	g_RecordPlayFrame = 0;
	g_RecordFrame = 0;
}

void KeyManager_Finalize() {

	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}

}

void KeyManager_Update() {

	g_PrevData = g_CurrentData;
	
	if (g_KeyManagerMode <= 1) {

		g_CurrentData = 0;

		for (int i = 0; i < KM_MAX; i++) {

			//�����ꂽ�ӏ��ɑΉ�����r�b�g�𗧂Ă�
			if (Keyboard_IsKeyDown(g_KKs[i])) {
				g_CurrentData |= 1u << i;

			}
		}

		if (g_KeyManagerMode == 1) {
			if (g_RecordPlayFrame >= g_RecordFrame) g_RecordPlayFrame = g_RecordFrame;
			g_pRecordCurrentData[g_RecordPlayFrame++] = g_CurrentData;
		}
	}
	else{
		g_CurrentData = g_pRecordCurrentData[g_RecordPlayFrame++];
		//if (g_RecordPlayFrame >= �}�b�N�X���z������L�^���~�߂ă��[�h���m�[�}���ɂ���)

	}

	g_TriggerData = (g_PrevData ^ g_CurrentData) & g_CurrentData;
	g_ReleaseData = (g_PrevData ^ g_CurrentData) & g_PrevData;

}

//�����Ă���
bool KeyManager_Press(KeyKind KK) {


	return g_CurrentData & (1u << (int)KK);

}
	
//�������u��
bool KeyManager_Trigger(KeyKind KK) {

	return g_TriggerData & (1u << (int)KK);

}

//�������u��
bool KeyManager_Release(KeyKind KK) {

	return g_ReleaseData & (1u << (int)KK);

}

void KeyManager_RecordStart(int frame_max) {

	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
	}

	g_pRecordCurrentData = (unsigned char*)malloc(frame_max);
	g_KeyManagerMode = 1;
	g_RecordFrame = 0;
}

void KeyManager_RecordEnd() {

	FILE* fp = fopen("keyrecord.dat","wb");
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	fwrite(g_pRecordCurrentData, sizeof(unsigned char), g_RecordFrame, fp);
	fclose(fp);

	g_KeyManagerMode = 0;

}

void KeyManager_RecordLoad() {

	FILE* fp = fopen("keyrecord.dat", "rb");
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	g_pRecordCurrentData = (unsigned char*)malloc(g_RecordFrame);
	fread(g_pRecordCurrentData, sizeof(unsigned char), g_RecordFrame, fp);
	fclose(fp);

}

void KeyManager_RecordPlay() {

	g_RecordFrame = 0;
	g_KeyManagerMode = 2;

}

bool KeyManager_IsRecordPlay() {

	if (g_KeyManagerMode == 2) {

		return true;
	}

	return false;
}
