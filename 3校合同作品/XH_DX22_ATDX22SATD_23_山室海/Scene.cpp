//====================================
// �Q�[���V�[��
//====================================
#include "Scene.h"
#include "input.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"


static SCENE_ID g_nNextID = SCENE_TITLE;
static SCENE_ID g_nID = SCENE_TITLE;


static bool Pause_flag=false;

static int Pause_flag2=-1;


typedef void (*FuncPointer)(void); 

static const FuncPointer InitFunc[] = {
	InitTitle,
	InitGame,
	InitResult
};

static const FuncPointer UninitFunc[] = {
	UninitTitle,
	UninitGame,
	UninitResult
};

static const FuncPointer UpdateFunc[] = {
	UpdateTitle,
	UpdateGame,
	UpdateResult
};

static const FuncPointer DrawFunc[] = {
	DrawTitle,
	DrawGame,
	DrawResult
};

//=================================================================================================
//	���ʏ����������֐�
//
//
//=================================================================================================
void InitScene(void)
{

	InitFunc[g_nID]();	

}

//=================================================================================================
//	���ʏ����������֐�
//
//
//=================================================================================================
void UninitScene(void)
{

	UninitFunc[g_nID]();	

}

//=================================================================================================
//	���ʏ����������֐�
//
//
//=================================================================================================
void UpdateScene(void)
{

	UpdateFunc[g_nID]();

	
}

//=================================================================================================
//	���ʏ����������֐�
//
//�t�F�[�h�A�E�g�̂��ƂɌĂяo��
//=================================================================================================
void DrawScene(void)
{

      DrawFunc[g_nID]();	




	// �`�悪�I�������Ƃ�
	if( g_nNextID != g_nID)
	{
		UninitScene();
		g_nID = g_nNextID;
		InitScene();
	}


}

//=================================================================================================
//	���ʏ����������֐�
//
//
//=================================================================================================
SCENE_ID ChangeScene(SCENE_ID nextScene)
{
 	g_nNextID = nextScene;

	return g_nID;
}

