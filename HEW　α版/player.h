//=============================================================================
//
// プレイヤーの処理 [player.h]
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "field.h"



//*************************************
// プレイヤーの構造体
//*************************************
typedef struct
{
	float fPosX;		// 現在の位置(Ｘ座標)
	float fPosY;		// 現在の位置(Ｙ座標)
	float fPosXOld;		// 前回の位置(Ｘ座標)
	float fPosYOld;		// 前回の位置(Ｙ座標)
	float fMoveX;		// 移動量(Ｘ方向)
	float fMoveY;		// 移動量(Ｙ方向)
	int count;
	bool bJump;			// ジャンプ中かどうか
	bool bGravity;
	bool bLand;// 着地中かどうか
	bool bMove;			// 移動したかどうか(描画更新用)
	bool bShot;			// ショット中かどうか
	float fDirect;		// 向き
	FIELD *pField;		// 地面へのポインタ
	FIELD2 *pField2;
} PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void TermPlayer(void);
void UpdatePlayer(int *falg);
void DrawPlayer(int *flag);

#endif