//=============================================================================
//
// サウンド処理 [sound.h]
// Author : KAI YAMAMURO
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDPARAM;

//*****************************************************************************
// サウンドファイル
//*****************************************************************************

// 各音素材のパラメータ
static const SOUNDPARAM g_aParam[] =
{
	{"music\\futta-fly.wav",  -1},		// BGM0
	{"music\\kettei.wav",  0},
	{"music\\bomb2.wav",  0},
	{"music\\dog.wav",  0},
	{"music\\READY.WAV",  0},
	{"music\\START.WAV",  0},
	{"music\\bgm.wav",  -1},
	{"music\\loading.wav",  -1},
	{"music\\result.wav",  -1},
	{"music\\dead.wav",  0},
	{"music\\ora.wav",  0},
	{"music\\senntaku.wav",  0},
	{"music\\levelup.wav",  0},
	{"music\\beamgun1.wav",  0},
	{"music\\shot1.wav",  0},
};



typedef enum
{
	SOUND_LABEL_BGM = 0,		// BGM0
	SOUND_LABEL_KETTEI,
	SOUND_LABEL_EXPLOSION,
	SOUND_LABEL_DOG,
	SOUND_LABEL_READY,
	SOUND_LABEL_START,
	SOUND_LABEL_BGM000,
	SOUND_LABEL_LOADING,
	SOUND_LABEL_RESULT,
	SOUND_LABEL_DEAD,
	SOUND_LABEL_ORA,
	SOUND_LABEL_SENNTAKU,
	SOUND_LABEL_LEVELUP,
	SOUND_LABEL_BEAM,
	SOUND_LABEL_SHOT,
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
