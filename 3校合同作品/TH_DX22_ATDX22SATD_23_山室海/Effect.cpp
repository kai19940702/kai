#include "effect.h"
/*====================================================================================================================================-

	effect.cpp

====================================================================================================================================*/

#include "Effect.h"
#include "Camera.h"
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "model.h"

/*====================================================================================================================================-

	�\����

====================================================================================================================================*/

typedef struct
{
	 D3DXMATRIX g_mtxWorld_k;
	D3DXMATRIX g_mtxWorld;
	 D3DXVECTOR3 vPos;
	 bool color;
	 int nLimit;
	 int nBirth; //���ꂽ�Ƃ��̃t���[����
	 int nAlpha;
	 bool bEffect;
	 int  Size;
}EFFECT;


typedef struct
{// ���_�̍\����
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR color;			// �F
	D3DXVECTOR2 texcoord;	// �e�N�X�`�����W
}VERTEX_3D_EFFECT;

/*====================================================================================================================================-

	�O���[�o���ϐ�

====================================================================================================================================*/

static EFFECT g_Effects[EFFECT_MAX];

static LPDIRECT3DVERTEXBUFFER9 ef_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ef_pIndexBuffer = NULL;

static int g_nFrameCount=0;

static D3DXMATRIX g_mtxInvView;


static const TEXTURE_EFFECT g_aTexture={"texture\\effect000.jpg",80,80};


static LPDIRECT3DTEXTURE9 g_pTextures; 

static VERTEX_3D_EFFECT v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,155) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,155) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,155) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,155) ,D3DXVECTOR2 (1.0f,1.0f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};

/*====================================================================================================================================-

	�������֐�

====================================================================================================================================*/
void InitEffect(void)
{
	for( int i = 0 ; i<EFFECT_MAX; i++)
	{
		g_Effects[i].bEffect = false;
	}
	g_nFrameCount=0;

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


	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_EFFECT) * 4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D_EFFECT,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ef_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(NULL, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}




	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&ef_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

		for( int i = 0 ; i<EFFECT_MAX ; i++ )
		{

			g_Effects[i].bEffect = false;

		}

	 CreateVertex_ef();

}

/*====================================================================================================================================-

	�I���֐�

====================================================================================================================================*/
void UninitEffect(void)
{
	if(ef_pVertexBuffer)
	{
		ef_pVertexBuffer->Release();
		ef_pVertexBuffer = NULL;

	}

	if(ef_pIndexBuffer)
	{
		ef_pIndexBuffer->Release();
		ef_pIndexBuffer = NULL;

	}

		if (g_pTextures!= NULL)
		{// �e�N�X�`���ێ��̊J��
			g_pTextures->Release();
			g_pTextures = NULL;
		}
	
}

/*====================================================================================================================================-

	�X�V�֐�

====================================================================================================================================*/
void UpdateEffect(void)
{

	D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

	g_mtxInvView._41 = 0.0f;
	g_mtxInvView._42 = 0.0f;
	g_mtxInvView._43 = 0.0f;

	for( int i = 0 ; i<EFFECT_MAX; i++)
	{
		if(g_Effects[i].bEffect)
		{
			//�������s������
			int nAge = g_nFrameCount - g_Effects[i].nBirth;

			if(nAge >=g_Effects[i].nLimit)
			{
				g_Effects[i].bEffect =false;
			}

			g_Effects[i].nAlpha-=255/g_Effects[i].nLimit;
		
			if(!g_Effects[i].color)
			{
				v[0].color=D3DCOLOR_RGBA(0,255,255,g_Effects[i].nAlpha);
				v[1].color=D3DCOLOR_RGBA(0,255,255,g_Effects[i].nAlpha);
				v[2].color=D3DCOLOR_RGBA(0,255,255,g_Effects[i].nAlpha);
				v[3].color=D3DCOLOR_RGBA(0,255,255,g_Effects[i].nAlpha);
			}
			else

			{
				v[0].color=D3DCOLOR_RGBA(255,0,0,g_Effects[i].nAlpha);
				v[1].color=D3DCOLOR_RGBA(255,0,0,g_Effects[i].nAlpha);
				v[2].color=D3DCOLOR_RGBA(255,0,0,g_Effects[i].nAlpha);
				v[3].color=D3DCOLOR_RGBA(255,0,0,g_Effects[i].nAlpha);
			}
			 CreateVertex_ef();
			 

			D3DXMatrixTranslation( &g_Effects[i].g_mtxWorld_k, g_Effects[i].vPos.x ,g_Effects[i].vPos.y  ,g_Effects[i].vPos.z);
			D3DXMatrixScaling(&g_Effects[i].g_mtxWorld,0.5,0.5,0.5);
			 g_Effects[i].g_mtxWorld*=g_Effects[i].g_mtxWorld_k;
			g_Effects[i].g_mtxWorld=g_mtxInvView*g_Effects[i].g_mtxWorld;
		}
	}
	g_nFrameCount++;
}



/*====================================================================================================================================-

	�`��֐�

====================================================================================================================================*/
void DrawEffect(void) 
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_EFFECT);//������F�ƒ��_�𑗂�Ƃ����Ӗ�

		pDevice->SetStreamSource(0,
		ef_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_EFFECT)); //�P���_���̃T�C�Y

		pDevice->SetIndices(ef_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures);						// �e�N�X�`���ێ��A�h���X

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //���C�e�B���O�I��

		pDevice->SetRenderState( D3DRS_ZENABLE , FALSE );

		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

		//���e�X�g
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	//	pDevice->SetRenderState(D3DRS_ALPHAREF,);
	//	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for(int i = EFFECT_MAX ; i>0 ; i--)
	{
		
		if(g_Effects[i].bEffect)
		{


			//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
			pDevice->SetTransform(D3DTS_WORLD,&g_Effects[i].g_mtxWorld);

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
	//���l���v�Z
	//�N��O�̎�...��1.0f(255)
	//�N�� ==�����̎�...��0.0f(0)

	//�ۂ�`��


	//�����̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState( D3DRS_ZENABLE , TRUE );



}

/*====================================================================================================================================-

	�G�t�F�N�g�쐬�֐�

====================================================================================================================================*/
void CreatEffect( float x, float y,float z,int nLife, bool type)
{
		for( int i = 0 ; i<EFFECT_MAX ; i++ )
		{
			if( !g_Effects[i].bEffect )
			{
				g_Effects[i].vPos = D3DXVECTOR3(x,y,z);
				g_Effects[i].nBirth = g_nFrameCount;
				g_Effects[i].color = type;
				g_Effects[i].nAlpha = 255;
				g_Effects[i].nLimit =nLife;
				g_Effects[i].bEffect = true;
				break;
			}
		}
}

void CreateVertex_ef(void)
{
	VERTEX_3D_EFFECT* pV;
	LPWORD pIndex;

	ef_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	ef_pVertexBuffer->Unlock();


	ef_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	ef_pIndexBuffer->Unlock();
}