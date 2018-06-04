//=============================================================================
//
// �n�ʂ̏���4 [field4.cpp]
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
FIELD4 g_aField4[MAX_FIELD];			// �n�ʂ̏��
extern int stage;
//=============================================================================
// �n�ʂ̏���������
//=============================================================================
void InitField4(void)
{

	// �n�ʂ̏�񏉊���
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField4[nCntField].fPosX = 0.0f;
		g_aField4[nCntField].fPosY = 0.0f;
		g_aField4[nCntField].fPosXOld = 0.0f;
		g_aField4[nCntField].fPosYOld = 0.0f;
		g_aField4[nCntField].fWidth = 0.0f;
		g_aField4[nCntField].fMoveX = 0.0f;
		g_aField4[nCntField].fMoveY = 0.0f;
		g_aField4[nCntField].bMove = false;
		g_aField4[nCntField].bUse = false;
	}

	if(stage==1)
	{
	// �n�ʂ̐ݒ�(������)
	SetField4(18.0f, 23.0f, 26.0f, 0.0f, 0.0f);
	}
	else
	{
	SetField4(63.0f, 23.0f, 2.0f, 0.0f, 0.0f);
	SetField4(34.0f, 11.0f, 2.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �n�ʂ̏I������
//=============================================================================
void TermField4(void)
{
}

//=============================================================================
// �n�ʂ̍X�V����
//=============================================================================
void UpdateField4(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField4[nCntField].bUse == true)
		{
			if(g_aField4[nCntField].bMove == true)
			{
				// �O��̈ʒu��ۑ�
				g_aField4[nCntField].fPosXOld = g_aField4[nCntField].fPosX;
				g_aField4[nCntField].fPosYOld = g_aField4[nCntField].fPosY;

				// �ʒu���X�V
				g_aField4[nCntField].fPosX += g_aField4[nCntField].fMoveX;
				g_aField4[nCntField].fPosY += g_aField4[nCntField].fMoveY;

				g_aField4[nCntField].nCount++;
				if(g_aField4[nCntField].nCount >= 100)
				{// ��莞�Ԍo��
					g_aField4[nCntField].fMoveX *= -1.0f;
					g_aField4[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// �n�ʂ̕`�揈��
//=============================================================================
void DrawField4(void)
{
	// �F�̐ݒ�
	COLOR(CORAL);

	// �n�ʂ̕\��
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField4[nCntField].bUse == true)
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
			LOCATE((int)g_aField4[nCntField].fPosX, (int)g_aField4[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField4[nCntField].fWidth / 2; nCntBlock++)
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
void SetField4(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField4[nCntField].bUse == false)
		{
			g_aField4[nCntField].fPosX =
			g_aField4[nCntField].fPosXOld = fPosX;
			g_aField4[nCntField].fPosY =
			g_aField4[nCntField].fPosYOld = fPosY;
			g_aField4[nCntField].fWidth = fWidth;
			g_aField4[nCntField].fMoveX = fMoveX;
			g_aField4[nCntField].fMoveY = fMoveY;
			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField4[nCntField].bMove = false;
			}
			else
			{
				g_aField4[nCntField].bMove = true;
			}
			g_aField4[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �n�ʂ̎擾
//=============================================================================
FIELD4 *GetField4(void)
{
	return &g_aField4[0];
}