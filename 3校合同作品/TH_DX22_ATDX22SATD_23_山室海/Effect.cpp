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

	構造体

====================================================================================================================================*/

typedef struct
{
	 D3DXMATRIX g_mtxWorld_k;
	D3DXMATRIX g_mtxWorld;
	 D3DXVECTOR3 vPos;
	 bool color;
	 int nLimit;
	 int nBirth; //作られたときのフレーム数
	 int nAlpha;
	 bool bEffect;
	 int  Size;
}EFFECT;


typedef struct
{// 頂点の構造体
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}VERTEX_3D_EFFECT;

/*====================================================================================================================================-

	グローバル変数

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

	初期化関数

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
		MessageBox(NULL, "デバイスが読み込めませんでした", "エラーメッセージ", MB_OK);
	}




	HRESULT hr;

		hr = D3DXCreateTextureFromFile(
			pDevice,															// デバイス
			g_aTexture.fileName,												// ファイル名（実行ファイルと同じ場所だったらそのまま）
			&g_pTextures);													// テクスチャ保持アドレスのアドレス

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
			MessageBox(NULL, "テクスチャが読み込めませんでした", "エラーメッセージ", MB_OK);
		}


	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_EFFECT) * 4, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D_EFFECT,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&ef_pVertexBuffer, //管理者のポインタ
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(NULL, "頂点バッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}




	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&ef_pIndexBuffer, //管理者のポインタ
								NULL);

	if( FAILED (hr) )
	{
		MessageBox(NULL, "インデックスバッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}

		for( int i = 0 ; i<EFFECT_MAX ; i++ )
		{

			g_Effects[i].bEffect = false;

		}

	 CreateVertex_ef();

}

/*====================================================================================================================================-

	終了関数

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
		{// テクスチャ保持の開放
			g_pTextures->Release();
			g_pTextures = NULL;
		}
	
}

/*====================================================================================================================================-

	更新関数

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
			//寿命が尽きたか
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

	描画関数

====================================================================================================================================*/
void DrawEffect(void) 
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D_EFFECT);//今から色と頂点を送るという意味

		pDevice->SetStreamSource(0,
		ef_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_EFFECT)); //１頂点分のサイズ

		pDevice->SetIndices(ef_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures);						// テクスチャ保持アドレス

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //ライティングオン

		pDevice->SetRenderState( D3DRS_ZENABLE , FALSE );

		//加算合成の設定
		pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

		//αテスト
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	//	pDevice->SetRenderState(D3DRS_ALPHAREF,);
	//	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for(int i = EFFECT_MAX ; i>0 ; i--)
	{
		
		if(g_Effects[i].bEffect)
		{


			//各種行列の設定(好きなタイミングで設定してOK)
			pDevice->SetTransform(D3DTS_WORLD,&g_Effects[i].g_mtxWorld);

			pDevice->SetTexture(
			0,									// テクスチャステージ
			g_pTextures);						// テクスチャ保持アドレス

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//プリミティブタイプ
										0,					//ベース
										0,					//インデックス最小
										4,					//頂点数
										0,
										2);				//プリミティブ数
		}
	}
	//α値を計算
	//年齢が０の時...α1.0f(255)
	//年齢 ==寿命の時...α0.0f(0)

	//丸を描画


	//合成の設定を元に戻す
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState( D3DRS_ZENABLE , TRUE );



}

/*====================================================================================================================================-

	エフェクト作成関数

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