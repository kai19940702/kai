//=============================================================================
//
// �X�^�[�g��ʏ���[main.cpp]
//
//=============================================================================


#include"main.h"
#include"player.h"
#include"field.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================

//���y
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
	extern int MP3_system1;//system��
	extern int MP3_system2;//system��

	PLAYMP3(MP3_start);


//����������

		COLOR(WHITE);
		LOCATE(32,2);
		printf("���������������");
		COLOR(BLUE);
		LOCATE(15,5);
		printf("�y�`�z�y�c�z");
		COLOR(WHITE);
		LOCATE(27,5);
		printf("�ňړ�");
		COLOR(BLUE);
		LOCATE(33,5);
		printf("�y�X�y�[�X�z");
		COLOR(WHITE);
		LOCATE(45,5);
		printf("�ŃW�����v�@");
		COLOR(BLUE);
		LOCATE(15,7);
		printf("�y�p�z");
		COLOR(WHITE);
		LOCATE(21,7);
		printf("�F�n�ꔽ�]�@(�d�͂�����ւ��C���[�W�I�j");
		COLOR(BLUE);
		LOCATE(15,9);
		printf("�y�a�z");
		COLOR(WHITE);
		LOCATE(21,9);
		printf("�F�t�b�N�V���b�g�I��");

	

		LOCATE(15,11);
		COLOR(CORAL);
		printf("��");
		LOCATE(17,11);
		COLOR(WHITE);
		printf("��");
		LOCATE(19,11);
		COLOR(CORAL);
		printf("��");
		LOCATE(21,11);
		COLOR(WHITE);
		printf("�ɓ�����Ƃf�`�l�d�n�u�d�q!");

		LOCATE(15,16);
		printf("�M�~�b�N�̓�������Ȃ���S�[����ڎw����!!!!!");

	COLOR(WHITE);
	LOCATE(2,24);
	printf("����������������������������������������������������������������������������");


	COLOR(YELLOW);
	LOCATE(53,19);
	printf("<�}�O�l�b�g���l>");
	COLOR(BLUE);
	LOCATE(53,20);
	printf("����");
	COLOR(WHITE);
	LOCATE(58,20);
	printf("�E�񂪐L�т�");
	LOCATE(58,21);
	printf("�E����");
	COLOR(BLUE);
	LOCATE(64,21);
	printf("S��");
	COLOR(WHITE);
	LOCATE(58,22);
	printf("�E�̂�");
	COLOR(CORAL);
	LOCATE(64,22);
	printf("N��");

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
			printf("�@��");
			LOCATE(70,23);
			COLOR(CORAL);
			printf("�@��");
		}
		else
		{
			LOCATE(70,23-i);
			COLOR(GRAY);
			printf("�@��");
			LOCATE(70,22-i);
			COLOR(BLUE);
			printf("�@��");
		}

	}

	PLAYMP3(MP3_system1);

	COLOR(WHITE);
	LOCATE(65,3);
	printf("���[�h����");
	LOCATE(65,4);
	printf("PUSH ENTER!");

	rewind(stdin);
	getchar();


	//���艹�Ƃa�f�l�I��
	PLAYMP3(MP3_system2);
	CLOSEMP3(MP3_start);

	CLS();


//�o�ꏈ��

	PLAYMP3(MP3_beam);

	
	COLOR(WHITE);
	LOCATE(2,24);
	printf("����������������������������������������������������������������������������");

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
			printf("�E");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("  ");
			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("��");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("  ");
			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("��");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("  ");
			LOCATE(g_player.fPosX,g_player.fPosY);
			printf("��");
			Sleep(60);

			LOCATE(g_player.fPosX,g_player.fPosY-1);
			COLOR(BLUE);
			printf("��");
			Sleep(60);
			

		BACKCOLOR(BLACK);
		CLS();

	CLOSEMP3(MP3_laser);
	CLOSEMP3(MP3_beam);
	CLOSEMP3(MP3_start);
}