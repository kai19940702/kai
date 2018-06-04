#include "main.h"
#include "Camera.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include "Input.h"
#include"model.h"


#define SPEED (0.1f)
#define S_SPEED (0.02f)

static float clip =0;


//----------------------------------------------------//
//----------------------------------------------------//

static D3DXMATRIX g_mtxView;
static D3DXMATRIX g_mtxProjection;

				// �J�������W,���_
static D3DXVECTOR3 g_eye( 0.0f , 5.0f , -10.0f);
static D3DXVECTOR3 g_at( 0.0f , 0.0f ,0.0f );

static D3DXVECTOR3 g_front , g_right;	//�K���P�ʃx�N�g��
static D3DXVECTOR3 g_up( 0.0f , 1.0f , 0.0f);

//�萔
static float g_speed=SPEED;	//�ړ����x
static float g_spin;	//��]���x
//----------------------------------------------------//
//					�������֐�						�@//
//----------------------------------------------------//
void CameraInit(void)
{
	g_eye=D3DXVECTOR3( 0.0f , 5.0f , -10.0f);
	g_at=D3DXVECTOR3( 0.0f , 0.0f ,0.0f );

}
//----------------------------------------------------//
//					�I���֐�						�@//
//----------------------------------------------------//
void CameraUninit(void)
{

}
//----------------------------------------------------//
//					�X�V�֐�						�@//
//----------------------------------------------------//
void CameraUpdate(void)
{


	//�O�����̃x�N�g�������
	g_front=g_at-g_eye;
	//�P�ʃx�N�g����
//	D3DXVec3Normalize(&g_front,&g_front);

	D3DXVECTOR3 vec=g_front;
	vec.y=0;
	D3DXVec3Normalize(&vec,&vec);


	//����(�P�ʃx�N�g�����m�Ȃ�[�P�`�P�j
	//float a = D3DXvec3Dot(&���Ӄx�N�g��,&�E�Ӄx�N�g��)

	//�O�ςŉE���������߂�
	D3DXVec3Cross(&g_right,&g_front,&g_up);
	D3DXVec3Normalize(&g_right,&g_right);

	D3DXMATRIX mtx;


	g_at=*GetPlayerPos();

	g_eye.x=g_at.x;
	g_eye.y=g_at.y+1;
	g_eye.z=g_at.z-3;
/*
	//�O�ړ�
	if(GetKeyboardPress(DIK_W))
	{
		g_eye+=vec*g_speed;
		g_at+=vec*g_speed;
	}



	//���ړ�
	if(GetKeyboardPress(DIK_S))
	{
		g_eye-=vec*g_speed;
		g_at-=vec*g_speed;
	}

	//��
	if(GetKeyboardPress(DIK_A))
	{
		g_eye+=g_right*g_speed;
		g_at+=g_right*g_speed;
	}

	//�E
	if(GetKeyboardPress(DIK_D))
	{
		g_eye-=g_right*g_speed;
		g_at-=g_right*g_speed;
	}

	//��
	if(GetKeyboardPress(DIK_Q))
	{
		g_eye.y+=0.1f;
		g_at.y+=0.1f;

	}

	//��
	if(GetKeyboardPress(DIK_E))
	{
		g_eye.y-=0.1f;
		g_at.y-=0.1f;

	}


	//����]
	if(GetKeyboardPress(DIK_J))
	{
		g_spin=-S_SPEED;
		D3DXMatrixRotationY(&mtx,g_spin);
		D3DXVECTOR3 dir =g_at-g_eye;
		D3DXVec3TransformNormal(&dir,&dir,&mtx);
		D3DXVec3TransformNormal(&g_front,&g_front,&mtx);
		D3DXVec3TransformNormal(&g_right,&g_right,&mtx);
		D3DXVec3TransformNormal(&g_up,&g_up,&mtx);
		dir+=g_eye;
		g_at=dir;
	}
	if(GetKeyboardPress(DIK_U))
	{
		g_spin=-S_SPEED;
		D3DXMatrixRotationY( &mtx,g_spin);
		D3DXVECTOR3 dir =g_eye-g_at;
		D3DXVec3TransformNormal(&dir,&dir,&mtx);
		D3DXVec3TransformNormal(&g_front,&g_front,&mtx);
		D3DXVec3TransformNormal(&g_right,&g_right,&mtx);
		D3DXVec3TransformNormal(&g_up,&g_up,&mtx);
		dir+=g_at;
		g_eye=dir;
	}
	//�E��]
	if(GetKeyboardPress(DIK_O))
	{
		g_spin=S_SPEED;
		D3DXMatrixRotationY( &mtx,g_spin);
	//	D3DXVECTOR3 dir =g_at-g_eye;
		D3DXVECTOR3 dir =g_eye-g_at;
		D3DXVec3TransformNormal(&dir,&dir,&mtx);
		D3DXVec3TransformNormal(&g_front,&g_front,&mtx);
		D3DXVec3TransformNormal(&g_right,&g_right,&mtx);
		D3DXVec3TransformNormal(&g_up,&g_up,&mtx);
	//	dir+=g_eye;
		dir+=g_at;
	//	g_at=dir;
		g_eye=dir;
	}

	if(GetKeyboardPress(DIK_L))
	{
		g_spin=S_SPEED;
		D3DXMatrixRotationY( &mtx,g_spin);
		D3DXVECTOR3 dir =g_at-g_eye;
	//	D3DXVECTOR3 dir =g_eye-g_at;
		D3DXVec3TransformNormal(&dir,&dir,&mtx);
		D3DXVec3TransformNormal(&g_front,&g_front,&mtx);
		D3DXVec3TransformNormal(&g_right,&g_right,&mtx);
		D3DXVec3TransformNormal(&g_up,&g_up,&mtx);
		dir+=g_eye;
	//	dir+=g_at;
		g_at=dir;
	//	g_eye=dir;
	}


	//���]
	if(GetKeyboardPress(DIK_K))
	{
		g_spin=-S_SPEED;
		D3DXMatrixRotationAxis( &mtx,&g_right,g_spin);
		D3DXVECTOR3 dir =g_at-g_eye;
		D3DXVec3TransformNormal(&dir,&dir,&mtx);
		D3DXVec3TransformNormal(&g_front,&g_front,&mtx);
		D3DXVec3TransformNormal(&g_right,&g_right,&mtx);
		D3DXVec3TransformNormal(&g_up,&g_up,&mtx);

		dir+=g_eye;
		g_at=dir;
	}

	//����]
	if(GetKeyboardPress(DIK_I))
	{
		g_spin=S_SPEED;
		D3DXMatrixRotationAxis( &mtx,&g_right,g_spin);
		D3DXVECTOR3 dir =g_at-g_eye;
		D3DXVec3TransformNormal(&dir,&dir,&mtx);
		D3DXVec3TransformNormal(&g_front,&g_front,&mtx);
		D3DXVec3TransformNormal(&g_right,&g_right,&mtx);
		D3DXVec3TransformNormal(&g_up,&g_up,&mtx);
		dir+=g_eye;
		g_at=dir;
	}

*/

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();


	D3DXMatrixPerspectiveFovLH( &g_mtxProjection,						//�o��
								D3DX_PI/3/*�܂���D3DXToradian(60)*/,	//��p
								(float)SCREEN_WIDTH/SCREEN_HEIGHT,		//�A�X�y�N�g��
								0.1f,									//�j�A�N���b�v�̐ݒ�(0�ɂ��Ă͂����Ȃ�)
								1000.0f);								//�t�@�[�N���b�v�̐ݒ�

	clip+=0.5;

	D3DXMatrixLookAtLH( &g_mtxView, &g_eye, &g_at, &g_up );

	pDevice->SetTransform(D3DTS_VIEW ,&g_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION,&g_mtxProjection);

}



D3DXVECTOR3* Getg_at(void)
{
	return &g_at;
}

D3DXVECTOR3* Getg_eye(void)
{
	return &g_eye;
}

D3DXMATRIX* GetmtxView(void)
{
	return &g_mtxView;
}
