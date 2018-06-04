//=============================================================================
//
// �e�̏��� [bullet.cpp]
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "field.h"
#include "explosion.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(1)		// �e�̍ő吔
#define	VALUE_GRAVITY			(0.05f)		// �d�͗�
#define button2_x (66)
#define button2_y (15)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BULLET g_aBullet[MAX_BULLET];		// �e�̏��
extern bool button;
//=============================================================================
// �e�̏���������
//=============================================================================
void InitBullet(void)
{
	// �e�̏�񏉊���
	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].fPosX = 0.0f;
		g_aBullet[nCntBullet].fPosY = 0.0f;
		g_aBullet[nCntBullet].fPosXOld = 0.0f;
		g_aBullet[nCntBullet].fPosYOld = 0.0f;
		g_aBullet[nCntBullet].fMoveX = 0.0f;
		g_aBullet[nCntBullet].fMoveY = 0.0f;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].gravity = false;
		g_aBullet[nCntBullet].player_x = 0;
		g_aBullet[nCntBullet].player_y = 0;
		g_aBullet[nCntBullet].muki = 1.0f;
		g_aBullet[nCntBullet].Shot_x=1;
		g_aBullet[nCntBullet].Shot_y=1;
	}
}

//=============================================================================
// �e�̏I������
//=============================================================================
void TermBullet(void)
{
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void UpdateBullet(int *flag)
{
	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(g_aBullet[nCntBullet].bUse == true)
		{// �e���g�p���
			// �O��̈ʒu��ۑ�
			g_aBullet[nCntBullet].fPosXOld = g_aBullet[nCntBullet].fPosX;
			g_aBullet[nCntBullet].fPosYOld = g_aBullet[nCntBullet].fPosY;

			// �ʒu���X�V
			g_aBullet[nCntBullet].fPosX += g_aBullet[nCntBullet].fMoveX;

	/*
			if(g_aBullet[nCntBullet].gravity==false)
			{
				g_aBullet[nCntBullet].fMoveY+=VALUE_GRAVITY;
			}
			else
			{
				g_aBullet[nCntBullet].fMoveY-=VALUE_GRAVITY;
			}

		*/
	

			g_aBullet[nCntBullet].fPosY += g_aBullet[nCntBullet].fMoveY;

			FIELD *pField;
			pField = GetField();

			FIELD3 *pField3;
			pField3 = GetField3();

			FIELD5 *pField5;
			pField5 = GetField5();
			for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField3++)
			{
				extern PLAYER g_player;
				if(g_aBullet[nCntBullet].fPosX>=pField3->fPosX
				&&g_aBullet[nCntBullet].fPosX<=(pField3->fPosX+pField3->fWidth)
				&&(int)g_aBullet[nCntBullet].fPosY==(int)pField3->fPosY)
				{
					LOCATE((int)(g_aBullet[nCntBullet].fPosXOld), (int)(g_aBullet[nCntBullet].fPosYOld));
					COLOR(GRAY);
					printf("��");

					SetExplosion(g_aBullet[nCntBullet].fPosXOld, g_aBullet[nCntBullet].fPosYOld, EXPLOSIONTYPE_PLAYER,
					g_aBullet[nCntBullet].player_x,g_aBullet[nCntBullet].player_y,
					g_player.fDirect,g_aBullet[nCntBullet].gravity,g_aBullet[nCntBullet].Shot_x,g_aBullet[nCntBullet].Shot_y);

					if(button==false)
					{
						*flag=2;
					}
					else
					{
						*flag=1;
					}

					g_aBullet[nCntBullet].bUse = false;	
				}
			}

			for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField5++)
			{
				if(g_aBullet[nCntBullet].fPosX>=pField5->fPosX
				&&g_aBullet[nCntBullet].fPosX<=(pField5->fPosX+pField5->fWidth)
				&&(int)g_aBullet[nCntBullet].fPosY==(int)pField5->fPosY)
				{
					LOCATE((int)(g_aBullet[nCntBullet].fPosXOld), (int)(g_aBullet[nCntBullet].fPosYOld));
					COLOR(GRAY);
					printf("��");

					SetExplosion(g_aBullet[nCntBullet].fPosXOld, g_aBullet[nCntBullet].fPosYOld, EXPLOSIONTYPE_PLAYER,
					g_aBullet[nCntBullet].player_x,g_aBullet[nCntBullet].player_y,
					g_aBullet[nCntBullet].muki,g_aBullet[nCntBullet].gravity,g_aBullet[nCntBullet].Shot_x,g_aBullet[nCntBullet].Shot_y);

					if(button==true)
					{
						*flag=2;
					}
					else
					{
						*flag=1;
					}

					g_aBullet[nCntBullet].bUse = false;	

				}
			}

			for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
			{
				if((int)g_aBullet[nCntBullet].fPosX>=pField->fPosX-1
				&&(int)g_aBullet[nCntBullet].fPosX<=(pField->fPosX+pField->fWidth)
				&&(int)g_aBullet[nCntBullet].fPosY==(int)pField->fPosY)
				{

					LOCATE((int)(g_aBullet[nCntBullet].fPosXOld), (int)(g_aBullet[nCntBullet].fPosYOld));
					COLOR(GRAY);
					printf("��");

					SetExplosion(g_aBullet[nCntBullet].fPosXOld, g_aBullet[nCntBullet].fPosYOld, EXPLOSIONTYPE_PLAYER,
					g_aBullet[nCntBullet].player_x,g_aBullet[nCntBullet].player_y,
					g_aBullet[nCntBullet].muki,g_aBullet[nCntBullet].gravity,g_aBullet[nCntBullet].Shot_x,g_aBullet[nCntBullet].Shot_y);

					*flag=2;

					g_aBullet[nCntBullet].bUse = false;	
				}
			}


			if(g_aBullet[nCntBullet].fPosX <= 2.0f
			|| g_aBullet[nCntBullet].fPosX >= 79.0f
			|| g_aBullet[nCntBullet].fPosY <3.0f
			|| g_aBullet[nCntBullet].fPosY > 24.0f)
			{// �e����ʊO�ɏo��
				// �O��̈ʒu�ł̒e������
				LOCATE((int)(g_aBullet[nCntBullet].fPosXOld), (int)(g_aBullet[nCntBullet].fPosYOld));
				COLOR(GRAY);
				printf("��");


				// �����ݒ�

					SetExplosion(g_aBullet[nCntBullet].fPosXOld, g_aBullet[nCntBullet].fPosYOld, EXPLOSIONTYPE_PLAYER,
						g_aBullet[nCntBullet].player_x,g_aBullet[nCntBullet].player_y,
						g_aBullet[nCntBullet].muki,g_aBullet[nCntBullet].gravity,g_aBullet[nCntBullet].Shot_x,g_aBullet[nCntBullet].Shot_y);

					*flag=2;
				

				g_aBullet[nCntBullet].bUse = false;		// �e�𖢎g�p��Ԃ�
			}
		}
	}
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void DrawBullet(void)
{
	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{


		if(g_aBullet[nCntBullet].bUse == true)
		{// �e���g�p���
			// �F�ݒ�

				COLOR(CORAL);


			// �O��̈ʒu�ł̒e������
			LOCATE((int)(g_aBullet[nCntBullet].fPosXOld), (int)(g_aBullet[nCntBullet].fPosYOld));
			COLOR(GRAY);
			printf("��");
			// ���݂̈ʒu�ɒe��\��
			if(g_aBullet[nCntBullet].fPosX >= 3.0f && g_aBullet[nCntBullet].fPosX <= 79.0f)
			{
				COLOR(BLUE);
				LOCATE((int)(g_aBullet[nCntBullet].fPosX), (int)(g_aBullet[nCntBullet].fPosY));
				printf("��");
			}


		}
	}
	
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void SetBullet(float fPosX, float fPosY, float fMoveX, float fMoveY,
	bool Gravity,float *X,float *Y,float muki1,float shot_x,float shot_y)
{
	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(g_aBullet[nCntBullet].bUse == false)
		{// �e�����g�p���
			g_aBullet[nCntBullet].fPosX = fPosX;
			g_aBullet[nCntBullet].fPosXOld = fPosX;
		
			if(Gravity==false)
			{
				g_aBullet[nCntBullet].fPosYOld = fPosY;
				g_aBullet[nCntBullet].fPosY = fPosY;
				g_aBullet[nCntBullet].fMoveY = -(shot_y);
			}
			else
			{
				g_aBullet[nCntBullet].fPosYOld = fPosY-1;
				g_aBullet[nCntBullet].fPosY = fPosY-1;
				g_aBullet[nCntBullet].fMoveY = shot_y;
			}
			g_aBullet[nCntBullet].fMoveX = (shot_x)*muki1;
			g_aBullet[nCntBullet].bUse = true;		// �e���g�p��Ԃ�
			g_aBullet[nCntBullet].gravity = Gravity;
			g_aBullet[nCntBullet].player_x=X;
			g_aBullet[nCntBullet].player_y=Y;
			g_aBullet[nCntBullet].muki=muki1;
			g_aBullet[nCntBullet].Shot_x=shot_x;
			g_aBullet[nCntBullet].Shot_y=shot_y;

			break;
		}
	}
}

