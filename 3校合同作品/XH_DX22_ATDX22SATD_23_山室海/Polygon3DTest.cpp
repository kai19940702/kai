#include "main.h"
#include "Polygon3DTset.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "model.h"

#define CUBE_NUM (5)



//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************


static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;


static D3DXMATRIX g_mtxWorld[5];

static float fRotY=0;

static D3DXVECTOR3 pos;

static const TEXTURE2 g_aTexture[] = {
	{"texture\\shadow000.jpg", 80,80},

};
// �z�񐔂���
static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(g_aTexture);

static LPDIRECT3DTEXTURE9 g_pTextures[ TEXTURE_FILE_COUNT ]; 
static D3DCOLOR g_PolygonColor = 0xffffffff;




static VERTEX_3D v[] = {
		//�O
		{ D3DXVECTOR3(-0.5,0.0,0.5) ,D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f)  },//0
		{ D3DXVECTOR3(0.5,0.0,-0.5)  ,D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,1.0f) },//1
		{ D3DXVECTOR3(0.5,0.0,0.5),D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,0.0f) },//2
		{ D3DXVECTOR3(-0.5,0.0,-0.5) ,D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f)},//3
		
	};


static WORD index[]={ 0, 2, 3,	//	WORD��2�o�C�g
					  1, 3, 2};







/*=========================================================
		����������
===========================================================*/
bool Polygon3DTestInit(HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		return false;
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
			MessageBox(hWnd, "�e�N�X�`�����ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
			return false;
		}
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&g_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(hWnd, "���_�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
		return false;
	}




	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&g_pIndexBuffer, //�Ǘ��҂̃|�C���^
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(hWnd, "�C���f�b�N�X�o�b�t�@���쐬����܂���ł���", "�G���[���b�Z�[�W", MB_OK);
		return false;
	}

	CreateVertex();


	return true;
}
/*=========================================================
		�I������
===========================================================*/
void Polygon3DTestUninit(void)
{
	if(g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;

	}

	if(g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;

	}
	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		if (g_pTextures[i] != NULL)
		{// �e�N�X�`���ێ��̊J��
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}
/*=========================================================
		�X�V����
===========================================================*/
void Polygon3DTestUpdate(void)
{




	pos=*GetPlayerPos();
	D3DXMatrixTranslation( &g_mtxWorld[0],pos.x,0.1,pos.z);


}
/*=========================================================
		�`�揈��
===========================================================*/
void Polygon3DTestDraw(void)
{
	//�}�e���A���쐬
	
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);//������F�ƒ��_�𑗂�Ƃ����Ӗ�


		pDevice->SetStreamSource(0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_3D)); //�P���_���̃T�C�Y

		pDevice->SetIndices(g_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures[0]);						// �e�N�X�`���ێ��A�h���X

//---------�`�揈��------------------//

	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);


		//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
		pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld[0]);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
									0,					//�x�[�X
									0,					//�C���f�b�N�X�ŏ�
									4,					//���_��
									0,
									2);				//�v���~�e�B�u��


	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);


}

void CreateVertex(void)
{
	VERTEX_3D* pV;
	LPWORD pIndex;

	g_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	g_pVertexBuffer->Unlock();


	g_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,index,sizeof(index));
	g_pIndexBuffer->Unlock();
}
