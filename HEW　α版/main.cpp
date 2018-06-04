//=============================================================================
//
// アクションゲーム[main.cpp]
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "field.h"
#include "bullet.h"
#include "explosion.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Init(void);
void Term(void);
void Update(void);
void Draw(void);
void DispFPS(void);
void title(void);
void DrawGravity(void);
void Button(void);
void Goal(void);
void start(void);
void menu(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nCountFPS;				// FPSカウンタ
int flag=0;
int count=0;
bool Gravity=false;
bool fin_flag=0;
int x=1;
int x_2=26;
int x_3=52;
bool button=false;
int  count_switch1=30;
bool count_switch2=false;
bool goal_switch=false;
int stage=1;

/*******************************************************************************/
int MP3_bgm;
int MP3_jump;
int MP3_shot;
int MP3_gameover;
int MP3_change;
int MP3_button1;
int MP3_button2;
int MP3_shot_fin;
int MP3_system1;
int MP3_system2;
int MP3_shoot;
int MP3_goal;
//=============================================================================
// メイン関数
//=============================================================================
void main(void)
{
	unsigned long dwExecLastTime;
	unsigned long dwFPSLastTime;
	unsigned long dwCurrentTime;
	int nCountFrame;

	// 分解能を設定
	timeBeginPeriod(1);

	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	nCountFrame = 0;

while(1)
{
	CLS();

		MP3_bgm=OPENMP3("bgm_main.mp3");
		MP3_jump=OPENMP3("jump.mp3");
		MP3_shot=OPENMP3("shot.mp3");
		MP3_gameover=OPENMP3("gameover.mp3");
		MP3_change=OPENMP3("change.mp3");
		MP3_button1=OPENMP3("button1.mp3");
		MP3_button2=OPENMP3("button2.mp3");
		MP3_shot_fin=OPENMP3("shot_fin.mp3");
		MP3_system1=OPENMP3("system1.mp3");
		MP3_system2=OPENMP3("system2.mp3");
		MP3_shoot=OPENMP3("shoot.mp3");
		MP3_goal=OPENMP3("goal.mp3");

	title();

	// 初期化処理

	menu();


	Init();


	start();

	count_switch2=false;
	goal_switch=false;
	Gravity=false;
	fin_flag=false;
	button=false;

	PLAYMP3(MP3_bgm,1);

	// カーソル表示ＯＦＦ
	CUROFF();


	// ゲームメイン処理
	while(fin_flag!=true)
	{
		//dwCurrentTime = timeGetTime();
		//if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
		//{
		//	g_nCountFPS = nCountFrame * 1000 / (dwCurrentTime - dwFPSLastTime);
		//	dwFPSLastTime = dwCurrentTime;
		//	nCountFrame = 0;
		//}

		//if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
		//{
		//	dwExecLastTime = dwCurrentTime;

			// 更新処理
			Update();

			// 描画処理
			Draw();

			Goal();


			// FPS表示
			//DispFPS();


		//	nCountFrame++;
		//}
	}
		CLOSEMP3(MP3_bgm);
		CLOSEMP3(MP3_jump);
		CLOSEMP3(MP3_shot);
		CLOSEMP3(MP3_gameover);
		CLOSEMP3(MP3_change);
		CLOSEMP3(MP3_button1);
		CLOSEMP3(MP3_button2);
		CLOSEMP3(MP3_shot_fin);
		CLOSEMP3(MP3_system1);
		CLOSEMP3(MP3_system2);
		CLOSEMP3(MP3_shoot);
		CLOSEMP3(MP3_goal);
		Term();
}

	// カーソル表示ＯＮ
	CURON();

	// 終了処理
	Term();

	// 分解能を戻す
	timeEndPeriod(1);
}

//=============================================================================
// 初期化処理
//=============================================================================
void Init(void)
{
	// 地面の初期化処理
	InitField();

	InitField2();

	InitField3();

	InitField4();

	InitField5();

	// プレイヤーの初期化処理
	InitPlayer();

	// 弾の初期化処理
	InitBullet();

	// 爆発の初期化処理
	InitExplosion();

}

//=============================================================================
// 終了処理
//=============================================================================
void Term(void)
{
	// 地面の終了処理
	TermField();

	TermField2();

	TermField3();

	TermField4();

	TermField5();

	// プレイヤーの終了処理
	TermPlayer();

	TermBullet();

	// 爆発の終了処理
	TermExplosion();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 地面の更新処理
	UpdateField();

	UpdateField2();

	UpdateField3();

	UpdateField4();

	UpdateField5();

	Button();

	// プレイヤーの更新処理
	UpdatePlayer(&flag);

	// 弾の更新処理
	UpdateBullet(&flag);

	// 爆発の更新処理
	UpdateExplosion(&flag);

	UpdateExplosion2(&flag);



}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// 地面の描画処理
	DrawField();

	DrawField2();

	DrawField3();

	DrawField4();

	DrawField5();


	// プレイヤーの描画処理
	DrawPlayer(&flag);

	// 弾の描画処理
	DrawBullet();

	// 爆発の描画処理
	DrawExplosion();

	//地場の描画処理
	DrawGravity();

}



//=============================================================================
// FPS表示
//=============================================================================

/*
void DispFPS(void)
{
	// 色設定
	COLOR(WHITE);

	LOCATE(2, 3);
	printf("FPS:%d", g_nCountFPS);
}
*/

