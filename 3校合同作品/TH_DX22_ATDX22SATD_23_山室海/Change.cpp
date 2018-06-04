#include "Change.h"
#include "main.h"
#include "Camera.h"
#include "model.h"
#include "Sound.h"


#define EXPLOSION_MAX (40)
#define EXPLOSION_WIDTH		(256)
#define EXPLOSION_HEIGHT	(256)
#define EXPLOSION_PATTERN_MAX (8)

typedef struct
{// 頂点の構造体
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}VERTEX_3D_CHANGE;

typedef struct
{
	D3DXMATRIX g_mtxWorld;
	D3DXVECTOR3 pos;
	int count;
	int nPattern;
	bool use;
	bool type;
}CHANGE;


static D3DXMATRIX k_mtxWorld;

static CHANGE change;

static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 ch_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ch_pIndexBuffer = NULL;

static const TEXTURE_CHANGE g_aTexture[2]={
						{"texture\\change_effect1.png",1024,512},
						{"texture\\change_effect2.png",1024,512},
									};
static LPDIRECT3DTEXTURE9 g_pTextures[2]; 

static VERTEX_3D_CHANGE v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2 (0.25f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2(0.0f,0.5f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,122) ,D3DXVECTOR2 (0.25f,0.5f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};

void InitChange (void)
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, "デバイスが読み込めませんでした", "エラーメッセージ", MB_OK);
	}




	HRESULT hr;

	for(int i=0 ; i<2 ; i++)
	{

		hr = D3DXCreateTextureFromFile(
			pDevice,															// デバイス
			g_aTexture[i].fileName,												// ファイル名（実行ファイルと同じ場所だったらそのまま）
			&g_pTextures[i]);													// テクスチャ保持アドレスのアドレス

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
			MessageBox(NULL, "テクスチャが読み込めませんでした", "エラーメッセージ", MB_OK);
		}
	}
	

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_CHANGE) * 4, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D_CHANGE,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&ch_pVertexBuffer, //管理者のポインタ
								NULL);


	if( FAILED (hr) )
	{
		MessageBox(NULL, "頂点バッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}



	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&ch_pIndexBuffer, //管理者のポインタ
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "インデックスバッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}


	 CreateVertex_ch();

	 change.use=false;

}
void UninitChange(void)
{
}
void UpdateChange(void)
{
	D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

	g_mtxInvView._41 = 0.0f;
	g_mtxInvView._42 = 0.0f;
	g_mtxInvView._43 = 0.0f;

	for(int i = 0 ; i < EXPLOSION_MAX ; i++)
	{
		if(change.use)
		{
			D3DXMatrixScaling(&k_mtxWorld,3.5,3.5,1);
			D3DXMatrixTranslation( &change.g_mtxWorld, GetPlayerPos()->x ,GetPlayerPos()->y  ,GetPlayerPos()->z-1);
			change.g_mtxWorld=k_mtxWorld*change.g_mtxWorld;
			change.g_mtxWorld=g_mtxInvView*change.g_mtxWorld;

		}
	}
}
void DrawChange(void)
{
LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D_CHANGE);//今から色と頂点を送るという意味

		pDevice->SetStreamSource(0,
		ch_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_CHANGE)); //１頂点分のサイズ

		pDevice->SetIndices(ch_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures[0]);						// テクスチャ保持アドレス

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //ライティングオン
		


		//αテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

//---------描画処理------------------//



		if(change.use)
		{
			if(change.type)
			{
				change.count++;
			
				int nPattern = change.count/2;

				v[0].texcoord = D3DXVECTOR2(0.0f+((nPattern%5)*0.2),0.0f+((nPattern/5)*0.166));
				v[1].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.0f+(nPattern/5*0.166));
				v[2].texcoord =	D3DXVECTOR2(0.0f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166)) ;
				v[3].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166));

				CreateVertex_ch();

				if(nPattern>29)
				{
	 				change.use=false;
				}


				//各種行列の設定(好きなタイミングで設定してOK)
				pDevice->SetTransform(D3DTS_WORLD,&change.g_mtxWorld);

				pDevice->SetTexture(
				0,									// テクスチャステージ
				g_pTextures[0]);						// テクスチャ保持アドレス

				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//プリミティブタイプ
											0,					//ベース
											0,					//インデックス最小
											4,					//頂点数
											0,
											2);				//プリミティブ数
			}


		if(!change.type)
			{
				change.count++;
			
				int nPattern = change.count/2;

				v[0].texcoord = D3DXVECTOR2(0.0f+((nPattern%5)*0.2),0.0f+((nPattern/5)*0.166));
				v[1].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.0f+(nPattern/5*0.166));
				v[2].texcoord =	D3DXVECTOR2(0.0f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166)) ;
				v[3].texcoord =	D3DXVECTOR2(0.2f+(nPattern%5*0.2),0.166f+(nPattern/5*0.166));

				CreateVertex_ch();

				if(nPattern>29)
				{
	 				change.use=false;
				}


				//各種行列の設定(好きなタイミングで設定してOK)
				pDevice->SetTransform(D3DTS_WORLD,&change.g_mtxWorld);

				pDevice->SetTexture(
				0,									// テクスチャステージ
				g_pTextures[1]);						// テクスチャ保持アドレス

				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//プリミティブタイプ
											0,					//ベース
											0,					//インデックス最小
											4,					//頂点数
											0,
											2);				//プリミティブ数
			}

		}

	
}
bool CreateChage(D3DXVECTOR3 Pos , bool type)
{
	if(change.use==false)
	{
		change.use=true;
		change.count=0;
		change.pos=Pos;
		change.type=type;
		return true;
	}
	return false;
}

void CreateVertex_ch(void)
{
	VERTEX_3D_CHANGE* pV;
	LPWORD pIndex;

	ch_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	ch_pVertexBuffer->Unlock();


	ch_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	ch_pIndexBuffer->Unlock();
}