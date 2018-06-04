//=============================================================================
//
// 地面の処理 [field.h]
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_FIELD		(40)		// 地面の最大数

//*************************************
// 地面の構造体
//*************************************
typedef struct
{
	float fPosX;		// 地面の基準位置(Ｘ座標)
	float fPosY;		// 地面の基準位置(Ｙ座標)
	float fPosXOld;		// 地面の前回の位置(Ｘ座標)
	float fPosYOld;		// 地面の前回の位置(Ｙ座標)
	float fWidth;		// 地面の幅
	float fMoveX;		// 地面の移動量(Ｘ方向)
	float fMoveY;		// 地面の移動量(Ｙ方向)
	int nCount;			// カウンター
	bool bMove;			// 地面が移動しているかどうか
	bool bUse;			// 地面を使用しているかどうか
} FIELD;

typedef struct
{
	float fPosX;		// 地面の基準位置(Ｘ座標)
	float fPosY;		// 地面の基準位置(Ｙ座標)
	float fPosXOld;		// 地面の前回の位置(Ｘ座標)
	float fPosYOld;		// 地面の前回の位置(Ｙ座標)
	float fWidth;		// 地面の幅
	float fMoveX;		// 地面の移動量(Ｘ方向)
	float fMoveY;		// 地面の移動量(Ｙ方向)
	int nCount;			// カウンター
	bool bMove;			// 地面が移動しているかどうか
	bool bUse;			// 地面を使用しているかどうか
} FIELD2;

typedef struct
{
	float fPosX;		// 地面の基準位置(Ｘ座標)
	float fPosY;		// 地面の基準位置(Ｙ座標)
	float fPosXOld;		// 地面の前回の位置(Ｘ座標)
	float fPosYOld;		// 地面の前回の位置(Ｙ座標)
	float fWidth;		// 地面の幅
	float fMoveX;		// 地面の移動量(Ｘ方向)
	float fMoveY;		// 地面の移動量(Ｙ方向)
	int nCount;			// カウンター
	bool bMove;			// 地面が移動しているかどうか
	bool bUse;			// 地面を使用しているかどうか
} FIELD3;

typedef struct
{
	float fPosX;		// 地面の基準位置(Ｘ座標)
	float fPosY;		// 地面の基準位置(Ｙ座標)
	float fPosXOld;		// 地面の前回の位置(Ｘ座標)
	float fPosYOld;		// 地面の前回の位置(Ｙ座標)
	float fWidth;		// 地面の幅
	float fMoveX;		// 地面の移動量(Ｘ方向)
	float fMoveY;		// 地面の移動量(Ｙ方向)
	int nCount;			// カウンター
	bool bMove;			// 地面が移動しているかどうか
	bool bUse;			// 地面を使用しているかどうか
} FIELD4;

typedef struct
{
	float fPosX;		// 地面の基準位置(Ｘ座標)
	float fPosY;		// 地面の基準位置(Ｙ座標)
	float fPosXOld;		// 地面の前回の位置(Ｘ座標)
	float fPosYOld;		// 地面の前回の位置(Ｙ座標)
	float fWidth;		// 地面の幅
	float fMoveX;		// 地面の移動量(Ｘ方向)
	float fMoveY;		// 地面の移動量(Ｙ方向)
	int nCount;			// カウンター
	bool bMove;			// 地面が移動しているかどうか
	bool bUse;			// 地面を使用しているかどうか
} FIELD5;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitField(void);
void TermField(void);
void UpdateField(void);
void DrawField(void);
void InitField2(void);
void TermField2(void);
void UpdateField2(void);
void DrawField2(void);
void InitField3(void);
void TermField3(void);
void UpdateField3(void);
void DrawField3(void);
void InitField4(void);
void TermField4(void);
void UpdateField4(void);
void DrawField4(void);
void InitField5(void);
void TermField5(void);
void UpdateField5(void);
void DrawField5(void);

void SetField(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD *GetField(void);

void SetField2(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD2 *GetField2(void);

void SetField3(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD3 *GetField3(void);

void SetField4(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD4 *GetField4(void);

void SetField5(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD5 *GetField5(void);

#endif

