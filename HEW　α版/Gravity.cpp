//*****************************************************************************
//�n��󋵕`��[Gravity.cpp]
//*****************************************************************************

#include"main.h"

//*****************************************************************************
//DrawGravity�֐�
//*****************************************************************************

void DrawGravity(void)
{
	extern bool Gravity; //�n��󋵎擾
	extern int x;
	extern int x_2;
	extern int x_3;
	extern int count;

	int y;
	int y_2;
	int y_3;

//�`�揈��
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
				printf("�@�@");
				LOCATE(3+x,1);
				printf("�r��");

				COLOR(CORAL);
				LOCATE(77-y,25);
				printf("�@�@");
				LOCATE(77-x,25);
				printf("�m��");

				COLOR(BLUE);
				LOCATE(3+y_2,1);
				printf("�@�@");
				LOCATE(3+x_2,1);
				printf("�r��");

				COLOR(CORAL);
				LOCATE(77-y_2,25);
				printf("�@�@");
				LOCATE(77-x_2,25);
				printf("�m��");

				COLOR(BLUE);
				LOCATE(3+y_3,1);
				printf("�@�@");
				LOCATE(3+x_3,1);
				printf("�r��");

				COLOR(CORAL);
				LOCATE(77-y_3,25);
				printf("�@�@");
				LOCATE(77-x_3,25);
				printf("�m��");
		
		}
		else
		{
				COLOR(CORAL);
				LOCATE(3+y,1);
				printf("�@�@");
				LOCATE(3+x,1);
				printf("�m��");

				COLOR(BLUE);
				LOCATE(77-y,25);
				printf("�@�@");
				LOCATE(77-x,25);
				printf("�r��");

				COLOR(CORAL);
				LOCATE(3+y_2,1);
				printf("�@�@");
				LOCATE(3+x_2,1);
				printf("�m��");

				COLOR(BLUE);
				LOCATE(77-y_2,25);
				printf("�@�@");
				LOCATE(77-x_2,25);
				printf("�r��");

				COLOR(CORAL);
				LOCATE(3+y_3,1);
				printf("�@�@");
				LOCATE(3+x_3,1);
				printf("�m��");

				COLOR(BLUE);
				LOCATE(77-y_3,25);
				printf("�@�@");
				LOCATE(77-x_3,25);
				printf("�r��");
		}
	}

	count++;
}
