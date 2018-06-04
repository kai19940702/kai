//=============================================================================
//
// 爆発の処理 [explosion.cpp]
//
//=============================================================================
#include "main.h"
#include "explosion.h"
#include "bullet.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION		(100)		// 爆発の最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
EXPLOSION g_aExplosion[MAX_EXPLOSION];		// 弾の情報
extern bool button;
extern int MP3_shot_fin;
int mp3flag=0;
//=============================================================================
// 爆発の初期化処理
//=============================================================================
void InitExplosion(void)
{
	// 弾の情報初期化
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].fPosX = 0.0f;
		g_aExplosion[nCntExplosion].fPosY = 0.0f;
		g_aExplosion[nCntExplosion].type = EXPLOSIONTYPE_PLAYER;
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].gravity = false;
		g_aExplosion[nCntExplosion].Shot_x=1.0;
		g_aExplosion[nCntExplosion].Shot_y=0.5;
	}
}

//=============================================================================
// 爆発の終了処理
//=============================================================================
void TermExplosion(void)
{
}

//=============================================================================
// 爆発の更新処理
//=============================================================================
void UpdateExplosion(int *flag)
{
	float *X;
	float *Y;
	extern PLAYER g_player;

	if(*flag==1)
	{


	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{

		if(g_aExplosion[nCntExplosion].bUse == true)
		{// 爆発が使用状態
			g_aExplosion[nCntExplosion].nCounter++;
			if(g_aExplosion[nCntExplosion].nCounter > 24)
			{// 爆発終了
				/*

				// 爆発を消去
				LOCATE((int)(g_aExplosion[nCntExplosion].fPosX), (int)(g_aExplosion[nCntExplosion].fPosY));
				printf("　");
				*/
					if(mp3flag==0)
					{
						PLAYMP3(MP3_shot_fin);
						mp3flag=1;
					}
				X=g_aExplosion[nCntExplosion].player_x;
				Y=g_aExplosion[nCntExplosion].player_y;

				*X+=g_aExplosion[nCntExplosion].Shot_x*g_aExplosion[nCntExplosion].muki;
				if(g_aExplosion[nCntExplosion].gravity==false)
				{
					*Y-=g_aExplosion[nCntExplosion].Shot_y;
				}
				else
				{
					*Y+=g_aExplosion[nCntExplosion].Shot_y;
				}


				if((int)*Y==(int)(g_aExplosion[nCntExplosion].fPosY))
				{
				g_aExplosion[nCntExplosion].bUse = false;		// 爆発を未使用状態に
				*flag=0;
				mp3flag=0;
				}
			
				
			




			}
		}
	}
	}
}



void UpdateExplosion2(int *flag)
{
	float *X;
	float *Y;
	float old_x;
	float old_y;

	if(*flag==2)
	{


	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse == true)
		{// 爆発が使用状態
			g_aExplosion[nCntExplosion].nCounter++;
			if(g_aExplosion[nCntExplosion].nCounter > 24)
			{// 爆発終了
				

				// 爆発を消去
				LOCATE((int)(g_aExplosion[nCntExplosion].fPosX), (int)(g_aExplosion[nCntExplosion].fPosY));
				printf("　");
				
				Y=g_aExplosion[nCntExplosion].player_y;
				g_aExplosion[nCntExplosion].fPosX-=g_aExplosion[nCntExplosion].Shot_x*g_aExplosion[nCntExplosion].muki;

				if(g_aExplosion[nCntExplosion].gravity==false)
				{
					g_aExplosion[nCntExplosion].fPosY+=g_aExplosion[nCntExplosion].Shot_y;
				}
				else
				{
					g_aExplosion[nCntExplosion].fPosY-=g_aExplosion[nCntExplosion].Shot_y;
				}

				COLOR(BLUE);
				LOCATE((int)(g_aExplosion[nCntExplosion].fPosX), (int)(g_aExplosion[nCntExplosion].fPosY));
				printf("●");

				if((int)*Y==(int)(g_aExplosion[nCntExplosion].fPosY))
				{
					g_aExplosion[nCntExplosion].bUse = false;		// 爆発を未使用状態に
					*flag=0;
				}




			}
		}
	}
	}
}

//=============================================================================
// 爆発の描画処理
//=============================================================================
void DrawExplosion(void)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse == true)
		{// 爆発が使用状態

			// 色設定
			if(g_aExplosion[nCntExplosion].type == EXPLOSIONTYPE_PLAYER)
			{// プレイヤーの弾
				COLOR(BLUE);
			}
			else
			{// 敵の弾
				COLOR(PINK);
			}

		
			// 現在の位置に爆発を表示
			LOCATE((int)(g_aExplosion[nCntExplosion].fPosX), (int)(g_aExplosion[nCntExplosion].fPosY));
			if(g_aExplosion[nCntExplosion].nCounter < 6)
			{
				printf("●");
			}
		/*
			else if(g_aExplosion[nCntExplosion].nCounter < 12)
			{
				printf("○");
			}
			else if(g_aExplosion[nCntExplosion].nCounter < 18)
			{
				printf("＊");
			}
			else 
			{
				printf("・");
		
				*flag=false;
			}
			*/
		}
	}
}

//=============================================================================
// 爆発の設定
//=============================================================================
void SetExplosion(float fPosX, float fPosY, EXPLOSIONTYPE type, float *X,float *Y,float muki1,bool Gravity,float shot_x,float shot_y)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse == false)
		{// 爆発が未使用状態
			g_aExplosion[nCntExplosion].fPosX = fPosX;
			g_aExplosion[nCntExplosion].fPosY = fPosY;
			g_aExplosion[nCntExplosion].nCounter = 0;
			g_aExplosion[nCntExplosion].type = type;
			g_aExplosion[nCntExplosion].bUse = true;		// 爆発を使用状態に
			g_aExplosion[nCntExplosion].player_x=X;
			g_aExplosion[nCntExplosion].player_y=Y;
			g_aExplosion[nCntExplosion].muki=muki1;
			g_aExplosion[nCntExplosion].gravity=Gravity;
			g_aExplosion[nCntExplosion].Shot_x=shot_x;
			g_aExplosion[nCntExplosion].Shot_y=shot_y;
			break;
		}
	}
}




