#include "haikei.h"
#include "main.h"

typedef struct
{// ���_�̍\����
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}VERTEX_3D_HAIKEI;



static D3DXMATRIX g_mtxWorld;


static D3DXMATRIX k_mtxWorld;


static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 ha_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ha_pIndexBuffer = NULL;

static const TEXTURE_HAIKEI g_aTexture={"texture\\milky-way-474931_640.jpg",640,425};
static LPDIRECT3DTEXTURE9 g_pTextures; 

static VERTEX_3D_HAIKEI v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0f,1.0f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};




void InitHaikei(void)
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
	

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_HAIKEI) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_HAIKEI,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ha_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);


	if( FAILED (hr) )
	{
		MessageBox(NULL, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}



	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ha_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

	VERTEX_3D_HAIKEI* pV;
	LPWORD pIndex;

	ha_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	ha_pVertexBuffer->Unlock();


	ha_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	ha_pIndexBuffer->Unlock();

}
void UninitHaikei(void)
{
	if(ha_pVertexBuffer)
	{
		ha_pVertexBuffer->Release();
		ha_pVertexBuffer = NULL;

	}

	if(ha_pIndexBuffer)
	{
		ha_pIndexBuffer->Release();
		ha_pIndexBuffer = NULL;

	}

		if (g_pTextures!= NULL)
		{// �e�N�X�`���ێ��̊J��
			g_pTextures->Release();
		}

}
void UpdateHaikei(void)
{
		D3DXMatrixScaling(&g_mtxWorld,500,500,1);
		D3DXMatrixTranslation( &k_mtxWorld,0,0,300);
		g_mtxWorld*=k_mtxWorld;
}
void DrawHaikei(void)
{
LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_HAIKEI);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

		pDevice->SetStreamSource(0,
		ha_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_HAIKEI)); //�P���_���̃T�C�Y

		pDevice->SetIndices(ha_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures);						// �e�N�X�`���ێ��A�h���X

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��
		


		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

//---------�`�揈��------------------//



			//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
			pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

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