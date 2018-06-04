//=============================================================================
//
// �A�N�V�����Q�[��[main.cpp]
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "field.h"
#include "bullet.h"
#include "explosion.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Init(void);
void Term(void);
void Update(void);
void Draw(void);
void DispFPS(void);
void title(void);
void DrawGravity(void);
void Button(void);
void Goal(void);
void start(void);
void menu(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_nCountFPS;				// FPS�J�E���^
int flag=0;
int count=0;
bool Gravity=false;
bool fin_flag=0;
int x=1;
int x_2=26;
int x_3=52;
bool button=false;
int  count_switch1=30;
bool count_switch2=false;
bool goal_switch=false;
int stage=1;

/*******************************************************************************/
int MP3_bgm;
int MP3_jump;
int MP3_shot;
int MP3_gameover;
int MP3_change;
int MP3_button1;
int MP3_button2;
int MP3_shot_fin;
int MP3_system1;
int MP3_system2;
int MP3_shoot;
int MP3_goal;
//=============================================================================
// ���C���֐�
//=============================================================================
void main(void)
{
	unsigned long dwExecLastTime;
	unsigned long dwFPSLastTime;
	unsigned long dwCurrentTime;
	int nCountFrame;

	// ����\��ݒ�
	timeBeginPeriod(1);

	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	nCountFrame = 0;

while(1)
{
	CLS();

		MP3_bgm=OPENMP3("bgm_main.mp3");
		MP3_jump=OPENMP3("jump.mp3");
		MP3_shot=OPENMP3("shot.mp3");
		MP3_gameover=OPENMP3("gameover.mp3");
		MP3_change=OPENMP3("change.mp3");
		MP3_button1=OPENMP3("button1.mp3");
		MP3_button2=OPENMP3("button2.mp3");
		MP3_shot_fin=OPENMP3("shot_fin.mp3");
		MP3_system1=OPENMP3("system1.mp3");
		MP3_system2=OPENMP3("system2.mp3");
		MP3_shoot=OPENMP3("shoot.mp3");
		MP3_goal=OPENMP3("goal.mp3");

	title();

	// ����������

	menu();


	Init();


	start();

	count_switch2=false;
	goal_switch=false;
	Gravity=false;
	fin_flag=false;
	button=false;

	PLAYMP3(MP3_bgm,1);

	// �J�[�\���\���n�e�e
	CUROFF();


	// �Q�[�����C������
	while(fin_flag!=true)
	{
		//dwCurrentTime = timeGetTime();
		//if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
		//{
		//	g_nCountFPS = nCountFrame * 1000 / (dwCurrentTime - dwFPSLastTime);
		//	dwFPSLastTime = dwCurrentTime;
		//	nCountFrame = 0;
		//}

		//if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
		//{
		//	dwExecLastTime = dwCurrentTime;

			// �X�V����
			Update();

			// �`�揈��
			Draw();

			Goal();


			// FPS�\��
			//DispFPS();


		//	nCountFrame++;
		//}
	}
		CLOSEMP3(MP3_bgm);
		CLOSEMP3(MP3_jump);
		CLOSEMP3(MP3_shot);
		CLOSEMP3(MP3_gameover);
		CLOSEMP3(MP3_change);
		CLOSEMP3(MP3_button1);
		CLOSEMP3(MP3_button2);
		CLOSEMP3(MP3_shot_fin);
		CLOSEMP3(MP3_system1);
		CLOSEMP3(MP3_system2);
		CLOSEMP3(MP3_shoot);
		CLOSEMP3(MP3_goal);
		Term();
}

	// �J�[�\���\���n�m
	CURON();

	// �I������
	Term();

	// ����\��߂�
	timeEndPeriod(1);
}

//=============================================================================
// ����������
//=============================================================================
void Init(void)
{
	// �n�ʂ̏���������
	InitField();

	InitField2();

	InitField3();

	InitField4();

	InitField5();

	// �v���C���[�̏���������
	InitPlayer();

	// �e�̏���������
	InitBullet();

	// �����̏���������
	InitExplosion();

}

//=============================================================================
// �I������
//=============================================================================
void Term(void)
{
	// �n�ʂ̏I������
	TermField();

	TermField2();

	TermField3();

	TermField4();

	TermField5();

	// �v���C���[�̏I������
	TermPlayer();

	TermBullet();

	// �����̏I������
	TermExplosion();

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// �n�ʂ̍X�V����
	UpdateField();

	UpdateField2();

	UpdateField3();

	UpdateField4();

	UpdateField5();

	Button();

	// �v���C���[�̍X�V����
	UpdatePlayer(&flag);

	// �e�̍X�V����
	UpdateBullet(&flag);

	// �����̍X�V����
	UpdateExplosion(&flag);

	UpdateExplosion2(&flag);



}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �n�ʂ̕`�揈��
	DrawField();

	DrawField2();

	DrawField3();

	DrawField4();

	DrawField5();


	// �v���C���[�̕`�揈��
	DrawPlayer(&flag);

	// �e�̕`�揈��
	DrawBullet();

	// �����̕`�揈��
	DrawExplosion();

	//�n��̕`�揈��
	DrawGravity();

}



//=============================================================================
// FPS�\��
//=============================================================================

/*
void DispFPS(void)
{
	// �F�ݒ�
	COLOR(WHITE);

	LOCATE(2, 3);
	printf("FPS:%d", g_nCountFPS);
}
*/

