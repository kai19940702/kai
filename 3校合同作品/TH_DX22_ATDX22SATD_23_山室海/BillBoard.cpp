#include "BillBoard.h"
#include "Camera.h"
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "model.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Score.h"
#include "Homing.h"
#define BULLET_MAX (100)



typedef struct
{// ���_�̍\����
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}VERTEX_3D_BILLBOARD;

typedef struct
{
	D3DXMATRIX g_mtxWorld;
	D3DXMATRIX g_mtxWorld2;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 front;
	int count;
	bool use;
	bool type;
}BULLET;



static BULLET bullet[100];

static LPDIRECT3DVERTEXBUFFER9 b_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 b_pIndexBuffer = NULL;

static LPDIRECT3DVERTEXBUFFER9 sh_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 sh_pIndexBuffer = NULL;

static D3DXMATRIX g_mtxWorld_k;

static D3DXMATRIX g_mtxWorld_m;

static D3DXMATRIX g_mtxInvView;


static const TEXTURE_BILLBOARD g_aTexture[] = {
	{"texture\\ball.png",225,225},
	{"texture\\shadow000.jpg", 80,80},
};

static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(g_aTexture);

static LPDIRECT3DTEXTURE9 g_pTextures[ TEXTURE_FILE_COUNT ]; 

static VERTEX_3D_BILLBOARD v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(0,255,255,255) ,D3DXVECTOR2 (1.0f,1.0f)}
								};


static VERTEX_3D_BILLBOARD v2[] = {
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

bool HitCircle(float x0, float y0 , float z0   ,float r0, float x1, float y1, float z1   , float r1);

void InitBillBoard(void)
{
	for(int i=0 ; i<BULLET_MAX ; i++)
	{
		bullet[i].use=false;
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
			g_aTexture[i].fileName,												// �t�@�C�����i���s�t�@�C���Ɠ����ꏊ�������炻�̂܂܁j
			&g_pTextures[i]);													// �e�N�X�`���ێ��A�h���X�̃A�h���X

		if ( FAILED (hr) )
		{// ���G���[�`�F�b�N��΂�遚
			MessageBox(NULL, "�e�N�X�`�����ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
		}
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_BILLBOARD) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_BILLBOARD,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&b_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_BILLBOARD) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_BILLBOARD,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&sh_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(NULL, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}




	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&b_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);


	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&sh_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

	CreateVertex_b();
}


void CreateBuullet(bool type,float x)
{

	for(int i=0 ; i<BULLET_MAX ; i++)
	{
		if(!bullet[i].use)
		{
			bullet[i].use = true;
 			bullet[i].pos = *GetPlayerPos();
			bullet[i].pos.y-=1;
			bullet[i].pos.x=x;
			bullet[i].front = *GetPlayerfront();
			D3DXVec3Normalize(&bullet[i].front,&bullet[i].front);
			bullet[i].count=0;
			bullet[i].type=type;
			break;

		}
	}
}
void UninitBillBorad(void)
{
	if(b_pVertexBuffer)
	{
		b_pVertexBuffer->Release();
		b_pVertexBuffer = NULL;

	}

	if(b_pIndexBuffer)
	{
		b_pIndexBuffer->Release();
		b_pIndexBuffer = NULL;

	}
	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		if (g_pTextures[i] != NULL)
		{// �e�N�X�`���ێ��̊J��
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}

	if(sh_pVertexBuffer)
	{
		sh_pVertexBuffer->Release();
		sh_pVertexBuffer = NULL;

	}

	if(sh_pIndexBuffer)
	{
		sh_pIndexBuffer->Release();
		sh_pIndexBuffer = NULL;

	}

}
void UpdateBillBoard(void)
{
	//if(GetKeyboardTrigger(DIK_SPACE))
	//{
	//	CreateBuullet();
	//}

	D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

	g_mtxInvView._41 = 0.0f;
	g_mtxInvView._42 = 0.0f;
	g_mtxInvView._43 = 0.0f;

	for(int i=0 ; i<BULLET_MAX ; i++)
	{
		if(bullet[i].use)
		{
			D3DXMatrixScaling( &bullet[i].g_mtxWorld,0.2,0.2,0.2);

			bullet[i].count++;
			D3DXMatrixTranslation( &g_mtxWorld_m, bullet[i].pos.x , bullet[i].pos.y+1, bullet[i].pos.z);
			D3DXMatrixTranslation( &bullet[i].g_mtxWorld2, bullet[i].pos.x , 0.1, bullet[i].pos.z);
			bullet[i].pos+= (bullet[i].front*0.3);
			bullet[i].g_mtxWorld*=g_mtxWorld_m;

			bullet[i].g_mtxWorld=g_mtxInvView*bullet[i].g_mtxWorld;

			D3DXVECTOR3 enemy_pos= GetEnemyPos(i);


			for(int j=0 ; j<20 ; j++)
			{
				if(HitCircle(bullet[i].pos.x, bullet[i].pos.y, bullet[i].pos.z, 0.2, GetEnemyPos(j).x , GetEnemyPos(j).y, GetEnemyPos(j).z,  1))
				{
			
						CreateExplosion(bullet[i].pos);

						if(bullet[i].type!=GetEnemyType(j))
						{
							DestroyEnemy(j);
							AddScore();
						//	AddMeter();
						}

						bullet[i].use=false;
				
				}
				
			}
			if(bullet[i].pos.z>60)
			{
				bullet[i].use=false;
			}

		}

	}




}
void DrawBillBoard(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_BILLBOARD);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

		pDevice->SetStreamSource(0,
		b_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_BILLBOARD)); //�P���_���̃T�C�Y

		pDevice->SetIndices(b_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures[0]);						// �e�N�X�`���ێ��A�h���X

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��
		


		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

//---------�`�揈��------------------//


	for(int i = BULLET_MAX ; i > 0 ; i--)
	{
		if(bullet[i].use)
		{
			if(!bullet[i].type)
			{
				v[0].color=
				v[1].color=
				v[2].color=
				v[3].color=D3DCOLOR_RGBA(0,255,255,255);


				CreateVertex_b();
				//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
				pDevice->SetTransform(D3DTS_WORLD,&bullet[i].g_mtxWorld);

				pDevice->SetTexture(
				0,									// �e�N�X�`���X�e�[�W
				g_pTextures[0]);						// �e�N�X�`���ێ��A�h���X

				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
											0,					//�x�[�X
											0,					//�C���f�b�N�X�ŏ�
											4,					//���_��
											0,
											2);				//�v���~�e�B�u��
			}
			else
			{
				v[0].color=
				v[1].color=
				v[2].color=
				v[3].color=D3DCOLOR_RGBA(255,0,0,255);

				CreateVertex_b();
				//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
				pDevice->SetTransform(D3DTS_WORLD,&bullet[i].g_mtxWorld);

				pDevice->SetTexture(
				0,									// �e�N�X�`���X�e�[�W
				g_pTextures[0]);						// �e�N�X�`���ێ��A�h���X

				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
											0,					//�x�[�X
											0,					//�C���f�b�N�X�ŏ�
											4,					//���_��
											0,
											2);				//�v���~�e�B�u��

			}
		}

	}

		pDevice->SetStreamSource(0,
		sh_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_BILLBOARD)); //�P���_���̃T�C�Y

		pDevice->SetIndices(sh_pIndexBuffer);

	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	for(int i = BULLET_MAX ; i > 0 ; i--)
	{
		if(bullet[i].use)
		{
			//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
			pDevice->SetTransform(D3DTS_WORLD,&bullet[i].g_mtxWorld2);

			pDevice->SetTexture(
			0,									// �e�N�X�`���X�e�[�W
			g_pTextures[1]);						// �e�N�X�`���ێ��A�h���X

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
										0,					//�x�[�X
										0,					//�C���f�b�N�X�ŏ�
										4,					//���_��
										0,
										2);				//�v���~�e�B�u��
		}

	}

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);


	/*
			//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
			pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld_m);

			pDevice->SetTexture(
			0,									// �e�N�X�`���X�e�[�W
			g_pTextures[1]);						// �e�N�X�`���ێ��A�h���X

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
										0,					//�x�[�X
										0,					//�C���f�b�N�X�ŏ�
										4,					//���_��
										0,
										2);				//�v���~�e�B�u��
	*/
}
void CreateVertex_b(void)
{
	VERTEX_3D_BILLBOARD * pV;
	LPWORD pIndex;

	VERTEX_3D_BILLBOARD * pV2;
	LPWORD pIndex2;

	b_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));

	b_pVertexBuffer->Unlock();

	sh_pVertexBuffer->Lock(0,0,(void**)&pV2,D3DLOCK_DISCARD);

	memcpy(pV2,v2,sizeof(v));

	sh_pVertexBuffer->Unlock();


	b_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));

	b_pIndexBuffer->Unlock();

	sh_pIndexBuffer->Lock(0,0,(void**)&pIndex2,D3DLOCK_DISCARD);
	memcpy(pIndex2,Index2,sizeof(Index));


	sh_pIndexBuffer->Unlock();

}


bool HitCircle(float x0, float y0 , float z0 ,float r0, float x1, float y1, float z1 , float r1)
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

/*NOTE

�s�����|���S��=>�J��������߂����ɕ`��
���߃|���S��=>�J�������牓�����ɕ`��(�s��������j
�������Ń\�[�g����̂Ń��[�g����Ȃ��B
D3DXVec3LeghtSq���g��(���[�g�g��Ȃ��j


���e�X�g
���̒l���`�F�b�N���č��i������`�悷��
�����b�g�@�E�E�|���S����`���Ȃ��̂�Z�o�b�t�@�����`����Ȃ�
�f�����b�g�E�E���u�����h�ł͂Ȃ��̂ŃG�b�W�������Ȃ��B



z�o�b�t�@(Z�e�X�g)

Z�o�b�t�@�̗L��(�������݁A�Q�Ɓj
pDevice->SetRenderState(D3DRS_ZENABLE,TRUE or FALSE)

z�o�b�t�@�̏������ݗL������(��������)
pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE or FALSE)


*/