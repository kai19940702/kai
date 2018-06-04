#include "main.h"
#include "grid.h"
#include <d3d9.h>
#include <d3dx9.h>


//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************

static D3DXMATRIX g_mtxWorld;


static float fRotX=0;
static float fRotY=0;
static float fRotZ=0;

static int count=0;
/*=========================================================
		����������
===========================================================*/
void GridInit(void)
{

}
/*=========================================================
		�I������
===========================================================*/
void GridUninit(void)
{

}
/*=========================================================
		�X�V����
===========================================================*/
void GridUpdate(void)
{


	//���[���h�ϊ��s��
	//�������Ȃ��s��(�P�ʍs��)
	D3DXMatrixIdentity( &g_mtxWorld );
	//D3DXMatrixRotationY( &g_mtxWorld,fRotY);
	




								
}
/*=========================================================
		�`�揈��
===========================================================*/
void GridDraw(void)
{	
	GRID v[44];
	int j=0;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE); //���C�e�B���O�I�t

	j=0;
	for(int i=0 ; i<44 ;i+=4)
	{
		v[i].pos=D3DXVECTOR3(-5+j,0.0,-5);
		v[i].color=D3DCOLOR_RGBA(255,0,0,255);
		v[i+1].pos=D3DXVECTOR3(-5+j,0.0,5);
		v[i+1].color=D3DCOLOR_RGBA(255,0,0,255);
		v[i+2].pos=D3DXVECTOR3(-5,0.0,-5+j);
		v[i+2].color=D3DCOLOR_RGBA(255,0,0,255);
		v[i+3].pos=D3DXVECTOR3(5,0.0,-5+j);
		v[i+3].color=D3DCOLOR_RGBA(255,0,0,255);
		j++;
	}



	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);//������F�ƒ��_�𑗂�Ƃ����Ӗ�


	//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

	pDevice->DrawPrimitiveUP(D3DPT_LINELIST,							// �v���~�e�B�u�^�C�v�i�}�`�̌`�j
								  22,									// �v���~�e�B�u�̐��i�}�`�̐��j
								  &v[0],								// ���_�ւ̃|�C���^
						  		  sizeof(GRID));					// 1�̒��_�̃T�C�Y


}