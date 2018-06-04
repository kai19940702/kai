#include "main.h"
#include "Polygon3DTset.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "model.h"

#define CUBE_NUM (5)



//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************


static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;


static D3DXMATRIX g_mtxWorld[5];

static float fRotY=0;

static D3DXVECTOR3 pos;

static const TEXTURE2 g_aTexture[] = {
	{"texture\\shadow000.jpg", 80,80},

};
// 配列数える
static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(g_aTexture);

static LPDIRECT3DTEXTURE9 g_pTextures[ TEXTURE_FILE_COUNT ]; 
static D3DCOLOR g_PolygonColor = 0xffffffff;




static VERTEX_3D v[] = {
		//前
		{ D3DXVECTOR3(-0.5,0.0,0.5) ,D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f)  },//0
		{ D3DXVECTOR3(0.5,0.0,-0.5)  ,D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,1.0f) },//1
		{ D3DXVECTOR3(0.5,0.0,0.5),D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,0.0f) },//2
		{ D3DXVECTOR3(-0.5,0.0,-0.5) ,D3DXVECTOR3(0.0,0.0,-1.0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f)},//3
		
	};


static WORD index[]={ 0, 2, 3,	//	WORDは2バイト
					  1, 3, 2};







/*=========================================================
		初期化処理
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
			pDevice,															// デバイス
			g_aTexture[i].fileName,												// ファイル名（実行ファイルと同じ場所だったらそのまま）
			&g_pTextures[i]);													// テクスチャ保持アドレスのアドレス

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
			MessageBox(hWnd, "テクスチャが読み込めませんでした", "エラーメッセージ", MB_OK);
			return false;
		}
	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *4, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&g_pVertexBuffer, //管理者のポインタ
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(hWnd, "頂点バッファが作成されませんでした", "エラーメッセージ", MB_OK);
		return false;
	}




	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&g_pIndexBuffer, //管理者のポインタ
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(hWnd, "インデックスバッファが作成されませんでした", "エラーメッセージ", MB_OK);
		return false;
	}

	CreateVertex();


	return true;
}
/*=========================================================
		終了処理
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
		{// テクスチャ保持の開放
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}
/*=========================================================
		更新処理
===========================================================*/
void Polygon3DTestUpdate(void)
{




	pos=*GetPlayerPos();
	D3DXMatrixTranslation( &g_mtxWorld[0],pos.x,0.1,pos.z);


}
/*=========================================================
		描画処理
===========================================================*/
void Polygon3DTestDraw(void)
{
	//マテリアル作成
	
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D);//今から色と頂点を送るという意味


		pDevice->SetStreamSource(0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_3D)); //１頂点分のサイズ

		pDevice->SetIndices(g_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures[0]);						// テクスチャ保持アドレス

//---------描画処理------------------//

	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);


		//各種行列の設定(好きなタイミングで設定してOK)
		pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld[0]);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//プリミティブタイプ
									0,					//ベース
									0,					//インデックス最小
									4,					//頂点数
									0,
									2);				//プリミティブ数


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
