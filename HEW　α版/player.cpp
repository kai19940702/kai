//=============================================================================
//
// プレイヤーの処理 [player.cpp]
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_X			(0.75f)		// 地上での移動量Ｘ方向
#define	VALUE_MOVE_X_AIR		(0.30f)		// 空中での移動量Ｘ方向
#define	VALUE_JUMP				(0.80f)		// ジャンプ量
#define	VALUE_RESIST_X			(0.60f)		// 地上での移動摩擦抵抗
#define	VALUE_RESIST_X_AIR		(0.50f)		// 空中での移動摩擦抵抗
#define	VALUE_GRAVITY			(0.05f)		// 重力量
#define	LIMIT_LEFT				(2.0f)		// 移動範囲左端
#define	LIMIT_RIGHT				(78.0f)		// 移動範囲右端
#define	LIMIT_DOWN				(24.0f)		// 移動範囲下端

#define SP (300)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CheckCollisionField(void);
void CheckCollisionField2(void);
void CheckCollisionField3(void);
void atarihanntei(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER g_player;							// プレイヤーの情報
extern bool Gravity;
extern bool button;

extern int MP3_shot;
extern int MP3_jump;
extern int MP3_gameover;
extern int MP3_change;
extern int MP3_bgm;
extern int MP3_shoot;
extern bool fin_flag;
int MP3_gameover_bgm=OPENMP3("gameover_bgm.mp3");
int key;

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
void InitPlayer(void)
{
	// プレイヤーの情報初期化
	g_player.fPosX =5.0f;
	g_player.fPosY = 0.0f;
	g_player.fPosXOld = 5.0f;
	g_player.fPosYOld = 23.0f;
	g_player.fMoveX = 0.0f;
	g_player.fMoveY = 0.0f;
	g_player.bJump = false;
	g_player.bLand = false;
	g_player.bShot = false;
	g_player.bMove = false;
	g_player.bGravity = false;
	g_player.fDirect = 1.0f;
	g_player.pField = NULL;
	g_player.count = 0;

}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void TermPlayer(void)
{
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void UpdatePlayer(int *flag)
{
	int count=0;
	float shot_x=1;
	float shot_y=1;
	int i,j;
	

	char change1_1[8][100]={"          ■■■■■■■■             ",
							"         ■■■■■■■■■■           ",
							"       ■■                ■■         ",
						    "     ■■                   ■■        ",
							"   ■■                    ■■■■■   ",
							"   ■■                      ■■■     ",
							"  ■■                        ■■      ",
							"  ■■                         ■       "};





	char change2_1[50][100]={"     ■                         ■■  ",
							 "    ■■                        ■■  ",
							 "   ■■■                      ■■   ",
						     " ■■■■■                    ■■   ",
							 "     ■■                    ■■     ",
							 "      ■■                  ■■      ",
							 "        ■■■■■■■■■■■        ",
							 "          ■■■■■■■■■          "};



		
	// 前回の位置を保存
	g_player.fPosXOld = g_player.fPosX;
	g_player.fPosYOld = g_player.fPosY;


	if(g_player.pField != NULL)
	{// 地面の上に乗っている場合
		g_player.fPosX += (g_player.pField->fPosX - g_player.pField->fPosXOld);
		g_player.fPosY += (g_player.pField->fPosY - g_player.pField->fPosYOld);
	}

if(*flag==0)
 {

	if(INP(PK_B))
		{// 攻撃
			while(INP(PK_B))
			{

				if(count%60001==20000)
				{
					shot_x=1;
					shot_y=1;

					for(i=0;i<6;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i*4), (int)(g_player.fPosY - 1.0f-i));
					printf("  ");
					}
					for(i=0;i<10;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i), (int)(g_player.fPosY - 1.0f-i));
					printf("○");
					}

				}
				if(count%60001==40000)
				{
					shot_x=1;
					shot_y=0.5;

					for(i=0;i<10;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i), (int)(g_player.fPosY - 1.0f-i));
					printf("  ");
					}

					for(i=0;i<6;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i*2), (int)(g_player.fPosY - 1.0f-i));
					printf("○");
					}
			}
			if(count%60001==60000)
			{
				shot_x=2;
				shot_y=0.5;

				for(i=0;i<6;i++)
				{
				LOCATE((int)(g_player.fPosX+2+i*2), (int)(g_player.fPosY - 1.0f-i));
				printf("  ");
				}

				for(i=0;i<6;i++)
				{
				LOCATE((int)(g_player.fPosX+2+i*4), (int)(g_player.fPosY - 1.0f-i));
				printf("○");
				}
			}
			count++;
		}

		if(!g_player.bShot)
		{
			if(g_player.fPosX >= 3.0f && g_player.fPosX <= 77.0f)
			{
				if(*flag==0)
				{
					// 弾の設定
					SetBullet(g_player.fPosX, g_player.fPosY
						, g_player.fDirect, 0.0f,g_player.bGravity,
						&g_player.fPosX,&g_player.fPosY,g_player.fDirect,shot_x,shot_y);
					g_player.bShot = true;
					PLAYMP3(MP3_shoot);
					*flag=1;
					count=0;
				}
			}
		}
	}
	else
	{
		if(g_player.bShot)
		{// ショット中
			if(*flag==0)
			{
				g_player.bShot = false;
			}
		}
	}
 }	
	
	if(*flag==0)
	{
		if(INP(PK_A))
		{// 左移動
			if(g_player.bJump == true)
			{
				g_player.fMoveX -= VALUE_MOVE_X_AIR;
			}
			else
			{
				g_player.fMoveX -= VALUE_MOVE_X;
			}
				g_player.bMove = true;

				g_player.fDirect = -1.0f;
		}

		if(INP(PK_D))
		{// 右移動
			if(g_player.bJump == true)
			{
				g_player.fMoveX += VALUE_MOVE_X_AIR;
			}
			else
			{
				g_player.fMoveX += VALUE_MOVE_X;
			}
			g_player.bMove = true;

			g_player.fDirect = 1.0f;
		}

		if(INP(PK_SP))
		{
			// ジャンプ
			if(g_player.bGravity == false)
			{
				if(g_player.bJump == false)
				{
					PLAYMP3(MP3_jump);
					g_player.fMoveY = -VALUE_JUMP;
					g_player.bJump = true;
				}
			}
			else
			{
				if(g_player.bJump == false)
				{
					PLAYMP3(MP3_jump);
					g_player.fMoveY = +VALUE_JUMP;
					g_player.bJump = true;
				}
			}
		}


		if(INP(PK_Q))
		{
			PLAYMP3(MP3_change);
			for(j=0;j<2;j++)
			{
				if(j%2==0)
				{
					COLOR(BLUE);
				}
				else
				{
					COLOR(CORAL);
				}
				for(i=0;i<8;i++)
				{
					LOCATE(21,5+i);
					printf("%s",&change1_1[i][0]);
					LOCATE(34,13);
					printf("地場");
				}
				if(j%2==0)
				{
					COLOR(CORAL);
				}
				else
				{
					COLOR(BLUE);
				}
				for(i=0;i<8;i++)
				{
					LOCATE(20,14+i);
					printf("%s",&change2_1[i][0]);
					LOCATE(38,13);
					printf("反転");
				}
				Sleep(500);
			}
				system("cls");

				
				if(g_player.count>=15)
				{
					if(g_player.bGravity == false)
					{
						g_player.bGravity = true;
						LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
						printf("　");
						Gravity=true;	
				}
					else
					{
						g_player.bGravity = false;
						LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
						printf("　");
						Gravity=false;
					}
					g_player.count=0;
				}

			}
		}
	
	// 移動量更新
	if(g_player.bJump)
	{// ジャンプ中
		g_player.bMove = true;

		g_player.fMoveX += (0.0f - g_player.fMoveX) * VALUE_RESIST_X_AIR;		// 抵抗を加える
	}
	else
	{
		g_player.fMoveX += (0.0f - g_player.fMoveX) * VALUE_RESIST_X;			// 抵抗を加える
	}


 

 if(*flag==0)
 {
	if(g_player.bGravity == false)
	{
		g_player.fMoveY += VALUE_GRAVITY;			// 重力を加える
	}
	else
	{
		g_player.fMoveY -= VALUE_GRAVITY;
	}
 }



 if(*flag==0)
 {
	// 位置更新
	g_player.fPosX += g_player.fMoveX;
	if(g_player.fPosX < LIMIT_LEFT)
	{// 左端を超えた場合
		g_player.fPosX = LIMIT_LEFT;
	}
	if(g_player.fPosX > LIMIT_RIGHT)
	{// 右端を超えた場合
		g_player.fPosX = LIMIT_RIGHT;
	}
	
	g_player.fPosY += g_player.fMoveY;
 }

	
	CheckCollisionField2();
	CheckCollisionField3();


	if(CheckCollisionField() == true)
	{// 地面にめり込んだ
		g_player.bMove = true;
		g_player.fMoveY = 0.0f;
		g_player.bJump = false;
		g_player.bLand = true;
	}
	else
	{

		if(g_player.bLand)
		{	
			g_player.bJump = true;
			g_player.bLand = false;
		}
	}

	if((g_player.fPosX==GOAL_X)&&(g_player.fPosY==GOAL_Y))
	{
		system("cls");
		getchar();
	}


	atarihanntei();
	g_player.count++;
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void DrawPlayer(int *flag)
{
	// 色設定
	COLOR(YELLOW);

	if(g_player.bMove)
	{// 移動した場合
		// 前回の位置でのプレイヤーを消去
		if(g_player.bGravity==false)
		{
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
			printf("　");
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld - 1.0f));
			printf("　");
		}
		else
		{
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
			printf("　");
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld - 1.0f));
			printf("　");

			if(g_player.bJump == true)
			{
				LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld + 1.0f));
				printf("　");
			}
		}


		g_player.bMove = false;
	}

	// 現在の位置プレイヤーを表示
	if(g_player.bGravity==false)
	{
		COLOR(CORAL);
		LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY));
		printf("■");
		COLOR(BLUE);
		if(*flag==false)
		{
			LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
			printf("●");
		}
	}
	else
	{
		if(*flag==0)
		{
			COLOR(BLUE);
			LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY));
			printf("●");
		}
		COLOR(CORAL);
		LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
		printf("■");
	}


}

//=============================================================================
// 地面との当たり判定
//=============================================================================
bool CheckCollisionField(void)
{
	FIELD *pField;

	// 地面を取得
	pField = GetField();

	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
			if(pField->bUse == true)
			{

				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{// 地面の幅の範囲内
					if(g_player.fPosY > (pField->fPosY - 1.0f) && g_player.fPosYOld <= (pField->fPosY - 1.0f))
					{// 足元が地面にめり込んだ場合
						g_player.fPosY = pField->fPosY - 1.0f;
						g_player.pField = pField;
						return true;
						
					}
				}

				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{
					// 地面の幅の範囲内
					if((g_player.fPosY - 2.0f) < pField->fPosY && (g_player.fPosYOld - 1.0f) >= pField->fPosY)
					{
						// 頭が地面にめり込んだ場合
						g_player.fPosY = pField->fPosY + 2.0f;
						g_player.fMoveY = 0.0f;

						if(g_player.bGravity==true)
						{
							return true;
						}
					}
				}
			}


	}
	
		return false;
}


void CheckCollisionField2(void)
{
	FIELD2 *pField;


int k,j;

	char Y[5][20]={" ■     ■",
				   "  ■   ■ ",
				   "   ■■  ",
				   "    ■   ",
				   "    ■   "};

	char o[5][20]={"         ",
				   "   ■■  ",
		           " ■    ■",
				   " ■    ■",
				   "   ■■  "};

	char u[5][20]={"        ",
				   "■    ■",
				   "■    ■",
				   "■    ■",
				   "  ■■  "};
	
	char D[5][20]={"■■■   ",
		           "■    ■ ",
				   "■    ■ ",
				   "■    ■ ",
				   "■■■   "};

	char i[5][20]={"        ",
				   "   ■   ",
				   "        ",
				   "   ■   ",
				   "   ■   "};

	char e[5][20]={"          ",
				   "   ■■   ",
				   "  ■■■  ",
				   "  ■      ",
				   "   ■■   " };

	char d[5][20]={"     ■",
				   "     ■",
				   "   ■■",
				   "  ■ ■",
				   "   ■■"};

	// 地面を取得
	pField = GetField2();

	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
			if(pField->bUse == true)
			{
				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{// 地面の幅の範囲内
					if((int)g_player.fPosY-1 == (pField->fPosY))
					{
						CLOSEMP3(MP3_bgm);
						PLAYMP3(MP3_gameover);
						PLAYMP3(MP3_gameover_bgm);
						system("CLS");
						fin_flag=true;
						COLOR(CORAL);
						for(k=0;k<5;k++)
						{
							LOCATE(8,3+k);
							printf("%s",&Y[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(20,6+k);
							printf("%s",&o[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(33,3+k);
							printf("%s",&u[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(25,16+k);
							printf("%s",&D[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(35,12+k);
							printf("%s",&i[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(45,14+k);
							printf("%s",&e[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(55,17+k);
							printf("%s",&d[k][0]);
						}
						Sleep(SP);
						for(k=0;k<10;k+=4)
						{
							LOCATE(66+k,20);
							printf("■");
							Sleep(SP);
						}
						rewind(stdin);
						getchar();
					}
				}

			}


	}

}


void CheckCollisionField3(void)
{
int k,j;

	char Y[5][20]={" ■     ■",
				   "  ■   ■ ",
				   "   ■■  ",
				   "    ■   ",
				   "    ■   "};

	char o[5][20]={"         ",
				   "   ■■  ",
		           " ■    ■",
				   " ■    ■",
				   "   ■■  "};

	char u[5][20]={"        ",
				   "■    ■",
				   "■    ■",
				   "■    ■",
				   "  ■■  "};
	
	char D[5][20]={"■■■   ",
		           "■    ■ ",
				   "■    ■ ",
				   "■    ■ ",
				   "■■■   "};

	char i[5][20]={"        ",
				   "   ■   ",
				   "        ",
				   "   ■   ",
				   "   ■   "};

	char e[5][20]={"          ",
				   "   ■■   ",
				   "  ■■■  ",
				   "  ■      ",
				   "   ■■   " };

	char d[5][20]={"     ■",
				   "     ■",
				   "   ■■",
				   "  ■ ■",
				   "   ■■"};
	FIELD4 *pField;

	// 地面を取得
	pField = GetField4();

	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
			if(pField->bUse == true)
			{
				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{// 地面の幅の範囲内
					if((int)g_player.fPosY == (pField->fPosY ))
					{// 足元が地面にめり込んだ場合

						fin_flag=true;
						CLOSEMP3(MP3_bgm);
						PLAYMP3(MP3_gameover);
						system("CLS");
						PLAYMP3(MP3_gameover_bgm);
						COLOR(CORAL);
						for(k=0;k<5;k++)
						{
							LOCATE(8,3+k);
							printf("%s",&Y[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(20,6+k);
							printf("%s",&o[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(33,3+k);
							printf("%s",&u[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(25,16+k);
							printf("%s",&D[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(35,12+k);
							printf("%s",&i[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(45,14+k);
							printf("%s",&e[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(55,17+k);
							printf("%s",&d[k][0]);
						}
						Sleep(SP);
						for(k=0;k<10;k+=4)
						{
							LOCATE(66+k,20);
							printf("■");
							Sleep(SP);
						}
						rewind(stdin);
						getchar();
						CLS();
					}
				}
				
			}


	}

}

//壁との当たり判定

void atarihanntei(void)
{
	FIELD *pField;
	pField = GetField();


	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
		if((pField->fPosX<=g_player.fPosX+1)&&(pField->fPosY==g_player.fPosY)&&
			(((pField->fPosX)+(pField->fWidth-1))>=(g_player.fPosX))&&
			(g_player.fDirect == 1.0f))
		{
			g_player.fPosX-=1;
			g_player.fMoveX = 0.0f;
			break;
		}
		else if((pField->fPosX<=g_player.fPosX+1)&&(pField->fPosY==g_player.fPosY)&&
			(((pField->fPosX)+(pField->fWidth))>=(g_player.fPosX))&&
			(g_player.fDirect == -1.0f))
		{
			g_player.fPosX+=1;
			g_player.fMoveX = 0.0f;
			break;
		}

	}
}



