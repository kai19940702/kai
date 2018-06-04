//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE_X			(0.75f)		// �n��ł̈ړ��ʂw����
#define	VALUE_MOVE_X_AIR		(0.30f)		// �󒆂ł̈ړ��ʂw����
#define	VALUE_JUMP				(0.80f)		// �W�����v��
#define	VALUE_RESIST_X			(0.60f)		// �n��ł̈ړ����C��R
#define	VALUE_RESIST_X_AIR		(0.50f)		// �󒆂ł̈ړ����C��R
#define	VALUE_GRAVITY			(0.05f)		// �d�͗�
#define	LIMIT_LEFT				(2.0f)		// �ړ��͈͍��[
#define	LIMIT_RIGHT				(78.0f)		// �ړ��͈͉E�[
#define	LIMIT_DOWN				(24.0f)		// �ړ��͈͉��[

#define SP (300)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CheckCollisionField(void);
void CheckCollisionField2(void);
void CheckCollisionField3(void);
void atarihanntei(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER g_player;							// �v���C���[�̏��
extern bool Gravity;
extern bool button;

extern int MP3_shot;
extern int MP3_jump;
extern int MP3_gameover;
extern int MP3_change;
extern int MP3_bgm;
extern int MP3_shoot;
extern bool fin_flag;
int MP3_gameover_bgm=OPENMP3("gameover_bgm.mp3");
int key;

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
void InitPlayer(void)
{
	// �v���C���[�̏�񏉊���
	g_player.fPosX =5.0f;
	g_player.fPosY = 0.0f;
	g_player.fPosXOld = 5.0f;
	g_player.fPosYOld = 23.0f;
	g_player.fMoveX = 0.0f;
	g_player.fMoveY = 0.0f;
	g_player.bJump = false;
	g_player.bLand = false;
	g_player.bShot = false;
	g_player.bMove = false;
	g_player.bGravity = false;
	g_player.fDirect = 1.0f;
	g_player.pField = NULL;
	g_player.count = 0;

}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void TermPlayer(void)
{
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void UpdatePlayer(int *flag)
{
	int count=0;
	float shot_x=1;
	float shot_y=1;
	int i,j;
	

	char change1_1[8][100]={"          ����������������             ",
							"         ��������������������           ",
							"       ����                ����         ",
						    "     ����                   ����        ",
							"   ����                    ����������   ",
							"   ����                      ������     ",
							"  ����                        ����      ",
							"  ����                         ��       "};





	char change2_1[50][100]={"     ��                         ����  ",
							 "    ����                        ����  ",
							 "   ������                      ����   ",
						     " ����������                    ����   ",
							 "     ����                    ����     ",
							 "      ����                  ����      ",
							 "        ����������������������        ",
							 "          ������������������          "};



		
	// �O��̈ʒu��ۑ�
	g_player.fPosXOld = g_player.fPosX;
	g_player.fPosYOld = g_player.fPosY;


	if(g_player.pField != NULL)
	{// �n�ʂ̏�ɏ���Ă���ꍇ
		g_player.fPosX += (g_player.pField->fPosX - g_player.pField->fPosXOld);
		g_player.fPosY += (g_player.pField->fPosY - g_player.pField->fPosYOld);
	}

if(*flag==0)
 {

	if(INP(PK_B))
		{// �U��
			while(INP(PK_B))
			{

				if(count%60001==20000)
				{
					shot_x=1;
					shot_y=1;

					for(i=0;i<6;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i*4), (int)(g_player.fPosY - 1.0f-i));
					printf("  ");
					}
					for(i=0;i<10;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i), (int)(g_player.fPosY - 1.0f-i));
					printf("��");
					}

				}
				if(count%60001==40000)
				{
					shot_x=1;
					shot_y=0.5;

					for(i=0;i<10;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i), (int)(g_player.fPosY - 1.0f-i));
					printf("  ");
					}

					for(i=0;i<6;i++)
					{
					LOCATE((int)(g_player.fPosX+2+i*2), (int)(g_player.fPosY - 1.0f-i));
					printf("��");
					}
			}
			if(count%60001==60000)
			{
				shot_x=2;
				shot_y=0.5;

				for(i=0;i<6;i++)
				{
				LOCATE((int)(g_player.fPosX+2+i*2), (int)(g_player.fPosY - 1.0f-i));
				printf("  ");
				}

				for(i=0;i<6;i++)
				{
				LOCATE((int)(g_player.fPosX+2+i*4), (int)(g_player.fPosY - 1.0f-i));
				printf("��");
				}
			}
			count++;
		}

		if(!g_player.bShot)
		{
			if(g_player.fPosX >= 3.0f && g_player.fPosX <= 77.0f)
			{
				if(*flag==0)
				{
					// �e�̐ݒ�
					SetBullet(g_player.fPosX, g_player.fPosY
						, g_player.fDirect, 0.0f,g_player.bGravity,
						&g_player.fPosX,&g_player.fPosY,g_player.fDirect,shot_x,shot_y);
					g_player.bShot = true;
					PLAYMP3(MP3_shoot);
					*flag=1;
					count=0;
				}
			}
		}
	}
	else
	{
		if(g_player.bShot)
		{// �V���b�g��
			if(*flag==0)
			{
				g_player.bShot = false;
			}
		}
	}
 }	
	
	if(*flag==0)
	{
		if(INP(PK_A))
		{// ���ړ�
			if(g_player.bJump == true)
			{
				g_player.fMoveX -= VALUE_MOVE_X_AIR;
			}
			else
			{
				g_player.fMoveX -= VALUE_MOVE_X;
			}
				g_player.bMove = true;

				g_player.fDirect = -1.0f;
		}

		if(INP(PK_D))
		{// �E�ړ�
			if(g_player.bJump == true)
			{
				g_player.fMoveX += VALUE_MOVE_X_AIR;
			}
			else
			{
				g_player.fMoveX += VALUE_MOVE_X;
			}
			g_player.bMove = true;

			g_player.fDirect = 1.0f;
		}

		if(INP(PK_SP))
		{
			// �W�����v
			if(g_player.bGravity == false)
			{
				if(g_player.bJump == false)
				{
					PLAYMP3(MP3_jump);
					g_player.fMoveY = -VALUE_JUMP;
					g_player.bJump = true;
				}
			}
			else
			{
				if(g_player.bJump == false)
				{
					PLAYMP3(MP3_jump);
					g_player.fMoveY = +VALUE_JUMP;
					g_player.bJump = true;
				}
			}
		}


		if(INP(PK_Q))
		{
			PLAYMP3(MP3_change);
			for(j=0;j<2;j++)
			{
				if(j%2==0)
				{
					COLOR(BLUE);
				}
				else
				{
					COLOR(CORAL);
				}
				for(i=0;i<8;i++)
				{
					LOCATE(21,5+i);
					printf("%s",&change1_1[i][0]);
					LOCATE(34,13);
					printf("�n��");
				}
				if(j%2==0)
				{
					COLOR(CORAL);
				}
				else
				{
					COLOR(BLUE);
				}
				for(i=0;i<8;i++)
				{
					LOCATE(20,14+i);
					printf("%s",&change2_1[i][0]);
					LOCATE(38,13);
					printf("���]");
				}
				Sleep(500);
			}
				system("cls");

				
				if(g_player.count>=15)
				{
					if(g_player.bGravity == false)
					{
						g_player.bGravity = true;
						LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
						printf("�@");
						Gravity=true;	
				}
					else
					{
						g_player.bGravity = false;
						LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
						printf("�@");
						Gravity=false;
					}
					g_player.count=0;
				}

			}
		}
	
	// �ړ��ʍX�V
	if(g_player.bJump)
	{// �W�����v��
		g_player.bMove = true;

		g_player.fMoveX += (0.0f - g_player.fMoveX) * VALUE_RESIST_X_AIR;		// ��R��������
	}
	else
	{
		g_player.fMoveX += (0.0f - g_player.fMoveX) * VALUE_RESIST_X;			// ��R��������
	}


 

 if(*flag==0)
 {
	if(g_player.bGravity == false)
	{
		g_player.fMoveY += VALUE_GRAVITY;			// �d�͂�������
	}
	else
	{
		g_player.fMoveY -= VALUE_GRAVITY;
	}
 }



 if(*flag==0)
 {
	// �ʒu�X�V
	g_player.fPosX += g_player.fMoveX;
	if(g_player.fPosX < LIMIT_LEFT)
	{// ���[�𒴂����ꍇ
		g_player.fPosX = LIMIT_LEFT;
	}
	if(g_player.fPosX > LIMIT_RIGHT)
	{// �E�[�𒴂����ꍇ
		g_player.fPosX = LIMIT_RIGHT;
	}
	
	g_player.fPosY += g_player.fMoveY;
 }

	
	CheckCollisionField2();
	CheckCollisionField3();


	if(CheckCollisionField() == true)
	{// �n�ʂɂ߂荞��
		g_player.bMove = true;
		g_player.fMoveY = 0.0f;
		g_player.bJump = false;
		g_player.bLand = true;
	}
	else
	{

		if(g_player.bLand)
		{	
			g_player.bJump = true;
			g_player.bLand = false;
		}
	}

	if((g_player.fPosX==GOAL_X)&&(g_player.fPosY==GOAL_Y))
	{
		system("cls");
		getchar();
	}


	atarihanntei();
	g_player.count++;
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void DrawPlayer(int *flag)
{
	// �F�ݒ�
	COLOR(YELLOW);

	if(g_player.bMove)
	{// �ړ������ꍇ
		// �O��̈ʒu�ł̃v���C���[������
		if(g_player.bGravity==false)
		{
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
			printf("�@");
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld - 1.0f));
			printf("�@");
		}
		else
		{
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld));
			printf("�@");
			LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld - 1.0f));
			printf("�@");

			if(g_player.bJump == true)
			{
				LOCATE((int)(g_player.fPosXOld), (int)(g_player.fPosYOld + 1.0f));
				printf("�@");
			}
		}


		g_player.bMove = false;
	}

	// ���݂̈ʒu�v���C���[��\��
	if(g_player.bGravity==false)
	{
		COLOR(CORAL);
		LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY));
		printf("��");
		COLOR(BLUE);
		if(*flag==false)
		{
			LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
			printf("��");
		}
	}
	else
	{
		if(*flag==0)
		{
			COLOR(BLUE);
			LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY));
			printf("��");
		}
		COLOR(CORAL);
		LOCATE((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
		printf("��");
	}


}

//=============================================================================
// �n�ʂƂ̓����蔻��
//=============================================================================
bool CheckCollisionField(void)
{
	FIELD *pField;

	// �n�ʂ��擾
	pField = GetField();

	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
			if(pField->bUse == true)
			{

				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{// �n�ʂ̕��͈͓̔�
					if(g_player.fPosY > (pField->fPosY - 1.0f) && g_player.fPosYOld <= (pField->fPosY - 1.0f))
					{// �������n�ʂɂ߂荞�񂾏ꍇ
						g_player.fPosY = pField->fPosY - 1.0f;
						g_player.pField = pField;
						return true;
						
					}
				}

				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{
					// �n�ʂ̕��͈͓̔�
					if((g_player.fPosY - 2.0f) < pField->fPosY && (g_player.fPosYOld - 1.0f) >= pField->fPosY)
					{
						// �����n�ʂɂ߂荞�񂾏ꍇ
						g_player.fPosY = pField->fPosY + 2.0f;
						g_player.fMoveY = 0.0f;

						if(g_player.bGravity==true)
						{
							return true;
						}
					}
				}
			}


	}
	
		return false;
}


void CheckCollisionField2(void)
{
	FIELD2 *pField;


int k,j;

	char Y[5][20]={" ��     ��",
				   "  ��   �� ",
				   "   ����  ",
				   "    ��   ",
				   "    ��   "};

	char o[5][20]={"         ",
				   "   ����  ",
		           " ��    ��",
				   " ��    ��",
				   "   ����  "};

	char u[5][20]={"        ",
				   "��    ��",
				   "��    ��",
				   "��    ��",
				   "  ����  "};
	
	char D[5][20]={"������   ",
		           "��    �� ",
				   "��    �� ",
				   "��    �� ",
				   "������   "};

	char i[5][20]={"        ",
				   "   ��   ",
				   "        ",
				   "   ��   ",
				   "   ��   "};

	char e[5][20]={"          ",
				   "   ����   ",
				   "  ������  ",
				   "  ��      ",
				   "   ����   " };

	char d[5][20]={"     ��",
				   "     ��",
				   "   ����",
				   "  �� ��",
				   "   ����"};

	// �n�ʂ��擾
	pField = GetField2();

	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
			if(pField->bUse == true)
			{
				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{// �n�ʂ̕��͈͓̔�
					if((int)g_player.fPosY-1 == (pField->fPosY))
					{
						CLOSEMP3(MP3_bgm);
						PLAYMP3(MP3_gameover);
						PLAYMP3(MP3_gameover_bgm);
						system("CLS");
						fin_flag=true;
						COLOR(CORAL);
						for(k=0;k<5;k++)
						{
							LOCATE(8,3+k);
							printf("%s",&Y[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(20,6+k);
							printf("%s",&o[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(33,3+k);
							printf("%s",&u[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(25,16+k);
							printf("%s",&D[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(35,12+k);
							printf("%s",&i[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(45,14+k);
							printf("%s",&e[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(55,17+k);
							printf("%s",&d[k][0]);
						}
						Sleep(SP);
						for(k=0;k<10;k+=4)
						{
							LOCATE(66+k,20);
							printf("��");
							Sleep(SP);
						}
						rewind(stdin);
						getchar();
					}
				}

			}


	}

}


void CheckCollisionField3(void)
{
int k,j;

	char Y[5][20]={" ��     ��",
				   "  ��   �� ",
				   "   ����  ",
				   "    ��   ",
				   "    ��   "};

	char o[5][20]={"         ",
				   "   ����  ",
		           " ��    ��",
				   " ��    ��",
				   "   ����  "};

	char u[5][20]={"        ",
				   "��    ��",
				   "��    ��",
				   "��    ��",
				   "  ����  "};
	
	char D[5][20]={"������   ",
		           "��    �� ",
				   "��    �� ",
				   "��    �� ",
				   "������   "};

	char i[5][20]={"        ",
				   "   ��   ",
				   "        ",
				   "   ��   ",
				   "   ��   "};

	char e[5][20]={"          ",
				   "   ����   ",
				   "  ������  ",
				   "  ��      ",
				   "   ����   " };

	char d[5][20]={"     ��",
				   "     ��",
				   "   ����",
				   "  �� ��",
				   "   ����"};
	FIELD4 *pField;

	// �n�ʂ��擾
	pField = GetField4();

	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
			if(pField->bUse == true)
			{
				if((g_player.fPosX + 0.9f) > pField->fPosX && g_player.fPosX < (pField->fPosX + pField->fWidth - 0.1f))
				{// �n�ʂ̕��͈͓̔�
					if((int)g_player.fPosY == (pField->fPosY ))
					{// �������n�ʂɂ߂荞�񂾏ꍇ

						fin_flag=true;
						CLOSEMP3(MP3_bgm);
						PLAYMP3(MP3_gameover);
						system("CLS");
						PLAYMP3(MP3_gameover_bgm);
						COLOR(CORAL);
						for(k=0;k<5;k++)
						{
							LOCATE(8,3+k);
							printf("%s",&Y[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(20,6+k);
							printf("%s",&o[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(33,3+k);
							printf("%s",&u[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(25,16+k);
							printf("%s",&D[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(35,12+k);
							printf("%s",&i[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(45,14+k);
							printf("%s",&e[k][0]);
						}
						Sleep(SP);
						for(k=0;k<5;k++)
						{
							LOCATE(55,17+k);
							printf("%s",&d[k][0]);
						}
						Sleep(SP);
						for(k=0;k<10;k+=4)
						{
							LOCATE(66+k,20);
							printf("��");
							Sleep(SP);
						}
						rewind(stdin);
						getchar();
						CLS();
					}
				}
				
			}


	}

}

//�ǂƂ̓����蔻��

void atarihanntei(void)
{
	FIELD *pField;
	pField = GetField();


	g_player.pField = NULL;
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
		if((pField->fPosX<=g_player.fPosX+1)&&(pField->fPosY==g_player.fPosY)&&
			(((pField->fPosX)+(pField->fWidth-1))>=(g_player.fPosX))&&
			(g_player.fDirect == 1.0f))
		{
			g_player.fPosX-=1;
			g_player.fMoveX = 0.0f;
			break;
		}
		else if((pField->fPosX<=g_player.fPosX+1)&&(pField->fPosY==g_player.fPosY)&&
			(((pField->fPosX)+(pField->fWidth))>=(g_player.fPosX))&&
			(g_player.fDirect == -1.0f))
		{
			g_player.fPosX+=1;
			g_player.fMoveX = 0.0f;
			break;
		}

	}
}



