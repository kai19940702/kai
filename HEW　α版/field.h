//=============================================================================
//
// �n�ʂ̏��� [field.h]
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_FIELD		(40)		// �n�ʂ̍ő吔

//*************************************
// �n�ʂ̍\����
//*************************************
typedef struct
{
	float fPosX;		// �n�ʂ̊�ʒu(�w���W)
	float fPosY;		// �n�ʂ̊�ʒu(�x���W)
	float fPosXOld;		// �n�ʂ̑O��̈ʒu(�w���W)
	float fPosYOld;		// �n�ʂ̑O��̈ʒu(�x���W)
	float fWidth;		// �n�ʂ̕�
	float fMoveX;		// �n�ʂ̈ړ���(�w����)
	float fMoveY;		// �n�ʂ̈ړ���(�x����)
	int nCount;			// �J�E���^�[
	bool bMove;			// �n�ʂ��ړ����Ă��邩�ǂ���
	bool bUse;			// �n�ʂ��g�p���Ă��邩�ǂ���
} FIELD;

typedef struct
{
	float fPosX;		// �n�ʂ̊�ʒu(�w���W)
	float fPosY;		// �n�ʂ̊�ʒu(�x���W)
	float fPosXOld;		// �n�ʂ̑O��̈ʒu(�w���W)
	float fPosYOld;		// �n�ʂ̑O��̈ʒu(�x���W)
	float fWidth;		// �n�ʂ̕�
	float fMoveX;		// �n�ʂ̈ړ���(�w����)
	float fMoveY;		// �n�ʂ̈ړ���(�x����)
	int nCount;			// �J�E���^�[
	bool bMove;			// �n�ʂ��ړ����Ă��邩�ǂ���
	bool bUse;			// �n�ʂ��g�p���Ă��邩�ǂ���
} FIELD2;

typedef struct
{
	float fPosX;		// �n�ʂ̊�ʒu(�w���W)
	float fPosY;		// �n�ʂ̊�ʒu(�x���W)
	float fPosXOld;		// �n�ʂ̑O��̈ʒu(�w���W)
	float fPosYOld;		// �n�ʂ̑O��̈ʒu(�x���W)
	float fWidth;		// �n�ʂ̕�
	float fMoveX;		// �n�ʂ̈ړ���(�w����)
	float fMoveY;		// �n�ʂ̈ړ���(�x����)
	int nCount;			// �J�E���^�[
	bool bMove;			// �n�ʂ��ړ����Ă��邩�ǂ���
	bool bUse;			// �n�ʂ��g�p���Ă��邩�ǂ���
} FIELD3;

typedef struct
{
	float fPosX;		// �n�ʂ̊�ʒu(�w���W)
	float fPosY;		// �n�ʂ̊�ʒu(�x���W)
	float fPosXOld;		// �n�ʂ̑O��̈ʒu(�w���W)
	float fPosYOld;		// �n�ʂ̑O��̈ʒu(�x���W)
	float fWidth;		// �n�ʂ̕�
	float fMoveX;		// �n�ʂ̈ړ���(�w����)
	float fMoveY;		// �n�ʂ̈ړ���(�x����)
	int nCount;			// �J�E���^�[
	bool bMove;			// �n�ʂ��ړ����Ă��邩�ǂ���
	bool bUse;			// �n�ʂ��g�p���Ă��邩�ǂ���
} FIELD4;

typedef struct
{
	float fPosX;		// �n�ʂ̊�ʒu(�w���W)
	float fPosY;		// �n�ʂ̊�ʒu(�x���W)
	float fPosXOld;		// �n�ʂ̑O��̈ʒu(�w���W)
	float fPosYOld;		// �n�ʂ̑O��̈ʒu(�x���W)
	float fWidth;		// �n�ʂ̕�
	float fMoveX;		// �n�ʂ̈ړ���(�w����)
	float fMoveY;		// �n�ʂ̈ړ���(�x����)
	int nCount;			// �J�E���^�[
	bool bMove;			// �n�ʂ��ړ����Ă��邩�ǂ���
	bool bUse;			// �n�ʂ��g�p���Ă��邩�ǂ���
} FIELD5;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitField(void);
void TermField(void);
void UpdateField(void);
void DrawField(void);
void InitField2(void);
void TermField2(void);
void UpdateField2(void);
void DrawField2(void);
void InitField3(void);
void TermField3(void);
void UpdateField3(void);
void DrawField3(void);
void InitField4(void);
void TermField4(void);
void UpdateField4(void);
void DrawField4(void);
void InitField5(void);
void TermField5(void);
void UpdateField5(void);
void DrawField5(void);

void SetField(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD *GetField(void);

void SetField2(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD2 *GetField2(void);

void SetField3(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD3 *GetField3(void);

void SetField4(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD4 *GetField4(void);

void SetField5(float fPosX, float fPosY, float fWidth, float fMoveX, float fMoveY);
FIELD5 *GetField5(void);

#endif

