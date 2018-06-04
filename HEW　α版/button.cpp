//=============================================================================
//
// ボタン処理[button.cpp]
//
//=============================================================================

#include "main.h"
#include "player.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define button_x (74)
#define button_y (7)
#define button3_x (23)
#define button3_y (19)
#define button2_x (74)
#define button2_y (9)

#define goal_2x   (5)
#define goal_2y   (9)



//*****************************************************************************
// BUtton 関数
//*****************************************************************************


void Button (void)
{ 
	extern PLAYER g_player;
	extern bool button;
	int i;
	extern int count_switch1;
	extern bool count_switch2;
	extern bool goal_switch;
	extern BULLET g_aBullet[1];
	extern int MP3_button1;
	extern int MP3_button2;
	extern int stage;

	COLOR(YELLOW);

	if(stage==1)
	{
			if(button==false)
			{
				LOCATE(button_x,button_y);
				printf("■");
			}
			else
			{
				LOCATE(button_x,button_y);
				printf("□");
			}

			if(button==true)
			{
				LOCATE(button3_x,button3_y);
				printf("■");
			}
			else
			{
				LOCATE(button3_x,button3_y);
				printf("□");
			}

 			if(((int)(g_player.fPosX)==button_x)&&((int)(g_player.fPosY)==button_y)&&(count_switch1>30)
				||((int)(g_player.fPosX)==button3_x)&&((int)(g_player.fPosY)==button3_y)&&(count_switch1>30))
				{
					PLAYMP3(MP3_button1);
				if(button==false)
				{
					button=true;
				}
				else
				{
					button=false;
				}
				count_switch1=0;

			}

		COLOR(H_GREEN);
		if(goal_switch==false)
		{
			LOCATE(button2_x,button2_y);
			printf("■");
		}
		else
		{
			LOCATE(button2_x,button2_y);
			printf("□");
		}

 		if((int)(g_player.fPosX)==button2_x&&(int)(g_player.fPosY)-1==button2_y&&(count_switch2==false)&&count_switch1>30)
		{
			goal_switch=true;
			PLAYMP3(MP3_button2);
		}

		count_switch1++;
	}


	if(stage==2)
	{
			COLOR(YELLOW);
			if(button==false)
			{
				LOCATE(42,13);
				printf("■");
			}
			else
			{
				LOCATE(42,13);
				printf("□");
			}

			if(button==true)
			{
				LOCATE(4,16);
				printf("■");
			}
			else
			{
				LOCATE(4,16);
				printf("□");
			}

 			if(((int)(g_player.fPosX)==42)&&((int)(g_player.fPosY)==14)&&(count_switch1>30)
				||((int)(g_player.fPosX)==4)&&((int)(g_player.fPosY)==16)&&(count_switch1>30))
				{
					PLAYMP3(MP3_button1);

				if(button==false)
				{
					button=true;
				}
				else
				{
					button=false;
				}
				count_switch1=0;

			}

		COLOR(H_GREEN);
		if(goal_switch==false)
		{
			LOCATE(goal_2x,goal_2y);
			printf("■");
		}
		else
		{
			LOCATE(goal_2x,goal_2y);
			printf("□"); 
		}

 		if((int)(g_player.fPosX)==goal_2x&&(int)(g_player.fPosY)==goal_2y&&(count_switch2==false)&&count_switch1>30)
		{
			goal_switch=true;
			PLAYMP3(MP3_button2);
		}

		count_switch1++;
	}
}