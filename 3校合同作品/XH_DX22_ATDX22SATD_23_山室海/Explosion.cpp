#include "Explosion.h"
#include "BillBoard.h"
#include "main.h"
#include "Camera.h"

#define EXPLOSION_MAX (40)
#define EXPLOSION_WIDTH		(256)
#define EXPLOSION_HEIGHT	(256)
#define EXPLOSION_PATTERN_MAX (8)

typedef struct
{// ���_�̍\����
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}VERTEX_3D_EXPLOSION;

typedef struct
{
	D3DXMATRIX g_mtxWorld;
	D3DXVECTOR3 pos;
	int count;
	int nPattern;
	bool use;
}EXPLOSION;


static D3DXMATRIX k_mtxWorld;

static EXPLOSION explosion[100];

static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 ex_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ex_pIndexBuffer = NULL;

static const TEXTURE_BILLBOARD g_aTexture={"texture\\explosion.png",1024,512};
static LPDIRECT3DTEXTURE9 g_pTextures; 

static VERTEX_3D_EXPLOSION v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (0.25f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.5f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (0.25f,0.5f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};

void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, "�f�o�C�X���ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

	for(int i=0 ; i< EXPLOSION_MAX ;i++)
	{
		explosion[i].use=false;
	}



	HRESULT hr;


		hr = D3DXCreateTextureFromFile(
			pDevice,															// �f�o�C�X
			g_aTexture.fileName,												// �t�@�C�����i���s�t�@�C���Ɠ����ꏊ�������炻�̂܂܁j
			&g_pTextures);													// �e�N�X�`���ێ��A�h���X�̃A�h���X

		if ( FAILED (hr) )
		{// ���G���[�`�F�b�N��΂�遚
			MessageBox(NULL, "�e�N�X�`�����ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
		}
	

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_EXPLOSION) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_BILLBOARD,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ex_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);


	if( FAILED (hr) )
	{
		MessageBox(NULL, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}



	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ex_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}


	 CreateVertex_ex();

}
void UninitExplosion(void)
{
	if(ex_pVertexBuffer)
	{
		ex_pVertexBuffer->Release();
		ex_pVertexBuffer = NULL;

	}

	if(ex_pIndexBuffer)
	{
		ex_pIndexBuffer->Release();
		ex_pIndexBuffer = NULL;

	}

		if (g_pTextures!= NULL)
		{// �e�N�X�`���ێ��̊J��
			g_pTextures->Release();
			g_pTextures = NULL;
		}
	
}
void UpdateExplosion(void)
{

	D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

	g_mtxInvView._41 = 0.0f;
	g_mtxInvView._42 = 0.0f;
	g_mtxInvView._43 = 0.0f;

	for(int i = 0 ; i < EXPLOSION_MAX ; i++)
	{
		if(explosion[i].use)
		{
			D3DXMatrixScaling(&k_mtxWorld,5,5,1);
			D3DXMatrixTranslation( &explosion[i].g_mtxWorld, explosion[i].pos.x ,explosion[i].pos.y+1  ,explosion[i].pos.z-1);
			explosion[i].g_mtxWorld=k_mtxWorld*explosion[i].g_mtxWorld;
			explosion[i].g_mtxWorld=g_mtxInvView*explosion[i].g_mtxWorld;

		}
	}
}
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_BILLBOARD);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

		pDevice->SetStreamSource(0,
		ex_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_EXPLOSION)); //�P���_���̃T�C�Y

		pDevice->SetIndices(ex_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures);						// �e�N�X�`���ێ��A�h���X

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��
		


		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

//---------�`�揈��------------------//


	for(int i = 0 ; i < EXPLOSION_MAX; i++)
	{
		if(explosion[i].use)
		{
			explosion[i].count++;
			
			int nPattern =explosion[i].count/5;

			v[0].texcoord = D3DXVECTOR2(0.0f+((nPattern%4)*0.25),0.0f+((nPattern/4)*0.5));
			v[1].texcoord =	D3DXVECTOR2(0.25f+(nPattern%4*0.25),0.0f+(nPattern/4*0.5));
			v[2].texcoord =	D3DXVECTOR2(0.0f+(nPattern%4*0.25),0.5f+(nPattern/4*0.5)) ;
			v[3].texcoord =	D3DXVECTOR2(0.25f+(nPattern%4*0.25),0.5f+(nPattern/4*0.5));

			CreateVertex_ex();

			if(nPattern>7)
			{
	 			explosion[i].use=false;
				break;
			}


			//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
			pDevice->SetTransform(D3DTS_WORLD,&explosion[i].g_mtxWorld);

			pDevice->SetTexture(
			0,									// �e�N�X�`���X�e�[�W
			g_pTextures);						// �e�N�X�`���ێ��A�h���X

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
										0,					//�x�[�X
										0,					//�C���f�b�N�X�ŏ�
										4,					//���_��
										0,
										2);				//�v���~�e�B�u��
		}

	}
}
void CreateExplosion( D3DXVECTOR3 Pos)
{
	for(int i=0 ; i<EXPLOSION_MAX ; i++)
	{
		if(!explosion[i].use)
		{
			explosion[i].count=0;
			explosion[i].pos=Pos;
			explosion[i].use=true;
			break;
		}
	}
}


void CreateVertex_ex(void)
{
	VERTEX_3D_EXPLOSION* pV;
	LPWORD pIndex;

	ex_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	ex_pVertexBuffer->Unlock();


	ex_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	ex_pIndexBuffer->Unlock();
}