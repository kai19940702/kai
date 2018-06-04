//=============================================================================
//
// 地面の処理 [field.cpp]
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
FIELD g_aField[MAX_FIELD];			// 地面の情報
extern int stage;
//=============================================================================
// 地面の初期化処理
//=============================================================================
void InitField(void)
{

	// 地面の情報初期化
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField[nCntField].fPosX = 0.0f;
		g_aField[nCntField].fPosY = 0.0f;
		g_aField[nCntField].fPosXOld = 0.0f;
		g_aField[nCntField].fPosYOld = 0.0f;
		g_aField[nCntField].fWidth = 0.0f;
		g_aField[nCntField].fMoveX = 0.0f;
		g_aField[nCntField].fMoveY = 0.0f;
		g_aField[nCntField].bMove = false;
		g_aField[nCntField].bUse = false;
	}

	if(stage==1)
	{
		// 地面の設定(今だけ)
		SetField(2.0f, 2.0f, 78.0f, 0.0f, 0.0f);
		SetField(10.0f, 5.0f, 60.0f, 0.0f, 0.0f);
		SetField(2.0f, 24.0f, 78.0f, 0.0f, 0.0f);
		SetField(44.0f, 24.0f, 38.0f, 0.0f, 0.0f);
		SetField(68.0f, 8.0f, 12.0f, 0.0f, 0.0f);
		SetField(15.0f, 10.0f, 18.0f, 0.0f, 0.0f);
		SetField(36.0f, 15.0f, 18.0f, 0.0f, 0.0f);
		SetField(19.0f, 20.0f, 18.0f, 0.0f, 0.0f);
		SetField(19.0f, 19.0f, 2.0f, 0.0f, 0.0f);
		SetField(19.0f, 18.0f, 2.0f, 0.0f, 0.0f);
		SetField(19.0f, 17.0f, 2.0f, 0.0f, 0.0f);
		SetField(19.0f, 16.0f, 2.0f, 0.0f, 0.0f);
		SetField(72.0f, 19.0f, 8.0f, 0.0f, 0.0f); 
		SetField(16.0f, 23.0f, 2.0f, 0.0f, 0.0f);
		SetField(44.0f, 23.0f, 2.0f, 0.0f, 0.0f);
		SetField(68.0f, 9.0f, 2.0f, 0.0f, 0.0f);
		SetField(68.0f, 10.0f, 2.0f, 0.0f, 0.0f);
		SetField(70.0f, 19.0f, 2.0f, 0.0f, 0.0f);
		SetField(70.0f, 18.0f, 2.0f, 0.0f, 0.0f);
		SetField(70.0f, 17.0f, 2.0f, 0.0f, 0.0f);
	}

	if(stage==2)
	{
		SetField(2.0f, 10.0f, 16.0f, 0.0f, 0.0f);
		SetField(32.0f, 10.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 9.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 8.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 7.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 6.0f, 10.0f, 0.0f, 0.0f);
		SetField(48.0f, 2.0f, 17.0f, 0.0f, 0.0f);	
		SetField(2.0f, 2.0f, 22.0f, 0.0f, 0.0f);
		SetField(26.0f, 2.0f, 20.0f, 0.0f, 0.0f);
		SetField(65.0f, 16.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 17.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 18.0f, 2.0f, 0.0f, 0.0f); 
		SetField(65.0f, 19.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 20.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 21.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 22.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 23.0f, 2.0f, 0.0f, 0.0f);
		SetField(2.0f, 24.0f, 78.0f, 0.0f, 0.0f);
		SetField(2.0f, 17.0f, 48.0f, 0.0f, 0.0f); 
		SetField(34.0f, 12.0f, 16.0f, 0.0f, 0.0f); 
		SetField(34.0f, 12.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 13.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 14.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 15.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 16.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 17.0f, 2.0f, 0.0f, 0.0f); 
		SetField(72.0f, 19.0f, 8.0f, 0.0f, 0.0f); 
	}

	
}

//=============================================================================
// 地面の終了処理
//=============================================================================
void TermField(void)
{
}

//=============================================================================
// 地面の更新処理
//=============================================================================
void UpdateField(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField[nCntField].bUse == true)
		{
			if(g_aField[nCntField].bMove == true)
			{
				// 前回の位置を保存
				g_aField[nCntField].fPosXOld = g_aField[nCntField].fPosX;
				g_aField[nCntField].fPosYOld = g_aField[nCntField].fPosY;

				// 位置を更新
				g_aField[nCntField].fPosX += g_aField[nCntField].fMoveX;
				g_aField[nCntField].fPosY += g_aField[nCntField].fMoveY;

				g_aField[nCntField].nCount++;
				if(g_aField[nCntField].nCount >= 100)
				{// 一定時間経過
					g_aField[nCntField].fMoveX *= -1.0f;
					g_aField[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// 地面の描画処理
//=============================================================================
void DrawField(void)
{
	// 色の設定
	COLOR(WHITE);

	// 地面の表示
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField[nCntField].bUse == true)
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
			LOCATE((int)g_aField[nCntField].fPosX, (int)g_aField[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField[nCntField].fWidth / 2; nCntBlock++)
			{
				strcat(&aBuf[0], "■");
			}
			printf("%s", &aBuf[0]);
#endif
		}
	}

}

//=============================================================================
// 地面の設定
//=============================================================================
void SetField(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField[nCntField].bUse == false)
		{
			g_aField[nCntField].fPosX =
			g_aField[nCntField].fPosXOld = fPosX;
			g_aField[nCntField].fPosY =
			g_aField[nCntField].fPosYOld = fPosY;
			g_aField[nCntField].fWidth = fWidth;
			g_aField[nCntField].fMoveX = fMoveX;
			g_aField[nCntField].fMoveY = fMoveY;
			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField[nCntField].bMove = false;
			}
			else
			{
				g_aField[nCntField].bMove = true;
			}
			g_aField[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 地面の取得
//=============================================================================
FIELD *GetField(void)
{
	return &g_aField[0];
}
