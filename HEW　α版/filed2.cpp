//=============================================================================
//
// �n�ʂ̏���2 [field2.cpp]
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
FIELD2 g_aField2[MAX_FIELD];			// �n�ʂ̏��
extern int stage;
//=============================================================================
// �n�ʂ̏���������
//=============================================================================
void InitField2(void)
{
	// �n�ʂ̏�񏉊���
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField2[nCntField].fPosX = 0.0f;
		g_aField2[nCntField].fPosY = 0.0f;
		g_aField2[nCntField].fPosXOld = 0.0f;
		g_aField2[nCntField].fPosYOld = 0.0f;
		g_aField2[nCntField].fWidth = 0.0f;
		g_aField2[nCntField].fMoveX = 0.0f;
		g_aField2[nCntField].fMoveY = 0.0f;
		g_aField2[nCntField].bMove = false;
		g_aField2[nCntField].bUse = false;
	}

	if(stage==1)
	{
		// �n�ʂ̐ݒ�
		SetField2(10.0f, 6.0f, 4.0f, 0.0f, 0.0f);
		SetField2(15.0f, 11.0f, 18.0f, 0.0f, 0.0f);
		SetField2(36.0f, 16.0f, 18.0f, 0.0f, 0.0f);
		SetField2(68.0f, 6.0f, 2.0f, 0.0f, 0.0f);
		SetField2(68.0f, 7.0f, 2.0f, 0.0f, 0.0f);
	}
	else
	{
		SetField2(24.0f, 2.0f, 2.0f, 0.0f, 0.0f);
		SetField2(46.0f, 2.0f, 2.0f, 0.0f, 0.0f);
		SetField2(64.0f, 2.0f, 16.0f, 0.0f, 0.0f);
		SetField2(19.0f, 3.0f, 4.0f, 0.0f, 0.0f);
	}


}

//=============================================================================
// �n�ʂ̏I������
//=============================================================================
void TermField2(void)
{
}

//=============================================================================
// �n�ʂ̍X�V����
//=============================================================================
void UpdateField2(void)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField2[nCntField].bUse == true)
		{
			if(g_aField2[nCntField].bMove == true)
			{
				// �O��̈ʒu��ۑ�
				g_aField2[nCntField].fPosXOld = g_aField2[nCntField].fPosX;
				g_aField2[nCntField].fPosYOld = g_aField2[nCntField].fPosY;

				// �ʒu���X�V
				g_aField2[nCntField].fPosX += g_aField2[nCntField].fMoveX;
				g_aField2[nCntField].fPosY += g_aField2[nCntField].fMoveY;

				g_aField2[nCntField].nCount++;
				if(g_aField2[nCntField].nCount >= 100)
				{// ��莞�Ԍo��
					g_aField2[nCntField].fMoveX *= -1.0f;
					g_aField2[nCntField].nCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// �n�ʂ̕`�揈��
//=============================================================================
void DrawField2(void)
{
	// �F�̐ݒ�
	COLOR(CORAL);

	// �n�ʂ̕\��
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField2[nCntField].bUse == true)
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
			LOCATE((int)g_aField2[nCntField].fPosX, (int)g_aField2[nCntField].fPosY);
			for(int nCntBlock = 0; nCntBlock < (int)g_aField2[nCntField].fWidth / 2; nCntBlock++)
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
void SetField2(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY)
{
	for(int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if(g_aField2[nCntField].bUse == false)
		{
			g_aField2[nCntField].fPosX =
			g_aField2[nCntField].fPosXOld = fPosX;
			g_aField2[nCntField].fPosY =
			g_aField2[nCntField].fPosYOld = fPosY;
			g_aField2[nCntField].fWidth = fWidth;
			g_aField2[nCntField].fMoveX = fMoveX;
			g_aField2[nCntField].fMoveY = fMoveY;

			if(fMoveX > -0.001f && fMoveX < 0.001f
			&& fMoveY > -0.001f && fMoveY < 0.001f)
			{
				g_aField2[nCntField].bMove = false;
			}
			else
			{
				g_aField2[nCntField].bMove = true;
			}
			g_aField2[nCntField].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �n�ʂ̎擾
//=============================================================================
FIELD2 *GetField2(void)
{
	return &g_aField2[0];
}
