#define GOAL_X (76)
#define GOAL_Y (23)
#define button2_x (74)
#define button2_y (9)


#include "main.h"
#include "player.h"
#include "field.h"

void DrawField(void);
void DrawGravity(void);
void InitField(void);
void InitPlayer(void);
void start(void);

void Goal (void)
{
	extern bool fin_flag;
	extern PLAYER g_player;
	extern int MP3_bgm;
	extern int  MP3_goal;
	extern int MP3_laser;
	extern int MP3_beam;
	extern  int stage;
	extern bool goal_switch;
	extern bool count_switch2;
	int i,k,j;
	int old_y;




		if(goal_switch==false)
		{
			for(i=0;i<4;i++)
			{
				COLOR(H_GREEN);
				LOCATE(72,23-i);
				printf("‚f");
			}
		}
		if(goal_switch==true&&count_switch2==false)
		{
			for(i=0;i<5;i++)
			{
				COLOR(H_GREEN);
				LOCATE(72,23-i);
				printf("  ");
				LOCATE(72,20-i);
				printf("‚f");
				Sleep(20);
			}
			count_switch2=true;
		}

		if(goal_switch==false)
		{
			if((int)g_player.fPosX==72&&g_player.fPosY<=23&&g_player.fPosY>=21)
			{
				g_player.fPosX=70;
			}
		}
		else
		{
			if((int)g_player.fPosX==GOAL_X&&g_player.fPosY==23)
			{
				CLOSEMP3(MP3_bgm);
				for(i=0;i<4;i++)
				{
					COLOR(H_GREEN);
					LOCATE(72,16+i);
					printf("  ");
					LOCATE(72,20+i);
					printf("‚f");
					Sleep(20);
				}
				LOCATE(72,19);

				PLAYMP3(MP3_beam);
				COLOR(WHITE);
				printf("¡");
				LOCATE(g_player.fPosX,g_player.fPosY-1);
				printf("  ");


				BACKCOLOR(H_YELLOW);
				for(i=1;i<24;i++)
				{
				LOCATE(71,i);
				printf("         ");
				Sleep(20);
				}
			

				COLOR(CORAL);
				LOCATE(g_player.fPosX,g_player.fPosY);
				printf("›");
				Sleep(100);
				LOCATE(g_player.fPosX,g_player.fPosY);
				printf("  ");
				LOCATE(g_player.fPosX,g_player.fPosY);
				printf("–");
				Sleep(100);
				LOCATE(g_player.fPosX,g_player.fPosY);
				printf("  ");
				LOCATE(g_player.fPosX,g_player.fPosY);
				printf("E");
				PLAYMP3(MP3_laser);

				while(g_player.fPosY!=1)
				{
					COLOR(CORAL);
					old_y=g_player.fPosY;
					g_player.fPosY--;
					LOCATE(g_player.fPosX,g_player.fPosY);
					printf("|");
				
					LOCATE(g_player.fPosX,old_y);
					printf(" ");
				
					Sleep(20);
				}

				BACKCOLOR(BLACK);
				PLAYMP3(MP3_goal);
				CLS();
				LOCATE(38,13);
				printf("GOAL");
				rewind(stdin);
				getchar();
				CLS();
				fin_flag=true;
				CLOSEMP3(MP3_goal);




			}
	}

}