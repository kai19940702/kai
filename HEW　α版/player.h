//=============================================================================
//
// �v���C���[�̏��� [player.h]
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "field.h"



//*************************************
// �v���C���[�̍\����
//*************************************
typedef struct
{
	float fPosX;		// ���݂̈ʒu(�w���W)
	float fPosY;		// ���݂̈ʒu(�x���W)
	float fPosXOld;		// �O��̈ʒu(�w���W)
	float fPosYOld;		// �O��̈ʒu(�x���W)
	float fMoveX;		// �ړ���(�w����)
	float fMoveY;		// �ړ���(�x����)
	int count;
	bool bJump;			// �W�����v�����ǂ���
	bool bGravity;
	bool bLand;// ���n�����ǂ���
	bool bMove;			// �ړ��������ǂ���(�`��X�V�p)
	bool bShot;			// �V���b�g�����ǂ���
	float fDirect;		// ����
	FIELD *pField;		// �n�ʂւ̃|�C���^
	FIELD2 *pField2;
} PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void TermPlayer(void);
void UpdatePlayer(int *falg);
void DrawPlayer(int *flag);

#endif