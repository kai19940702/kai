//=============================================================================
//
// 地面の処理2 [field2.cpp]
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
FIELD2 g_aField2[MAX_FIELD];			// 地面の情報
extern int stage;
//=============================================================================
// 地面の初期化処理
//=============================================================================
void InitField2(void)
{
	// 地面の情報初期化
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField2[nCntField].fPosX = 0.0f;
		g_aField2[nCntField].fPosY = 0.0f;
		g_aField2[nCntField].fPosXOld = 0.0f;
		g_aField2[nCntField].fPosYOld = 0.0f;
		g_aField2[nCntField].fWidth = 0.0f;
		g_aField2[nCntField].fMoveX = 0.0f;
		g_aField2[nCntField].fMoveY = 0.0f;
		g_aField2[nCntField].bMove = false;
		g_aField2[nCntField].bUse = false;
	}

	if(stage==1)
	{
		// 地面の設定
		SetField2(10.0f, 6.0f, 4.0f, 0.0f, 0.0f);
		SetField2(15.0f, 11.0f, 18.0f, 0.0f, 0.0f);
		SetField2(36.0f, 16.0f, 18.0f, 0.0f, 0.0f);
		SetField2(68.0f, 6.0f, 2.0f, 0.0f, 0.0f);
		SetField2(68.0f, 7.0f, 2.0f, 0.0f, 0.0f);
	}
	else
	{
		SetField2(24.0f, 2.0f, 2.0f, 0.0f, 0.0f);
		SetField2(46.0f, 2.0f, 2.0f, 0.0f, 0.0f);
		SetField2(64.0f, 2.0f, 16.0f, 0.0f, 0.0f);
		SetField2(19.0f, 3.0f, 4.0f, 0.0f, 0.0f);
	}


}

//=============================================================================
// 地面の終了処理
//=============================================================================
void TermField2(void)
{
}

//=============================================================================
// 地面の更新処理
//=============================================================================
void UpdateField2(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField2[nCntField].bUse == true)
		{
			if(g_aField2[nCntField].bMove == true)
			{
				// 前回の位置を保存
				g_aField2[nCntField].fPosXOld = g_aField2[nCntField].fPosX;
				g_aField2[nCntField].fPosYOld = g_aField2[nCntField].fPosY;

				// 位置を更新
				g_aField2[nCntField].fPosX += g_aField2[nCntField].fMoveX;
				g_aField2[nCntField].fPosY += g_aField2[nCntField].fMoveY;

				g_aField2[nCntField].nCount++;
				if(g_aField2[nCntField].nCount >= 100)
				{// 一定時間経過
					g_aField2[nCntField].fMoveX *= -1.0f;
					g_aField2[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// 地面の描画処理
//=============================================================================
void DrawField2(void)
{
	// 色の設定
	COLOR(CORAL);

	// 地面の表示
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField2[nCntField].bUse == true)
		{
#if 0	// このままだと重い…
			LOCATE((int)g_aField[nCntField].fPosX, (int)g_aField[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField[nCntField].fWidth / 2; nCntBlock++)
			{
				printf("▼");
			}
#else	// こうすると軽くなる…
			char aBuf[80];

			strcpy(&aBuf[0], "\0");
			LOCATE((int)g_aField2[nCntField].fPosX, (int)g_aField2[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField2[nCntField].fWidth / 2; nCntBlock++)
			{
				strcat(&aBuf[0], "▼");
			}
			printf("%s", &aBuf[0]);
#endif
		}
	}
}

//=============================================================================
// 地面の設定
//=============================================================================
void SetField2(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField2[nCntField].bUse == false)
		{
			g_aField2[nCntField].fPosX =
			g_aField2[nCntField].fPosXOld = fPosX;
			g_aField2[nCntField].fPosY =
			g_aField2[nCntField].fPosYOld = fPosY;
			g_aField2[nCntField].fWidth = fWidth;
			g_aField2[nCntField].fMoveX = fMoveX;
			g_aField2[nCntField].fMoveY = fMoveY;

			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField2[nCntField].bMove = false;
			}
			else
			{
				g_aField2[nCntField].bMove = true;
			}
			g_aField2[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 地面の取得
//=============================================================================
FIELD2 *GetField2(void)
{
	return &g_aField2[0];
}
