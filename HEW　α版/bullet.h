//=============================================================================
//
// 弾の処理 [bullet.h]
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*************************************
// 弾の種類
//*************************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,		// プレイヤーの弾
	BULLETTYPE_ENEMY,			// 敵の弾
	BULLETTYPE_MAX
} BULLETTYPE;

//*************************************
// 弾の構造体
//*************************************
typedef struct
{
	float fPosX;		// 現在の位置(Ｘ座標)
	float fPosY;		// 現在の位置(Ｙ座標)
	float fPosXOld;		// 前回の位置(Ｘ座標)
	float fPosYOld;		// 前回の位置(Ｙ座標)
	float fMoveX;		// 移動量(Ｘ方向)
	float fMoveY;		// 移動量(Ｙ方向)
	bool bUse;			// 使用中かどうか
	bool gravity;
	float *player_x;
	float *player_y;
	float muki;
	float Shot_x;
	float Shot_y;

} BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void TermBullet(void);
void UpdateBullet(int *flag);
void DrawBullet(void);

void SetBullet(float fPosX, float fPosY, float fMoveX, float fMoveY,
	  bool Gravity,float *X,float *Y,float muki,float shot_x,float shot_y);

#endif