//*****************************************************************************
//ínèÍèÛãµï`é [Gravity.cpp]
//*****************************************************************************

#include"main.h"

//*****************************************************************************
//DrawGravityä÷êî
//*****************************************************************************

void DrawGravity(void)
{
	extern bool Gravity; //ínèÍèÛãµéÊìæ
	extern int x;
	extern int x_2;
	extern int x_3;
	extern int count;

	int y;
	int y_2;
	int y_3;

//ï`âÊèàóù
	if(count%2==1)
	{
		y=x;

		y_2=x_2;

		y_3=x_3;

		x++;

		x_2++;

		x_3++;

		if( x > 75 )
		{
			x = 3;
		}

		if( x_2 > 75)
		{
			x_2 = 3;
		}

		if( x_3 > 75)
		{
			x_3 = 3;
		}

		if( Gravity == true )
		{
				COLOR(BLUE);
				LOCATE(3+y,1);
				printf("Å@Å@");
				LOCATE(3+x,1);
				printf("Çrã…");

				COLOR(CORAL);
				LOCATE(77-y,25);
				printf("Å@Å@");
				LOCATE(77-x,25);
				printf("Çmã…");

				COLOR(BLUE);
				LOCATE(3+y_2,1);
				printf("Å@Å@");
				LOCATE(3+x_2,1);
				printf("Çrã…");

				COLOR(CORAL);
				LOCATE(77-y_2,25);
				printf("Å@Å@");
				LOCATE(77-x_2,25);
				printf("Çmã…");

				COLOR(BLUE);
				LOCATE(3+y_3,1);
				printf("Å@Å@");
				LOCATE(3+x_3,1);
				printf("Çrã…");

				COLOR(CORAL);
				LOCATE(77-y_3,25);
				printf("Å@Å@");
				LOCATE(77-x_3,25);
				printf("Çmã…");
		
		}
		else
		{
				COLOR(CORAL);
				LOCATE(3+y,1);
				printf("Å@Å@");
				LOCATE(3+x,1);
				printf("Çmã…");

				COLOR(BLUE);
				LOCATE(77-y,25);
				printf("Å@Å@");
				LOCATE(77-x,25);
				printf("Çrã…");

				COLOR(CORAL);
				LOCATE(3+y_2,1);
				printf("Å@Å@");
				LOCATE(3+x_2,1);
				printf("Çmã…");

				COLOR(BLUE);
				LOCATE(77-y_2,25);
				printf("Å@Å@");
				LOCATE(77-x_2,25);
				printf("Çrã…");

				COLOR(CORAL);
				LOCATE(3+y_3,1);
				printf("Å@Å@");
				LOCATE(3+x_3,1);
				printf("Çmã…");

				COLOR(BLUE);
				LOCATE(77-y_3,25);
				printf("Å@Å@");
				LOCATE(77-x_3,25);
				printf("Çrã…");
		}
	}

	count++;
}
