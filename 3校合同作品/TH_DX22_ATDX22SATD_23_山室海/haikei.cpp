#include "haikei.h"
#include "main.h"

typedef struct
{// 頂点の構造体
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}VERTEX_3D_HAIKEI;



static D3DXMATRIX g_mtxWorld;


static D3DXMATRIX k_mtxWorld;


static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 ha_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ha_pIndexBuffer = NULL;

static const TEXTURE_HAIKEI g_aTexture={"texture\\milky-way-474931_640.jpg",640,425};
static LPDIRECT3DTEXTURE9 g_pTextures; 

static VERTEX_3D_HAIKEI v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0f,1.0f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};




void InitHaikei(void)
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
	

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_HAIKEI) * 4, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D_HAIKEI,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&ha_pVertexBuffer, //管理者のポインタ
								NULL);


	if( FAILED (hr) )
	{
		MessageBox(NULL, "頂点バッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}



	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&ha_pIndexBuffer, //管理者のポインタ
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "インデックスバッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}

	VERTEX_3D_HAIKEI* pV;
	LPWORD pIndex;

	ha_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	ha_pVertexBuffer->Unlock();


	ha_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	ha_pIndexBuffer->Unlock();

}
void UninitHaikei(void)
{
	if(ha_pVertexBuffer)
	{
		ha_pVertexBuffer->Release();
		ha_pVertexBuffer = NULL;

	}

	if(ha_pIndexBuffer)
	{
		ha_pIndexBuffer->Release();
		ha_pIndexBuffer = NULL;

	}

		if (g_pTextures!= NULL)
		{// テクスチャ保持の開放
			g_pTextures->Release();
		}

}
void UpdateHaikei(void)
{
		D3DXMatrixScaling(&g_mtxWorld,500,500,1);
		D3DXMatrixTranslation( &k_mtxWorld,0,0,300);
		g_mtxWorld*=k_mtxWorld;
}
void DrawHaikei(void)
{
LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D_HAIKEI);//今から色と頂点を送るという意味

		pDevice->SetStreamSource(0,
		ha_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_HAIKEI)); //１頂点分のサイズ

		pDevice->SetIndices(ha_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures);						// テクスチャ保持アドレス

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //ライティングオン
		


		//αテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

//---------描画処理------------------//



			//各種行列の設定(好きなタイミングで設定してOK)
			pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

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