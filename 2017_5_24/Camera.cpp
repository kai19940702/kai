#include "Renderer.h"
#include "Camera.h"
#include "CPlayer.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include "debug.h"
#include "CFiled.h"
//----------------------------------------------------//
//					�������֐�						�@//
//----------------------------------------------------//

CCamera::CCamera()
{
	 g_eye=D3DXVECTOR3( 0.0f , 5.0f ,-10.0f);
	 g_at=D3DXVECTOR3( 0.0f , 0.0f ,0.0f );

	 g_up=D3DXVECTOR3 ( 0.0f , 1.0f , 0.0f);
}
CCamera::~CCamera()
{
}
void CCamera::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}
//----------------------------------------------------//
//					�I���֐�						�@//
//----------------------------------------------------//
void CCamera::Uninit()
{

}
//----------------------------------------------------//
//					�X�V�֐�						�@//
//----------------------------------------------------//
void CCamera::Update()
{
	

	//�O�����̃x�N�g�������
	
	g_front=g_at-g_eye;
	//�P�ʃx�N�g����
//	D3DXVec3Normalize(&g_front,&g_front);

	g_at =CPlayer::GetPlayerPos();


	g_eye = g_at-10*(CPlayer::GetPlayerfront());

	g_eye.y+=4;

	D3DXVECTOR3 vec=g_front;
	vec.y=0;
	D3DXVec3Normalize(&vec,&vec);

	D3DXVec3Cross(&g_right,&g_front,&g_up);
	D3DXVec3Normalize(&g_right,&g_right);

	D3DXMATRIX mtx;




	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMATRIX g_mtxView;	//�r���[�s��
	D3DXMATRIX g_mtxProjection;//�v���W�F�N�V�����s��


	//�v���W�F�N�V����(�p�[�X�y�N�e�B�u)�s��̍쐬
	//��p�̐ݒ聁�Y�[���C���Y�[���A�E�g
	D3DXMatrixPerspectiveFovLH( &g_mtxProjection,						//�o��
								D3DX_PI/3/*�܂���D3DXToradian(60)*/,	//��p
								(float)SCREEN_WIDTH/SCREEN_HEIGHT,		//�A�X�y�N�g��
								0.1f,									//�j�A�N���b�v�̐ݒ�(0�ɂ��Ă͂����Ȃ�)
								1000.0f);								//�t�@�[�N���b�v�̐ݒ�

	D3DXMatrixLookAtLH( &g_mtxView, &g_eye, &g_at, &g_up );

	pDevice->SetTransform(D3DTS_VIEW ,&g_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION,&g_mtxProjection);


	POINT MousePos;
	GetCursorPos(&MousePos);
	ScreenToClient(m_hWnd,&MousePos);

	



	DebugString(0, 0,"X���W=%d Y���W=%d",(int)MousePos.x,(int)MousePos.y);





}

D3DXVECTOR3* CCamera::CalcScreenToXZ(D3DXVECTOR3* pout,int Sx,int Sy,int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj)
 {
   D3DXVECTOR3 nearpos;
   D3DXVECTOR3 farpos;
   D3DXVECTOR3 ray;
   CCamera::CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
   CCamera::CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   // ���Ƃ̌������N���Ă���ꍇ�͌�_��
   // �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
   if( ray.y <= 0 ) {
      // ����_
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else {
      *pout = farpos;
   }

   return pout;
}


D3DXVECTOR3* CCamera::CalcScreenToWorld(
   D3DXVECTOR3* pout,
   int Sx,  // �X�N���[��X���W
   int Sy,  // �X�N���[��Y���W
   float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,
   int Screen_h,
   D3DXMATRIX* View,
   D3DXMATRIX* Prj
) {
   // �e�s��̋t�s����Z�o
   D3DXMATRIX InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3(Sx,Sy,fZ), &tmp );

   return pout;
}