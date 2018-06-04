//=======================================
//	Game�֐�
//=======================================
#include "main.h"
#include "Game.h"
#include "Homing.h"
#include "Polygon.h"
#include "Sound.h"
#include "Scene.h"
#include "Input.h"
#include<math.h>
#include "Polygon3DTset.h"
#include "Camera.h"
#include "grid.h"
#include "Input.h"
#include "light.h"
#include "model.h"
#include "MeshFiled.h"
#include "BillBoard.h"
#include "shadow.h"
#include "Explosion.h"
#include "Scene.h"
#include "Enemy.h"
#include "Effect.h"
#include "Score.h"
#include "Change.h"
#include "Pause.h"
#include "Haikei.h"
#include "Rock_On.h"



#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_GAME (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHW�͕ϊ��t���O�Ȃ̂Ŕ���

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_GAME;


typedef struct
{// ���_�̍\����
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}VERTEX_3D_GAME;

static D3DXMATRIX g_mtxWorld;
static D3DXMATRIX k_mtxWorld;
static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 ga_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ga_pIndexBuffer = NULL;

static const TEXTURE_GAME ga_aTexture[] = {
	{"texture\\READY.png",292,72},
	{"texture\\GO.png", 169,72},
};

static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(ga_aTexture);

static LPDIRECT3DTEXTURE9 ga_pTextures[ TEXTURE_FILE_COUNT ]; 

static VERTEX_3D_GAME v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0f,1.0f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};


static bool fin_flag=false;
static int fin_count=0;
static bool pause_flag=false;

static bool start_flag=false;
static bool first_flag=false;

static float z=20;
static int count=0; 


//=================================================================================================
//	�Q�[�������������֐�
//
//
//=================================================================================================
void InitGame(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, "�f�o�C�X���ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}


	HRESULT hr;

	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		hr = D3DXCreateTextureFromFile(
			pDevice,															// �f�o�C�X
			ga_aTexture[i].fileName,												// �t�@�C�����i���s�t�@�C���Ɠ����ꏊ�������炻�̂܂܁j
			&ga_pTextures[i]);													// �e�N�X�`���ێ��A�h���X�̃A�h���X

		if ( FAILED (hr) )
		{// ���G���[�`�F�b�N��΂�遚
			MessageBox(NULL, "�e�N�X�`�����ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
		}
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_GAME) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_BILLBOARD,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ga_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);


	if( FAILED (hr) )
	{
		MessageBox(NULL, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}


	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ga_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

	VERTEX_3D_GAME* pV;
	LPWORD pIndex;

	ga_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	ga_pVertexBuffer->Unlock();


	ga_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	ga_pIndexBuffer->Unlock();



	InitScore();
	InitChange();
	InitEnemy();
	InitBillBoard();
	InitExplosion();
	InitHaikei();
	InitPause();
	InitHoming();
	InitModel();
	InitEffect();
	InitRock_On();

	fin_flag=false;
	fin_count=0;
	pause_flag=false;

	start_flag=false;
	first_flag=false;
}

//=================================================================================================
//	�Q�[���X�I�������֐�
//
//
//=================================================================================================
void UninitGame(void)
{

	 fin_flag=false;
	 fin_count=0;
	 pause_flag=false;

	 start_flag=false;
	 first_flag=false;
	
	 z=20;
	 count=0; 

	if(ga_pVertexBuffer)
	{
		ga_pVertexBuffer->Release();
		ga_pVertexBuffer = NULL;

	}

	if(ga_pIndexBuffer)
	{
		ga_pIndexBuffer->Release();
		ga_pIndexBuffer = NULL;

	}

	for(int i=0 ; i < TEXTURE_FILE_COUNT; i++)
	{
		if (ga_pTextures!= NULL)
		{// �e�N�X�`���ێ��̊J��
			ga_pTextures[i]->Release();
			ga_pTextures [i]= NULL;
		}
	}

	UninitHaikei();
	UninitHoming();
	UninitEffect();
	UninitModel();
	UninitEnemy();
	UninitRock_On();
//	UninitBillBoard();
}

//=================================================================================================
//	�Q�[���X�V�����֐�
//
//
//=================================================================================================
void UpdateGame( void )
{
	if(!start_flag)
	{
		D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

		g_mtxInvView._41 = 0.0f;
		g_mtxInvView._42 = 0.0f;
		g_mtxInvView._43 = 0.0f;


		D3DXMatrixScaling(&k_mtxWorld,3,1,1);
		D3DXMatrixTranslation( &g_mtxWorld,GetPlayerPos()->x,GetPlayerPos()->y,z);
		g_mtxWorld=k_mtxWorld*g_mtxWorld;
		g_mtxWorld=g_mtxInvView*g_mtxWorld;

		z-=0.2;

		if(z<-5)
		{
			z=20;
			count++;
			

			if(count==1)
			{
				PlaySound(SOUND_LABEL_START);
			}
			if(count==2)
			{
				start_flag=true;
				first_flag=false;
			}
		}

	}

	if(!first_flag)
	{
		CameraUpdate();
		PolygonUpdate();
		fin_flag=UpdateModel();
		UpdateEnemy();
		Polygon3DTestUpdate();
		GridUpdate();
		UpdateLight();
		UpdateBillBoard();
		MeshfFiledUpdate();
		UpdateExplosion();
		UpdateShadow();
		UpdateEffect();
		UpdateChange();
		pause_flag=UpdatePause2();
		UpdateHaikei();
		UpdateHoming();
		UpdateEffect();
		UpdateRock_On();
	

		if(count==0)
		{
			first_flag=true;
			PlaySound(SOUND_LABEL_READY);
			
		}
	
		

		if(fin_flag)
		{
			fin_count++;
		//	ChangeScene(SCENE_RESULT);
		}

		if(fin_count>60&&fin_flag)
		{
			ChangeScene(SCENE_RESULT);
		}
	}
	
}

//=================================================================================================
//	�Q�[���`�揈���֐�
//
//
//=================================================================================================
void DrawGame( void )
{
		//GridDraw();
		DrawModel();

		DrawEnemy();
		MeshfFiledDraw();
		DrawHaikei();
		Polygon3DTestDraw();//�e

		DrawBillBoard();
		DrawExplosion();
		DrawEffect();
		DrawScore( 0, 0, false, false);
		DrawChange();
		DrawHoming();
		DrawEffect();
		DrawRock_On();

		if(pause_flag)
		{
			DrawPause();
		}



	if(!start_flag)
	{

		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
		//FVF�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D_BILLBOARD);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

			pDevice->SetStreamSource(0,
			ga_pVertexBuffer,
			0,
			sizeof(VERTEX_3D_GAME)); //�P���_���̃T�C�Y

			pDevice->SetIndices(ga_pIndexBuffer);

			if(count==0)
			{
				pDevice->SetTexture(
				0,									// �e�N�X�`���X�e�[�W
				ga_pTextures[0]);						// �e�N�X�`���ێ��A�h���X
			}
			if(count==1)
			{
				pDevice->SetTexture(
				0,									// �e�N�X�`���X�e�[�W
				ga_pTextures[1]);						// �e�N�X�`���ێ��A�h���X
			}
			pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��
		


			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF,15);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	//---------�`�揈��------------------//



			//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
			pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);


			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
										0,					//�x�[�X
										0,					//�C���f�b�N�X�ŏ�
										4,					//���_��
										0,
										2);				//�v���~�e�B�u��
	}


}


