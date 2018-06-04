#include "main.h"
#include "shadow.h"
#include "BillBoard.h"
#include "model.h"

#define SHADOW_MAX (100)

typedef struct
{
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}TEXTURE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXMATRIX g_mtxWorld;
	bool b_use;
}SHADOW;

static TEXTURE v[] = {
		//�O
		{ D3DXVECTOR3(-0.5,0.0,0.5)  ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f)  },//0
		{ D3DXVECTOR3(0.5,0.0,-0.5)  ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,0.0f) },//1
		{ D3DXVECTOR3(0.5,0.0,0.5)   ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,0.0f) },//2
		{ D3DXVECTOR3(-0.5,0.0,-0.5) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f)},//3
		
	};


static WORD Index[]={ 0, 2, 3,	//	WORD��2�o�C�g
					  1, 3, 2};

static LPDIRECT3DVERTEXBUFFER9 s_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 s_pIndexBuffer = NULL;

static SHADOW shadow;

static const TEXTURE_SHADOW g_aTexture={"texture\\ball.png",225,225};


static LPDIRECT3DTEXTURE9 g_pTextures; 

void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, "�f�o�C�X���ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
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

		hr = pDevice->CreateVertexBuffer(sizeof(TEXTURE) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_SHADOW,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&s_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&s_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

	TEXTURE * pV;
	LPWORD pIndex;

	s_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	s_pVertexBuffer->Unlock();


	s_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	s_pIndexBuffer->Unlock();

}
void UninitShadow(void)
{
	if(s_pVertexBuffer)
	{
		s_pVertexBuffer->Release();
		s_pVertexBuffer = NULL;

	}

	if(s_pIndexBuffer)
	{
		s_pIndexBuffer->Release();
		s_pIndexBuffer = NULL;

	}

	if (g_pTextures!= NULL)
	{// �e�N�X�`���ێ��̊J��
		g_pTextures->Release();
		g_pTextures = NULL;
	}

}
void UpdateShadow(void)
{

	shadow.pos=*GetPlayerPos();
	D3DXMatrixTranslation( &shadow.g_mtxWorld,shadow.pos.x,0.5,shadow.pos.z);
}
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_SHADOW);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

		pDevice->SetStreamSource(0,
		s_pVertexBuffer,
		0,
		sizeof(SHADOW)); //�P���_���̃T�C�Y

		pDevice->SetIndices(s_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures);						// �e�N�X�`���ێ��A�h���X

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��
		
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);


			//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
			pDevice->SetTransform(D3DTS_WORLD,&shadow.g_mtxWorld);

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
/*
void CreateShadow(void)
{
	for(int i=0 ; i<SHADOW_MAX ;i++)
	{
		if(!shadow[i].b_use)
		{
			shadow[i].b_use=true;
//			shadow[i].pos=*GetPos(i);
			break;
		}
	}
}
*/