//*****************************************************************************
//タイトル処理[title.cpp]
//*****************************************************************************

#include "main.h"
#include<time.h> //乱数使用のため


//*****************************************************************************
// タイトル関数
//*****************************************************************************

void title (void)
{
	int MP3_title=OPENMP3("title_bgm.mp3");
	extern  int MP3_system2;
	int i;

	int x,y;
	int x_old[30];
	int y_old[30];
	int count=30;
	CUROFF();

	PLAYMP3(MP3_title,1);

	char M[100][100]={"                     ",
					  "      ■■    ■■■",
					  "     ■■■■■■■■",
					  "    ■■  ■■■ ■■",
					  "   ■■   ■■   ■■",
					  "  ■■   ■■    ■■",
					  " ■■   ■■     ■■"};

	char A[100][100]={"                  ",
					  "     ■■■■ ",
					  "    ■■■■■",
					  "   ■■   ■■",
					  "  ■■■■■■",
					  " ■■     ■■",
					  "■■      ■■"};

	char G[100][100]={"            ",
					  "  ■■■■  ",
					  " ■■   ■■",
					  "■■         ",
					  "■■   ■■■",
					  " ■■   ■■ ",
					  "  ■■■■   "};

	char N[100][100]={"                        ",
					  "       ■■■     ■■",
					  "      ■■■■   ■■ ",
					  "     ■■ ■■  ■■  ",
					  "    ■■  ■■ ■■   ",
					  "   ■■   ■■■■     ",
					  "  ■■    ■■■      "};

	char E[100][100]={"                  ",
					  "       ■■■■■ ",
					  "      ■■        ",
					  "     ■■■■■   ",
					  "    ■■          ",
					  "   ■■           ",
					  "  ■■■■■      "};


	char T[100][100]={"                ",
					  "  ■■■■■■",
					  "      ■■     ",
					  "     ■■       ",
					  "    ■■       ",
					  "   ■■       ",
					  "  ■■       "};

	char z[100][100]={"           ",
					  "■■■",
					  "   ■  ",
					  " ■   ",
					  "■■■"};

  srand((unsigned)time(NULL));


////////背景処理（星)//////////////////

  for( i = 0 ; i < 30 ; i++ )
  {
	  x_old[i] = 1 ;
	  y_old[i] = 1 ;
  }

  while( 1 )
  {

		if( count >= 20 )
		{
			for( i = 0 ;i < 30 ; i++ )
			{
				LOCATE( x_old[i] , y_old[i] );
				printf(" ");

				x = rand()%78 + 1;
				y = rand()%25 + 1;
				COLOR( YELLOW );
				LOCATE( x , y );
				printf(".");

				x_old[i] = x;
				y_old[i] = y;
			}
			count = 0;
		}

		count++;


	///////////////////M/////////////////////

		for( i = 1 ; i < 7 ; i++ )
		{
			COLOR(GRAY);
			LOCATE( 2 , 2+i );
			printf("%s", &M[i][0]);
		}

			//色付け処理
			LOCATE(3,8);
			COLOR(CORAL);
			printf("■■");

			COLOR(BLUE);
			LOCATE(10,8);
			printf("■■");

			LOCATE(19,8);
			COLOR(CORAL);
			printf("■■");

			COLOR(BLUE);
			LOCATE(8,3);
			printf("■■");

			COLOR(BLUE);
			LOCATE(16,3);
			printf("■■■");

/////////////////A////////////////////////////

		COLOR(GRAY);
		for( i = 1 ; i < 7 ; i++ )
		{
			LOCATE( 25 , 2+i );
			printf("%s",&A[i][0]);
		}

			//色付け

			LOCATE(25,8);
			COLOR(BLUE);
			printf("■■");

			LOCATE(35,8);
			COLOR(BLUE);
			printf("■■");

			LOCATE(30,3);
			COLOR(CORAL);
			printf("■■■■");

///////////////G/////////////////////

		COLOR(GRAY);

		for( i = 1 ; i < 7 ; i++ )
		{
			LOCATE( 41 , 2+i );
			printf("%s",&G[i][0]);
		}

			//色付け

			LOCATE(49,4);
			COLOR(CORAL);
			printf("■■");


			LOCATE(48,6);
			COLOR(BLUE);
			printf("■■■");

/////////////Ｎ//////////////////

		COLOR(GRAY);
		for( i = 1 ; i < 7 ; i++ )
		{
			LOCATE( 15 , 10+i );
			printf("%s",&N[i][0]);
		}

		//色付け
		COLOR(BLUE);
		LOCATE(22,11);
		printf("■■■");

		COLOR(CORAL);
		LOCATE(33,11);
		printf("■■");

		COLOR(CORAL);
		LOCATE(17,16);
		printf("■■");

		COLOR(BLUE);
		LOCATE(25,16);
		printf("■■■");

///////////////////////////////////

		COLOR(GRAY);

		for( i = 1 ; i < 7 ; i++ )
		{
			LOCATE( 37 , 10+i );
			printf("%s",&E[i][0]);
		}

		//色付け

		COLOR(CORAL);
		LOCATE(52,11);
		printf("■");

		COLOR(BLUE);
		LOCATE(50,13);
		printf("■");

		COLOR(CORAL);
		LOCATE(47,16);
		printf("■");


///////////Ｔ//////////////

		COLOR(GRAY);

		for( i = 1 ; i < 7 ; i++ )
		{
			LOCATE(55,10+i);
			printf("%s",&T[i][0]);
		}

		//色付け

		COLOR(BLUE);
		LOCATE(57,11);
		printf("■");

		COLOR(CORAL);
		LOCATE(67,11);
		printf("■");

		COLOR(BLUE);
		LOCATE(57,16);
		printf("■■");

//////////////Ｚ///////////////

		COLOR(GRAY);

		for( i = 1 ; i < 7 ; i++ )
		{
			LOCATE(70,12+i);
			printf("%s",&z[i][0]);
		}

		//色付け

		COLOR(CORAL);
		LOCATE(70,13);
		printf("■");

		COLOR(BLUE);
		LOCATE(74,16);
		printf("■");

/////////////////////////////

		LOCATE(33,22);
		printf("PUSH ENTER KEY");

		if(kbhit())
		{
			PLAYMP3(MP3_system2);
			break;
		}

	}


	CLOSEMP3(MP3_title);

	getchar();
	system("cls");

}