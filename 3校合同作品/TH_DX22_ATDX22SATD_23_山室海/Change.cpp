#include "Change.h"
#include "main.h"
#include "Camera.h"
#include "model.h"
#include "Sound.h"


#define EXPLOSION_MAX (40)
#define EXPLOSION_WIDTH		(256)
#define EXPLOSION_HEIGHT	(256)
#define EXPLOSION_PATTERN_MAX (8)

typedef struct
{// ���_�̍\����
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}VERTEX_3D_CHANGE;

typedef struct
{
	D3DXMATRIX g_mtxWorld;
	D3DXVECTOR3 pos;
	int count;
	int nPattern;
	bool use;
	bool type;
}CHANGE;


static D3DXMATRIX k_mtxWorld;

static CHANGE change;

static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 ch_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ch_pIndexBuffer = NULL;

static const TEXTURE_CHANGE g_aTexture[2]={
						{"texture\\change_effect1.png",1024,512},
						{"texture\\change_effect2.png",1024,512},
									};
static LPDIRECT3DTEXTURE9 g_pTextures[2]; 

static VERTEX_3D_CHANGE v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2 (0.25f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2(0.0f,0.5f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2 (0.25f,0.5f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};

void InitChange (void)
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, "�f�o�C�X���ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}




	HRESULT hr;

	for(int i=0 ; i<2 ; i++)
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
	

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_CHANGE) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_CHANGE,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ch_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);


	if( FAILED (hr) )
	{
		MessageBox(NULL, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}



	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ch_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}


	 CreateVertex_ch();

	 change.use=false;

}
void UninitChange(void)
{
}
void UpdateChange(void)
{
	D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

	g_mtxInvView._41 = 0.0f;
	g_mtxInvView._42 = 0.0f;
	g_mtxInvView._43 = 0.0f;

	for(int i = 0 ; i < EXPLOSION_MAX ; i++)
	{
		if(change.use)
		{
			D3DXMatrixScaling(&k_mtxWorld,3.5,3.5,1);
			D3DXMatrixTranslation( &change.g_mtxWorld, GetPlayerPos()->x ,GetPlayerPos()->y  ,GetPlayerPos()->z-1);
			change.g_mtxWorld=k_mtxWorld*change.g_mtxWorld;
			change.g_mtxWorld=g_mtxInvView*change.g_mtxWorld;

		}
	}
}
void DrawChange(void)
{
LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_CHANGE);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

		pDevice->SetStreamSource(0,
		ch_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_CHANGE)); //�P���_���̃T�C�Y

		pDevice->SetIndices(ch_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures[0]);						// �e�N�X�`���ێ��A�h���X

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��
		


		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

//---------�`�揈��------------------//



		if(change.use)
		{
			if(change.type)
			{
				change.count++;
			
				int nPattern = change.count/2;

				v[0].texcoord = D3DXVECTOR2(0.0f+((nPattern%5)*0.2),0.0f+((nPattern/5)*0.166));
				v[1].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.0f+(nPattern/5*0.166));
				v[2].texcoord =	D3DXVECTOR2(0.0f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166)) ;
				v[3].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166));

				CreateVertex_ch();

				if(nPattern>29)
				{
	 				change.use=false;
				}


				//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
				pDevice->SetTransform(D3DTS_WORLD,&change.g_mtxWorld);

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


		if(!change.type)
			{
				change.count++;
			
				int nPattern = change.count/2;

				v[0].texcoord = D3DXVECTOR2(0.0f+((nPattern%5)*0.2),0.0f+((nPattern/5)*0.166));
				v[1].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.0f+(nPattern/5*0.166));
				v[2].texcoord =	D3DXVECTOR2(0.0f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166)) ;
				v[3].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166));

				CreateVertex_ch();

				if(nPattern>29)
				{
	 				change.use=false;
				}


				//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
				pDevice->SetTransform(D3DTS_WORLD,&change.g_mtxWorld);

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

	
}
bool CreateChage(D3DXVECTOR3 Pos , bool type)
{
	if(change.use==false)
	{
		change.use=true;
		change.count=0;
		change.pos=Pos;
		change.type=type;
		return true;
	}
	return false;
}

void CreateVertex_ch(void)
{
	VERTEX_3D_CHANGE* pV;
	LPWORD pIndex;

	ch_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	ch_pVertexBuffer->Unlock();


	ch_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	ch_pIndexBuffer->Unlock();
}