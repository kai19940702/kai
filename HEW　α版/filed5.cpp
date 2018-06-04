//=============================================================================
//
// �n�ʂ̏���5 [field5.cpp]
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
FIELD5 g_aField5[MAX_FIELD];			// �n�ʂ̏��
extern bool button;
extern int stage;

//=============================================================================
// �n�ʂ̏���������
//=============================================================================
void InitField5(void)
{

	// �n�ʂ̏�񏉊���
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField5[nCntField].fPosX = 0.0f;
		g_aField5[nCntField].fPosY = 0.0f;
		g_aField5[nCntField].fPosXOld = 0.0f;
		g_aField5[nCntField].fPosYOld = 0.0f;
		g_aField5[nCntField].fWidth = 0.0f;
		g_aField5[nCntField].fMoveX = 0.0f;
		g_aField5[nCntField].fMoveY = 0.0f;
		g_aField5[nCntField].bMove = false;
		g_aField5[nCntField].bUse = false;
	}

	if(stage==1)
	{
	// �n�ʂ̐ݒ�(������)
	SetField5(72.0f, 18.0f, 8.0f, 0.0f, 0.0f);
	}
	else
	{
	SetField5(36.0f, 16.0f, 14.0f, 0.0f, 0.0f);
	SetField5(3.0f, 3.0f, 14.0f, 0.0f, 0.0f);
	}


}

//=============================================================================
// �n�ʂ̏I������
//=============================================================================
void TermField5(void)
{
}

//=============================================================================
// �n�ʂ̍X�V����
//=============================================================================
void UpdateField5(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField5[nCntField].bUse == true)
		{
			if(g_aField5[nCntField].bMove == true)
			{
				// �O��̈ʒu��ۑ�
				g_aField5[nCntField].fPosXOld = g_aField5[nCntField].fPosX;
				g_aField5[nCntField].fPosYOld = g_aField5[nCntField].fPosY;

				// �ʒu���X�V
				g_aField5[nCntField].fPosX += g_aField5[nCntField].fMoveX;
				g_aField5[nCntField].fPosY += g_aField5[nCntField].fMoveY;

				g_aField5[nCntField].nCount++;
				if(g_aField5[nCntField].nCount >= 100)
				{// ��莞�Ԍo��
					g_aField5[nCntField].fMoveX *= -1.0f;
					g_aField5[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// �n�ʂ̕`�揈��
//=============================================================================
void DrawField5(void)
{
	// �F�̐ݒ�
	COLOR(YELLOW);

	// �n�ʂ̕\��
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField5[nCntField].bUse == true)
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
			LOCATE((int)g_aField5[nCntField].fPosX, (int)g_aField5[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField5[nCntField].fWidth / 2; nCntBlock++)
			{
				if(button==true)
				{
				strcat(&aBuf[0], "��");
				}
				else
				{
					strcat(&aBuf[0], "��");
				}
			}
			printf("%s", &aBuf[0]);
#endif
		}
	}

}

//=============================================================================
// �n�ʂ̐ݒ�
//=============================================================================
void SetField5(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField5[nCntField].bUse == false)
		{
			g_aField5[nCntField].fPosX =
			g_aField5[nCntField].fPosXOld = fPosX;
			g_aField5[nCntField].fPosY =
			g_aField5[nCntField].fPosYOld = fPosY;
			g_aField5[nCntField].fWidth = fWidth;
			g_aField5[nCntField].fMoveX = fMoveX;
			g_aField5[nCntField].fMoveY = fMoveY;
			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField5[nCntField].bMove = false;
			}
			else
			{
				g_aField5[nCntField].bMove = true;
			}
			g_aField5[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �n�ʂ̎擾
//=============================================================================
FIELD5 *GetField5(void)
{
	return &g_aField5[0];
}