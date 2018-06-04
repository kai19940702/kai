#include "main.h"
#include "shadow.h"
#include "BillBoard.h"
#include "model.h"

#define SHADOW_MAX (100)

typedef struct
{
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}TEXTURE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXMATRIX g_mtxWorld;
	bool b_use;
}SHADOW;

static TEXTURE v[] = {
		//前
		{ D3DXVECTOR3(-0.5,0.0,0.5)  ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,0.0f)  },//0
		{ D3DXVECTOR3(0.5,0.0,-0.5)  ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,0.0f) },//1
		{ D3DXVECTOR3(0.5,0.0,0.5)   ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1.0f,0.0f) },//2
		{ D3DXVECTOR3(-0.5,0.0,-0.5) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f)},//3
		
	};


static WORD Index[]={ 0, 2, 3,	//	WORDは2バイト
					  1, 3, 2};

static LPDIRECT3DVERTEXBUFFER9 s_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 s_pIndexBuffer = NULL;

static SHADOW shadow;

static const TEXTURE_SHADOW g_aTexture={"texture\\ball.png",225,225};


static LPDIRECT3DTEXTURE9 g_pTextures; 

void InitShadow(void)
{
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

		hr = pDevice->CreateVertexBuffer(sizeof(TEXTURE) * 4, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D_SHADOW,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&s_pVertexBuffer, //管理者のポインタ
								NULL);

	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&s_pIndexBuffer, //管理者のポインタ
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "インデックスバッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}

	TEXTURE * pV;
	LPWORD pIndex;

	s_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	s_pVertexBuffer->Unlock();


	s_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	s_pIndexBuffer->Unlock();

}
void UninitShadow(void)
{
	if(s_pVertexBuffer)
	{
		s_pVertexBuffer->Release();
		s_pVertexBuffer = NULL;

	}

	if(s_pIndexBuffer)
	{
		s_pIndexBuffer->Release();
		s_pIndexBuffer = NULL;

	}

	if (g_pTextures!= NULL)
	{// テクスチャ保持の開放
		g_pTextures->Release();
		g_pTextures = NULL;
	}

}
void UpdateShadow(void)
{

	shadow.pos=*GetPlayerPos();
	D3DXMatrixTranslation( &shadow.g_mtxWorld,shadow.pos.x,0.5,shadow.pos.z);
}
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D_SHADOW);//今から色と頂点を送るという意味

		pDevice->SetStreamSource(0,
		s_pVertexBuffer,
		0,
		sizeof(SHADOW)); //１頂点分のサイズ

		pDevice->SetIndices(s_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures);						// テクスチャ保持アドレス

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //ライティングオン
		
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);


			//各種行列の設定(好きなタイミングで設定してOK)
			pDevice->SetTransform(D3DTS_WORLD,&shadow.g_mtxWorld);

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
/*
void CreateShadow(void)
{
	for(int i=0 ; i<SHADOW_MAX ;i++)
	{
		if(!shadow[i].b_use)
		{
			shadow[i].b_use=true;
//			shadow[i].pos=*GetPos(i);
			break;
		}
	}
}
*/