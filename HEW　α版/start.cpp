//=============================================================================
//
// スタート画面処理[main.cpp]
//
//=============================================================================


#include"main.h"
#include"player.h"
#include"field.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================

//音楽
int MP3_laser;
int MP3_beam;
int MP3_start;

//player
extern PLAYER g_player;

void start(void)
{
	MP3_laser=OPENMP3("laser.mp3");
	MP3_beam=OPENMP3("beam.mp3");
	MP3_start=OPENMP3("start_bgm.mp3");
	int old_y;
	int i;
	extern int MP3_system1;//system音
	extern int MP3_system2;//system音

	PLAYMP3(MP3_start);


//操作説明画面

		COLOR(WHITE);
		LOCATE(32,2);
		printf("◇◇操作説明◇◇");
		COLOR(BLUE);
		LOCATE(15,5);
		printf("【Ａ】【Ｄ】");
		COLOR(WHITE);
		LOCATE(27,5);
		printf("で移動");
		COLOR(BLUE);
		LOCATE(33,5);
		printf("【スペース】");
		COLOR(WHITE);
		LOCATE(45,5);
		printf("でジャンプ　");
		COLOR(BLUE);
		LOCATE(15,7);
		printf("【Ｑ】");
		COLOR(WHITE);
		LOCATE(21,7);
		printf("：地場反転　(重力が入れ替わるイメージ！）");
		COLOR(BLUE);
		LOCATE(15,9);
		printf("【Ｂ】");
		COLOR(WHITE);
		LOCATE(21,9);
		printf("：フックショット的な");

	

		LOCATE(15,11);
		COLOR(CORAL);
		printf("▲");
		LOCATE(17,11);
		COLOR(WHITE);
		printf("や");
		LOCATE(19,11);
		COLOR(CORAL);
		printf("▼");
		LOCATE(21,11);
		COLOR(WHITE);
		printf("に当たるとＧＡＭＥＯＶＥＲ!");

		LOCATE(15,16);
		printf("ギミックの謎を解きながらゴールを目指そう!!!!!");

	COLOR(WHITE);
	LOCATE(2,24);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");


	COLOR(YELLOW);
	LOCATE(53,19);
	printf("<マグネット星人>");
	COLOR(BLUE);
	LOCATE(53,20);
	printf("特徴");
	COLOR(WHITE);
	LOCATE(58,20);
	printf("・首が伸びる");
	LOCATE(58,21);
	printf("・頭が");
	COLOR(BLUE);
	LOCATE(64,21);
	printf("S極");
	COLOR(WHITE);
	LOCATE(58,22);
	printf("・体が");
	COLOR(CORAL);
	LOCATE(64,22);
	printf("N極");

	for( i = 0 ; i <= 15 ; i++ )
	{
		COLOR(WHITE);
		LOCATE(65,3);
		printf("Loading.  ");
		Sleep(100);
		LOCATE(65,3);
		printf("Loading.. ");
		Sleep(100);
		LOCATE(65,3);
		printf("Loading...");
		Sleep(100);

		if( i == 0 )
		{
			LOCATE(70,22);
			COLOR(BLUE);
			printf("　●");
			LOCATE(70,23);
			COLOR(CORAL);
			printf("　■");
		}
		else
		{
			LOCATE(70,23-i);
			COLOR(GRAY);
			printf("　首");
			LOCATE(70,22-i);
			COLOR(BLUE);
			printf("　●");
		}

	}

	PLAYMP3(MP3_system1);

	COLOR(WHITE);
	LOCATE(65,3);
	printf("ロード完了");
	LOCATE(65,4);
	printf("PUSH ENTER!");

	rewind(stdin);
	getchar();


	//決定音とＢＧＭ終了
	PLAYMP3(MP3_system2);
	CLOSEMP3(MP3_start);

	CLS();


//登場処理

	PLAYMP3(MP3_beam);

	
	COLOR(WHITE);
	LOCATE(2,24);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	BACKCOLOR(H_YELLOW);


	for( i = 1 ; i < 24 ; i++ )
	{
		LOCATE(2,i);
		printf("         ");
		Sleep(20);
	}
	Sleep(20);


		PLAYMP3(MP3_laser);




		while( g_player.fPosY != 23 )
		{
			COLOR(CORAL);

			old_y = g_player.fPosY;

			g_player.fPosY++;

			LOCATE(g_player.fPosX,g_player.fPosY);

			printf("|");

			LOCATE(g_player.fPosX,old_y);

			printf(" ");

			Sleep(20);
		}


			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("・");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("  ");
			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("＊");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("  ");
			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("□");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("  ");
			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("■");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY-1);
			COLOR(BLUE);
			printf("●");
			Sleep(60);
			

		BACKCOLOR(BLACK);
		CLS();

	CLOSEMP3(MP3_laser);
	CLOSEMP3(MP3_beam);
	CLOSEMP3(MP3_start);
}