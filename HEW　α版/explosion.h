//=============================================================================
//
// �����̏��� [explosion.h]
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*************************************
// �e�̎��
//*************************************
typedef enum
{
	EXPLOSIONTYPE_PLAYER = 0,		// �v���C���[�̒e�̔���
	EXPLOSIONTYPE_ENEMY,			// �G�̒e�̔���
	EXPLOSIONTYPE_MAX
} EXPLOSIONTYPE;

//*************************************
// �e�̍\����
//*************************************
typedef struct
{
	float fPosX;		// ���݂̈ʒu(�w���W)
	float fPosY;		// ���݂̈ʒu(�x���W)
	int nCounter;		// �J�E���^�[
	EXPLOSIONTYPE type;	// �����̎��
	bool bUse;			// �g�p�����ǂ���
	float *player_x;
	float *player_y;
	float muki;
	bool gravity;
	float Shot_x;
	float Shot_y;
} EXPLOSION;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void TermExplosion(void);
void UpdateExplosion(int *flag);
void UpdateExplosion2(int *flag);
void DrawExplosion(void);

void SetExplosion(float fPosX, float fPosY, EXPLOSIONTYPE type, float *X,
	float *Y,float muki,bool gravity,float shot_x,float shot_y);


#endif