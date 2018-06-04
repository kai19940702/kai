//=============================================================================
//
// �n�ʂ̏��� [field.cpp]
//
//=============================================================================
#include "main.h"
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
FIELD g_aField[MAX_FIELD];			// �n�ʂ̏��
extern int stage;
//=============================================================================
// �n�ʂ̏���������
//=============================================================================
void InitField(void)
{

	// �n�ʂ̏�񏉊���
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField[nCntField].fPosX = 0.0f;
		g_aField[nCntField].fPosY = 0.0f;
		g_aField[nCntField].fPosXOld = 0.0f;
		g_aField[nCntField].fPosYOld = 0.0f;
		g_aField[nCntField].fWidth = 0.0f;
		g_aField[nCntField].fMoveX = 0.0f;
		g_aField[nCntField].fMoveY = 0.0f;
		g_aField[nCntField].bMove = false;
		g_aField[nCntField].bUse = false;
	}

	if(stage==1)
	{
		// �n�ʂ̐ݒ�(������)
		SetField(2.0f, 2.0f, 78.0f, 0.0f, 0.0f);
		SetField(10.0f, 5.0f, 60.0f, 0.0f, 0.0f);
		SetField(2.0f, 24.0f, 78.0f, 0.0f, 0.0f);
		SetField(44.0f, 24.0f, 38.0f, 0.0f, 0.0f);
		SetField(68.0f, 8.0f, 12.0f, 0.0f, 0.0f);
		SetField(15.0f, 10.0f, 18.0f, 0.0f, 0.0f);
		SetField(36.0f, 15.0f, 18.0f, 0.0f, 0.0f);
		SetField(19.0f, 20.0f, 18.0f, 0.0f, 0.0f);
		SetField(19.0f, 19.0f, 2.0f, 0.0f, 0.0f);
		SetField(19.0f, 18.0f, 2.0f, 0.0f, 0.0f);
		SetField(19.0f, 17.0f, 2.0f, 0.0f, 0.0f);
		SetField(19.0f, 16.0f, 2.0f, 0.0f, 0.0f);
		SetField(72.0f, 19.0f, 8.0f, 0.0f, 0.0f); 
		SetField(16.0f, 23.0f, 2.0f, 0.0f, 0.0f);
		SetField(44.0f, 23.0f, 2.0f, 0.0f, 0.0f);
		SetField(68.0f, 9.0f, 2.0f, 0.0f, 0.0f);
		SetField(68.0f, 10.0f, 2.0f, 0.0f, 0.0f);
		SetField(70.0f, 19.0f, 2.0f, 0.0f, 0.0f);
		SetField(70.0f, 18.0f, 2.0f, 0.0f, 0.0f);
		SetField(70.0f, 17.0f, 2.0f, 0.0f, 0.0f);
	}

	if(stage==2)
	{
		SetField(2.0f, 10.0f, 16.0f, 0.0f, 0.0f);
		SetField(32.0f, 10.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 9.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 8.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 7.0f, 2.0f, 0.0f, 0.0f);
		SetField(32.0f, 6.0f, 10.0f, 0.0f, 0.0f);
		SetField(48.0f, 2.0f, 17.0f, 0.0f, 0.0f);	
		SetField(2.0f, 2.0f, 22.0f, 0.0f, 0.0f);
		SetField(26.0f, 2.0f, 20.0f, 0.0f, 0.0f);
		SetField(65.0f, 16.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 17.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 18.0f, 2.0f, 0.0f, 0.0f); 
		SetField(65.0f, 19.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 20.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 21.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 22.0f, 2.0f, 0.0f, 0.0f);
		SetField(65.0f, 23.0f, 2.0f, 0.0f, 0.0f);
		SetField(2.0f, 24.0f, 78.0f, 0.0f, 0.0f);
		SetField(2.0f, 17.0f, 48.0f, 0.0f, 0.0f); 
		SetField(34.0f, 12.0f, 16.0f, 0.0f, 0.0f); 
		SetField(34.0f, 12.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 13.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 14.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 15.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 16.0f, 2.0f, 0.0f, 0.0f); 
		SetField(34.0f, 17.0f, 2.0f, 0.0f, 0.0f); 
		SetField(72.0f, 19.0f, 8.0f, 0.0f, 0.0f); 
	}

	
}

//=============================================================================
// �n�ʂ̏I������
//=============================================================================
void TermField(void)
{
}

//=============================================================================
// �n�ʂ̍X�V����
//=============================================================================
void UpdateField(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField[nCntField].bUse == true)
		{
			if(g_aField[nCntField].bMove == true)
			{
				// �O��̈ʒu��ۑ�
				g_aField[nCntField].fPosXOld = g_aField[nCntField].fPosX;
				g_aField[nCntField].fPosYOld = g_aField[nCntField].fPosY;

				// �ʒu���X�V
				g_aField[nCntField].fPosX += g_aField[nCntField].fMoveX;
				g_aField[nCntField].fPosY += g_aField[nCntField].fMoveY;

				g_aField[nCntField].nCount++;
				if(g_aField[nCntField].nCount >= 100)
				{// ��莞�Ԍo��
					g_aField[nCntField].fMoveX *= -1.0f;
					g_aField[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// �n�ʂ̕`�揈��
//=============================================================================
void DrawField(void)
{
	// �F�̐ݒ�
	COLOR(WHITE);

	// �n�ʂ̕\��
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField[nCntField].bUse == true)
		{
#if 0	// ���̂܂܂��Əd���c
			LOCATE((int)g_aField[nCntField].fPosX, (int)g_aField[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField[nCntField].fWidth / 2; nCntBlock++)
			{
				printf("��");
			}
#else	// ��������ƌy���Ȃ�c
			char aBuf[80];

			strcpy(&aBuf[0], "\0");
			LOCATE((int)g_aField[nCntField].fPosX, (int)g_aField[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField[nCntField].fWidth / 2; nCntBlock++)
			{
				strcat(&aBuf[0], "��");
			}
			printf("%s", &aBuf[0]);
#endif
		}
	}

}

//=============================================================================
// �n�ʂ̐ݒ�
//=============================================================================
void SetField(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField[nCntField].bUse == false)
		{
			g_aField[nCntField].fPosX =
			g_aField[nCntField].fPosXOld = fPosX;
			g_aField[nCntField].fPosY =
			g_aField[nCntField].fPosYOld = fPosY;
			g_aField[nCntField].fWidth = fWidth;
			g_aField[nCntField].fMoveX = fMoveX;
			g_aField[nCntField].fMoveY = fMoveY;
			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField[nCntField].bMove = false;
			}
			else
			{
				g_aField[nCntField].bMove = true;
			}
			g_aField[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �n�ʂ̎擾
//=============================================================================
FIELD *GetField(void)
{
	return &g_aField[0];
}
