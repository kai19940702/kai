//=============================================================================
//
// 地面の処理5 [field5.cpp]
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
FIELD5 g_aField5[MAX_FIELD];			// 地面の情報
extern bool button;
extern int stage;

//=============================================================================
// 地面の初期化処理
//=============================================================================
void InitField5(void)
{

	// 地面の情報初期化
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField5[nCntField].fPosX = 0.0f;
		g_aField5[nCntField].fPosY = 0.0f;
		g_aField5[nCntField].fPosXOld = 0.0f;
		g_aField5[nCntField].fPosYOld = 0.0f;
		g_aField5[nCntField].fWidth = 0.0f;
		g_aField5[nCntField].fMoveX = 0.0f;
		g_aField5[nCntField].fMoveY = 0.0f;
		g_aField5[nCntField].bMove = false;
		g_aField5[nCntField].bUse = false;
	}

	if(stage==1)
	{
	// 地面の設定(今だけ)
	SetField5(72.0f, 18.0f, 8.0f, 0.0f, 0.0f);
	}
	else
	{
	SetField5(36.0f, 16.0f, 14.0f, 0.0f, 0.0f);
	SetField5(3.0f, 3.0f, 14.0f, 0.0f, 0.0f);
	}


}

//=============================================================================
// 地面の終了処理
//=============================================================================
void TermField5(void)
{
}

//=============================================================================
// 地面の更新処理
//=============================================================================
void UpdateField5(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField5[nCntField].bUse == true)
		{
			if(g_aField5[nCntField].bMove == true)
			{
				// 前回の位置を保存
				g_aField5[nCntField].fPosXOld = g_aField5[nCntField].fPosX;
				g_aField5[nCntField].fPosYOld = g_aField5[nCntField].fPosY;

				// 位置を更新
				g_aField5[nCntField].fPosX += g_aField5[nCntField].fMoveX;
				g_aField5[nCntField].fPosY += g_aField5[nCntField].fMoveY;

				g_aField5[nCntField].nCount++;
				if(g_aField5[nCntField].nCount >= 100)
				{// 一定時間経過
					g_aField5[nCntField].fMoveX *= -1.0f;
					g_aField5[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// 地面の描画処理
//=============================================================================
void DrawField5(void)
{
	// 色の設定
	COLOR(YELLOW);

	// 地面の表示
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField5[nCntField].bUse == true)
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
			LOCATE((int)g_aField5[nCntField].fPosX, (int)g_aField5[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField5[nCntField].fWidth / 2; nCntBlock++)
			{
				if(button==true)
				{
				strcat(&aBuf[0], "○");
				}
				else
				{
					strcat(&aBuf[0], "●");
				}
			}
			printf("%s", &aBuf[0]);
#endif
		}
	}

}

//=============================================================================
// 地面の設定
//=============================================================================
void SetField5(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField5[nCntField].bUse == false)
		{
			g_aField5[nCntField].fPosX =
			g_aField5[nCntField].fPosXOld = fPosX;
			g_aField5[nCntField].fPosY =
			g_aField5[nCntField].fPosYOld = fPosY;
			g_aField5[nCntField].fWidth = fWidth;
			g_aField5[nCntField].fMoveX = fMoveX;
			g_aField5[nCntField].fMoveY = fMoveY;
			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField5[nCntField].bMove = false;
			}
			else
			{
				g_aField5[nCntField].bMove = true;
			}
			g_aField5[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 地面の取得
//=============================================================================
FIELD5 *GetField5(void)
{
	return &g_aField5[0];
}