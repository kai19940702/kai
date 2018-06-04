//=============================================================================
//
// �����̏��� [explosion.cpp]
//
//=============================================================================
#include "main.h"
#include "explosion.h"
#include "bullet.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION		(100)		// �����̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EXPLOSION g_aExplosion[MAX_EXPLOSION];		// �e�̏��
extern bool button;
extern int MP3_shot_fin;
int mp3flag=0;
//=============================================================================
// �����̏���������
//=============================================================================
void InitExplosion(void)
{
	// �e�̏�񏉊���
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
// �����̏I������
//=============================================================================
void TermExplosion(void)
{
}

//=============================================================================
// �����̍X�V����
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
		{// �������g�p���
			g_aExplosion[nCntExplosion].nCounter++;
			if(g_aExplosion[nCntExplosion].nCounter > 24)
			{// �����I��
				/*

				// ����������
				LOCATE((int)(g_aExplosion[nCntExplosion].fPosX), (int)(g_aExplosion[nCntExplosion].fPosY));
				printf("�@");
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
				g_aExplosion[nCntExplosion].bUse = false;		// �����𖢎g�p��Ԃ�
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
		{// �������g�p���
			g_aExplosion[nCntExplosion].nCounter++;
			if(g_aExplosion[nCntExplosion].nCounter > 24)
			{// �����I��
				

				// ����������
				LOCATE((int)(g_aExplosion[nCntExplosion].fPosX), (int)(g_aExplosion[nCntExplosion].fPosY));
				printf("�@");
				
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
				printf("��");

				if((int)*Y==(int)(g_aExplosion[nCntExplosion].fPosY))
				{
					g_aExplosion[nCntExplosion].bUse = false;		// �����𖢎g�p��Ԃ�
					*flag=0;
				}




			}
		}
	}
	}
}

//=============================================================================
// �����̕`�揈��
//=============================================================================
void DrawExplosion(void)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse == true)
		{// �������g�p���

			// �F�ݒ�
			if(g_aExplosion[nCntExplosion].type == EXPLOSIONTYPE_PLAYER)
			{// �v���C���[�̒e
				COLOR(BLUE);
			}
			else
			{// �G�̒e
				COLOR(PINK);
			}

		
			// ���݂̈ʒu�ɔ�����\��
			LOCATE((int)(g_aExplosion[nCntExplosion].fPosX), (int)(g_aExplosion[nCntExplosion].fPosY));
			if(g_aExplosion[nCntExplosion].nCounter < 6)
			{
				printf("��");
			}
		/*
			else if(g_aExplosion[nCntExplosion].nCounter < 12)
			{
				printf("��");
			}
			else if(g_aExplosion[nCntExplosion].nCounter < 18)
			{
				printf("��");
			}
			else 
			{
				printf("�E");
		
				*flag=false;
			}
			*/
		}
	}
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void SetExplosion(float fPosX, float fPosY, EXPLOSIONTYPE type, float *X,float *Y,float muki1,bool Gravity,float shot_x,float shot_y)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse == false)
		{// ���������g�p���
			g_aExplosion[nCntExplosion].fPosX = fPosX;
			g_aExplosion[nCntExplosion].fPosY = fPosY;
			g_aExplosion[nCntExplosion].nCounter = 0;
			g_aExplosion[nCntExplosion].type = type;
			g_aExplosion[nCntExplosion].bUse = true;		// �������g�p��Ԃ�
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




