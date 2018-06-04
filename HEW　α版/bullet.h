//=============================================================================
//
// �e�̏��� [bullet.h]
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*************************************
// �e�̎��
//*************************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,		// �v���C���[�̒e
	BULLETTYPE_ENEMY,			// �G�̒e
	BULLETTYPE_MAX
} BULLETTYPE;

//*************************************
// �e�̍\����
//*************************************
typedef struct
{
	float fPosX;		// ���݂̈ʒu(�w���W)
	float fPosY;		// ���݂̈ʒu(�x���W)
	float fPosXOld;		// �O��̈ʒu(�w���W)
	float fPosYOld;		// �O��̈ʒu(�x���W)
	float fMoveX;		// �ړ���(�w����)
	float fMoveY;		// �ړ���(�x����)
	bool bUse;			// �g�p�����ǂ���
	bool gravity;
	float *player_x;
	float *player_y;
	float muki;
	float Shot_x;
	float Shot_y;

} BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void TermBullet(void);
void UpdateBullet(int *flag);
void DrawBullet(void);

void SetBullet(float fPosX, float fPosY, float fMoveX, float fMoveY,
	  bool Gravity,float *X,float *Y,float muki,float shot_x,float shot_y);

#endif