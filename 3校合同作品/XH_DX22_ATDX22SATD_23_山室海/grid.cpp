#include "main.h"
#include "grid.h"
#include <d3d9.h>
#include <d3dx9.h>


//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************

static D3DXMATRIX g_mtxWorld;


static float fRotX=0;
static float fRotY=0;
static float fRotZ=0;

static int count=0;
/*=========================================================
		初期化処理
===========================================================*/
void GridInit(void)
{

}
/*=========================================================
		終了処理
===========================================================*/
void GridUninit(void)
{

}
/*=========================================================
		更新処理
===========================================================*/
void GridUpdate(void)
{


	//ワールド変換行列
	//何もしない行列(単位行列)
	D3DXMatrixIdentity( &g_mtxWorld );
	//D3DXMatrixRotationY( &g_mtxWorld,fRotY);
	




								
}
/*=========================================================
		描画処理
===========================================================*/
void GridDraw(void)
{	
	GRID v[44];
	int j=0;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE); //ライティングオフ

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



	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D);//今から色と頂点を送るという意味


	//各種行列の設定(好きなタイミングで設定してOK)
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

	pDevice->DrawPrimitiveUP(D3DPT_LINELIST,							// プリミティブタイプ（図形の形）
								  22,									// プリミティブの数（図形の数）
								  &v[0],								// 頂点へのポインタ
						  		  sizeof(GRID));					// 1個の頂点のサイズ


}