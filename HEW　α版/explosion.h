//=============================================================================
//
// 爆発の処理 [explosion.h]
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*************************************
// 弾の種類
//*************************************
typedef enum
{
	EXPLOSIONTYPE_PLAYER = 0,		// プレイヤーの弾の爆発
	EXPLOSIONTYPE_ENEMY,			// 敵の弾の爆発
	EXPLOSIONTYPE_MAX
} EXPLOSIONTYPE;

//*************************************
// 弾の構造体
//*************************************
typedef struct
{
	float fPosX;		// 現在の位置(Ｘ座標)
	float fPosY;		// 現在の位置(Ｙ座標)
	int nCounter;		// カウンター
	EXPLOSIONTYPE type;	// 爆発の種類
	bool bUse;			// 使用中かどうか
	float *player_x;
	float *player_y;
	float muki;
	bool gravity;
	float Shot_x;
	float Shot_y;
} EXPLOSION;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void TermExplosion(void);
void UpdateExplosion(int *flag);
void UpdateExplosion2(int *flag);
void DrawExplosion(void);

void SetExplosion(float fPosX, float fPosY, EXPLOSIONTYPE type, float *X,
	float *Y,float muki,bool gravity,float shot_x,float shot_y);


#endif