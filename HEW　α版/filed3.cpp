//=============================================================================
//
// �n�ʂ̏���3 [field3.cpp]
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
FIELD3 g_aField3[MAX_FIELD];			// �n�ʂ̏��
extern bool button;
extern int stage;
//=============================================================================
// �n�ʂ̏���������
//=============================================================================
void InitField3(void)
{

	// �n�ʂ̏�񏉊���
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField3[nCntField].fPosX = 0.0f;
		g_aField3[nCntField].fPosY = 0.0f;
		g_aField3[nCntField].fPosXOld = 0.0f;
		g_aField3[nCntField].fPosYOld = 0.0f;
		g_aField3[nCntField].fWidth = 0.0f;
		g_aField3[nCntField].fMoveX = 0.0f;
		g_aField3[nCntField].fMoveY = 0.0f;
		g_aField3[nCntField].bMove = false;
		g_aField3[nCntField].bUse = false;
	}

	if(stage==1)
	{

		// �n�ʂ̐ݒ�(������)
		SetField3(15.0f, 6.0f, 18.0f, 0.0f, 0.0f);

	}

	if(stage==2)
	{

		SetField3(30.0f, 3.0f, 12.0f, 0.0f, 0.0f);
		SetField3(66.0f, 8.0f, 12.0f, 0.0f, 0.0f);
	}





}

//=============================================================================
// �n�ʂ̏I������
//=============================================================================
void TermField3(void)
{
}

//=============================================================================
// �n�ʂ̍X�V����
//=============================================================================
void UpdateField3(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField3[nCntField].bUse == true)
		{
			if(g_aField3[nCntField].bMove == true)
			{
				// �O��̈ʒu��ۑ�
				g_aField3[nCntField].fPosXOld = g_aField3[nCntField].fPosX;
				g_aField3[nCntField].fPosYOld = g_aField3[nCntField].fPosY;

				// �ʒu���X�V
				g_aField3[nCntField].fPosX += g_aField3[nCntField].fMoveX;
				g_aField3[nCntField].fPosY += g_aField3[nCntField].fMoveY;

				g_aField3[nCntField].nCount++;
				if(g_aField3[nCntField].nCount >= 100)
				{// ��莞�Ԍo��
					g_aField3[nCntField].fMoveX *= -1.0f;
					g_aField3[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// �n�ʂ̕`�揈��
//=============================================================================
void DrawField3(void)
{
	// �F�̐ݒ�
	COLOR(YELLOW);

	// �n�ʂ̕\��
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField3[nCntField].bUse == true)
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
			LOCATE((int)g_aField3[nCntField].fPosX, (int)g_aField3[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField3[nCntField].fWidth / 2; nCntBlock++)
			{
				if(button==false)
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
void SetField3(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField3[nCntField].bUse == false)
		{
			g_aField3[nCntField].fPosX =
			g_aField3[nCntField].fPosXOld = fPosX;
			g_aField3[nCntField].fPosY =
			g_aField3[nCntField].fPosYOld = fPosY;
			g_aField3[nCntField].fWidth = fWidth;
			g_aField3[nCntField].fMoveX = fMoveX;
			g_aField3[nCntField].fMoveY = fMoveY;
			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField3[nCntField].bMove = false;
			}
			else
			{
				g_aField3[nCntField].bMove = true;
			}
			g_aField3[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �n�ʂ̎擾
//=============================================================================
FIELD3 *GetField3(void)
{
	return &g_aField3[0];
}