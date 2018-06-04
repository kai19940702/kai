//******************************************************************
//						[Camera.h]											
//			Author：	作成日：2017/10/31			
//******************************************************************

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Main.h"

class CCamera 
{
private:

D3DXMATRIX g_mtxView;
 D3DXMATRIX g_mtxProjection;

		// カメラ座標,視点
 D3DXVECTOR3 g_eye;
 D3DXVECTOR3 g_at;

 D3DXVECTOR3 g_front , g_right;	//必ず単位ベクトル
 D3DXVECTOR3 g_up;
 HWND m_hWnd;

public:
	CCamera();
	~CCamera();
	void Init(HWND hWnd);
	void Draw(){};
	void Uninit();
	void Update();

	
	D3DXVECTOR3* CalcScreenToXZ(D3DXVECTOR3* pout,int Sx,int Sy,int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj);

	D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout,int Sx,int Sy,float fZ,int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj);

};


#endif