#include "Homing.h"
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Enemy.h"
#include "model.h"
#include "Camera.h"
#include "Explosion.h"
#include "Effect.h"
#include "Score.h"
#include "Sound.h"
#include "Polygon.h"
#include "Rock_On.h"

#define BULLET_MAX (30)



typedef struct
{// ���_�̍\����
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}VERTEX_3D_HOMING;

typedef struct
{
	D3DXMATRIX g_mtxWorld;
	D3DXMATRIX g_mtxWorld2;
	D3DXVECTOR3 P0;
	D3DXVECTOR3 P1;
	D3DXVECTOR3 P2;
	D3DXVECTOR3 P3;
	D3DXVECTOR3 pos;
	float t;//(0~1)
	int  J;
	int count;
	bool use;
	bool type;
}HOMING;



static HOMING homing[BULLET_MAX];

static LPDIRECT3DVERTEXBUFFER9 ho_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ho_pIndexBuffer = NULL;

static LPDIRECT3DVERTEXBUFFER9 sha_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 sha_pIndexBuffer = NULL;

static D3DXMATRIX g_mtxWorld_k;

static D3DXMATRIX g_mtxWorld_m;

static D3DXMATRIX g_mtxInvView;


static const TEXTURE_HOMING gh_aTexture[] = {
	{"texture\\ball.png",225,225},
	{"texture\\shadow000.jpg", 80,80},
};

static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(gh_aTexture);

static LPDIRECT3DTEXTURE9 gh_pTextures[ TEXTURE_FILE_COUNT ]; 

static VERTEX_3D_HOMING v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2 (1.0f,1.0f)}
								};


static VERTEX_3D_HOMING v2[] = {
		//�O
		{ D3DXVECTOR3(-0.5,0.0,0.5),  D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f)  },//0
		{ D3DXVECTOR3(0.5,0.0,-0.5)  ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,1.0f) },//1
		{ D3DXVECTOR3(0.5,0.0,0.5),   D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,0.0f) },//2
		{ D3DXVECTOR3(-0.5,0.0,-0.5) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f)},//3
		
	};

static WORD Index2[]={ 0, 2, 3,	//	WORD��2�o�C�g
					  1, 3, 2};

static WORD Index[6]={0,1,2,
					  1,3,2};


int meter_count=0;


void InitHoming(void)
{
	for(int i=0 ; i<BULLET_MAX ; i++)
	{
		homing[i].use=false;
	}

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
			gh_aTexture[i].fileName,												// �t�@�C�����i���s�t�@�C���Ɠ����ꏊ�������炻�̂܂܁j
			&gh_pTextures[i]);													// �e�N�X�`���ێ��A�h���X�̃A�h���X

		if ( FAILED (hr) )
		{// ���G���[�`�F�b�N��΂�遚
			MessageBox(NULL, "�e�N�X�`�����ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
		}
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_HOMING) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_HOMING,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ho_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_HOMING) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_HOMING,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&sha_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(NULL, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}




	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ho_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);


	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&sha_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

	VERTEX_3D_HOMING * pV;
	LPWORD pIndex;

	VERTEX_3D_HOMING * pV2;
	LPWORD pIndex2;

	ho_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));

	ho_pVertexBuffer->Unlock();

	sha_pVertexBuffer->Lock(0,0,(void**)&pV2,D3DLOCK_DISCARD);

	memcpy(pV2,v2,sizeof(v));

	sha_pVertexBuffer->Unlock();


	ho_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));

	ho_pIndexBuffer->Unlock();

	sha_pIndexBuffer->Lock(0,0,(void**)&pIndex2,D3DLOCK_DISCARD);
	memcpy(pIndex2,Index2,sizeof(Index));


	sha_pIndexBuffer->Unlock();

}
void UninitHoming(void)
{

	if(ho_pVertexBuffer)
	{
		ho_pVertexBuffer->Release();
		ho_pVertexBuffer = NULL;

	}

	if(ho_pIndexBuffer)
	{
		ho_pIndexBuffer->Release();
		ho_pIndexBuffer = NULL;

	}
	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		if (gh_pTextures[i] != NULL)
		{// �e�N�X�`���ێ��̊J��
			gh_pTextures[i]->Release();
			gh_pTextures[i] = NULL;
		}
	}

	if(sha_pVertexBuffer)
	{
		sha_pVertexBuffer->Release();
		sha_pVertexBuffer = NULL;

	}

	if(sha_pIndexBuffer)
	{
		sha_pIndexBuffer->Release();
		sha_pIndexBuffer = NULL;

	}

}
void UpdateHoming(void)
{

	D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

	g_mtxInvView._41 = 0.0f;
	g_mtxInvView._42 = 0.0f;
	g_mtxInvView._43 = 0.0f;

	for(int i=0 ; i<BULLET_MAX ; i++)
	{
		if(homing[i].use)
		{

			homing[i].P3 = GetEnemyPos(i);
			homing[i].t += 0.006;
			homing[i].P1 = (homing[i].P3-homing[i].P0)/3;
			homing[i].P2 = ((homing[i].P3-homing[i].P0)/3)*2;
			
			homing[i].P1.y += 6; 
			homing[i].P2.y += 6;
			if(rand()%2==0)
			{
				homing[i].P1.x += 6; 
				homing[i].P2.x += 6;
			}

			homing[i].pos.x = (homing[i].P0.x * (1-homing[i].t) * (1-homing[i].t) * (1-homing[i].t)) //P0
							 +(homing[i].P1.x * 3 * homing[i].t * (1-homing[i].t) * (1-homing[i].t)) //P1
							 +(homing[i].P2.x * 3 * homing[i].t * homing[i].t * (1-homing[i].t)) //P2
							 +(homing[i].P3.x  *homing[i].t * homing[i].t * homing[i].t);

			homing[i].pos.y = (homing[i].P0.y * (1-homing[i].t) * (1-homing[i].t) * (1-homing[i].t)) //P0
							 +(homing[i].P1.y * 3 * homing[i].t * (1-homing[i].t) * (1-homing[i].t)) //P1
							 +(homing[i].P2.y * 3 * homing[i].t * homing[i].t * (1-homing[i].t)) //P2
							 +(homing[i].P3.y  *homing[i].t * homing[i].t * homing[i].t);

			homing[i].pos.z = (homing[i].P0.z * (1-homing[i].t) * (1-homing[i].t) * (1-homing[i].t)) //P0
							 +(homing[i].P1.z * 3 * homing[i].t * (1-homing[i].t) * (1-homing[i].t)) //P1
							 +(homing[i].P2.z * 3 * homing[i].t * homing[i].t * (1-homing[i].t)) //P2
							 +(homing[i].P3.z * homing[i].t * homing[i].t * homing[i].t);

			 CreatEffect( homing[i].pos.x, homing[i].pos.y , homing[i].pos.z ,70, homing[i].type);
		
			D3DXMatrixScaling( &homing[i].g_mtxWorld,0.4,0.4,0.3);
			D3DXMatrixTranslation( &g_mtxWorld_k, homing[i].pos.x , homing[i].pos.y, homing[i].pos.z);
			homing[i].g_mtxWorld*=g_mtxWorld_k;
			D3DXMatrixTranslation( &homing[i].g_mtxWorld2, homing[i].pos.x , 0.1, homing[i].pos.z);


			for(int j=0 ; j<20 ; j++)
			{
				if(HitCircle3(homing[i].pos.x, homing[i].pos.y, homing[i].pos.z, 0.4, GetEnemyPos(j).x , GetEnemyPos(j).y, GetEnemyPos(j).z,  1))
				{	
					DestroyEnemy_rock(j);
					CreateExplosion(homing[i].pos);
					//	PlaySound(SOUND_LABEL_EXPLOSION);
					if(homing[i].type!=GetEnemyType(j))
					{
						DestroyEnemy(j);
					}
						homing[i].use=false;
						AddScore();
				
				}
				
			}


			if(homing[i].t>1)
			{
				homing[i].use=false;
				for(int k = 0 ; k < 20 ; k++)
				{
					DestroyEnemy_rock(k);
					Destroty_Rock_On (k);

				}

			}

		}
	}
}
void DrawHoming(void)
{

	meter_count++;

	if(meter_count >= 300)
	{
		meter_count=300;
		SetPolygonColor(D3DCOLOR_RGBA(255,255,0,255));
	}
	int nPattern = meter_count/10;
	SetPolygonTexture( 9 );
	SetPolygonScale( 1.0f,1.0f,1.0f,1.0f );
	PolygonDraw( 600,400, 192*(nPattern%5), 192*(nPattern/5),192,192,true);

	SetPolygonColor(D3DCOLOR_RGBA(255,255,255,255));


	if(meter_count >= 300)
	{
		SetPolygonTexture( 10 );
		SetPolygonScale( 2.0f,2.0f,1.0f,1.0f );
		PolygonDraw( 640,450, 0, 0,64,31,true);		
	}


	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_HOMING);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

		pDevice->SetStreamSource(0,
		ho_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_HOMING)); //�P���_���̃T�C�Y

		pDevice->SetIndices(ho_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		gh_pTextures[0]);						// �e�N�X�`���ێ��A�h���X

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��
		


		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for(int i = 0 ; i < BULLET_MAX ; i++)
	{
		if(homing[i].use)
		{
			pDevice->SetTransform(D3DTS_WORLD,&homing[i].g_mtxWorld);

				pDevice->SetTexture(
				0,									// �e�N�X�`���X�e�[�W
				gh_pTextures[0]);						// �e�N�X�`���ێ��A�h���X

				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
											0,					//�x�[�X
											0,					//�C���f�b�N�X�ŏ�
											4,					//���_��
											0,
											2);				//�v���~�e�B�u��
		}
	}
}
void CreateHoming(bool type)
{
	if(meter_count>=300)
	{
		
		for(int i=0 ; i<BULLET_MAX ; i++)
		{
			if(GetEnemyRock(i))
			{
				homing[i].type=type;
				homing[i].use = true;
				homing[i].P0 = *GetPlayerPos();
				homing[i].P1 = GetEnemyPos(i);
				homing[i].t=0;
			}
		}

		meter_count=0;
		if(!homing[0].type)
		{
				v[0].color=
				v[1].color=
				v[2].color=
				v[3].color=D3DCOLOR_RGBA(0,255,255,255);
		}
		else
		{
				v[0].color=
				v[1].color=
				v[2].color=
				v[3].color=D3DCOLOR_RGBA(255,0,0,255);
		}


		VERTEX_3D_HOMING * pV;
		LPWORD pIndex;

		ho_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

		memcpy(pV,v,sizeof(v));

		ho_pVertexBuffer->Unlock();


		ho_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
		memcpy(pIndex,Index,sizeof(Index));

		ho_pIndexBuffer->Unlock();


	}
}

bool HitCircle3(float x0, float y0 , float z0 ,float r0, float x1, float y1, float z1 , float r1)
{
	/*x0 - x0 = 0;
	y0 - y0 = 0;
	x1 - x0;
	y1 - y0;*/

	float x = x1 - x0;
	float y = y1 - y0;
	float z = z1 - z0;
	float l = x*x + y*y +z*z ;	// l�͎Εӂ̓��̒���

	return l < (r0 + r1) * (r0 + r1);
	
}

void AddMeter(void)
{
	meter_count+=10;
}