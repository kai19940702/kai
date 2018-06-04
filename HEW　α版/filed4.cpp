//=============================================================================
//
// 地面の処理4 [field4.cpp]
//
//=============================================================================
#include "main.h"
#include "field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
FIELD4 g_aField4[MAX_FIELD];			// 地面の情報
extern int stage;
//=============================================================================
// 地面の初期化処理
//=============================================================================
void InitField4(void)
{

	// 地面の情報初期化
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField4[nCntField].fPosX = 0.0f;
		g_aField4[nCntField].fPosY = 0.0f;
		g_aField4[nCntField].fPosXOld = 0.0f;
		g_aField4[nCntField].fPosYOld = 0.0f;
		g_aField4[nCntField].fWidth = 0.0f;
		g_aField4[nCntField].fMoveX = 0.0f;
		g_aField4[nCntField].fMoveY = 0.0f;
		g_aField4[nCntField].bMove = false;
		g_aField4[nCntField].bUse = false;
	}

	if(stage==1)
	{
	// 地面の設定(今だけ)
	SetField4(18.0f, 23.0f, 26.0f, 0.0f, 0.0f);
	}
	else
	{
	SetField4(63.0f, 23.0f, 2.0f, 0.0f, 0.0f);
	SetField4(34.0f, 11.0f, 2.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// 地面の終了処理
//=============================================================================
void TermField4(void)
{
}

//=============================================================================
// 地面の更新処理
//=============================================================================
void UpdateField4(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField4[nCntField].bUse == true)
		{
			if(g_aField4[nCntField].bMove == true)
			{
				// 前回の位置を保存
				g_aField4[nCntField].fPosXOld = g_aField4[nCntField].fPosX;
				g_aField4[nCntField].fPosYOld = g_aField4[nCntField].fPosY;

				// 位置を更新
				g_aField4[nCntField].fPosX += g_aField4[nCntField].fMoveX;
				g_aField4[nCntField].fPosY += g_aField4[nCntField].fMoveY;

				g_aField4[nCntField].nCount++;
				if(g_aField4[nCntField].nCount >= 100)
				{// 一定時間経過
					g_aField4[nCntField].fMoveX *= -1.0f;
					g_aField4[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// 地面の描画処理
//=============================================================================
void DrawField4(void)
{
	// 色の設定
	COLOR(CORAL);

	// 地面の表示
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField4[nCntField].bUse == true)
		{
#if 0	// このままだと重い…
			LOCATE((int)g_aField[nCntField].fPosX, (int)g_aField[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField[nCntField].fWidth / 2; nCntBlock++)
			{
				printf("□");
			}
#else	// こうすると軽くなる…
			char aBuf[80];

			strcpy(&aBuf[0], "\0");
			LOCATE((int)g_aField4[nCntField].fPosX, (int)g_aField4[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField4[nCntField].fWidth / 2; nCntBlock++)
			{
				strcat(&aBuf[0], "▲");
			}
			printf("%s", &aBuf[0]);
#endif
		}
	}

}

//=============================================================================
// 地面の設定
//=============================================================================
void SetField4(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField4[nCntField].bUse == false)
		{
			g_aField4[nCntField].fPosX =
			g_aField4[nCntField].fPosXOld = fPosX;
			g_aField4[nCntField].fPosY =
			g_aField4[nCntField].fPosYOld = fPosY;
			g_aField4[nCntField].fWidth = fWidth;
			g_aField4[nCntField].fMoveX = fMoveX;
			g_aField4[nCntField].fMoveY = fMoveY;
			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField4[nCntField].bMove = false;
			}
			else
			{
				g_aField4[nCntField].bMove = true;
			}
			g_aField4[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 地面の取得
//=============================================================================
FIELD4 *GetField4(void)
{
	return &g_aField4[0];
}