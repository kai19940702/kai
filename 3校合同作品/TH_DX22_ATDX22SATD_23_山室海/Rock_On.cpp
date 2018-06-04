#include "Rock_On.h"
#include "main.h"
#include "Camera.h"
#include "Enemy.h"



#define ROCKON_MAX (20)

typedef struct
{// 頂点の構造体
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}VERTEX_3D_ROCK_ON;

typedef struct
{
	D3DXMATRIX g_mtxWorld;
	D3DXVECTOR3 pos;
	int num;
	float size;
	bool use;

}ROCK_ON;


static D3DXMATRIX k_mtxWorld;

static ROCK_ON rock_on[ROCKON_MAX];

static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 rock_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 rock_pIndexBuffer = NULL;

static const TEXTURE_ROCKON gr_aTexture={"texture\\rock_on.png",1024,512};
static LPDIRECT3DTEXTURE9 gr_pTextures; 

static VERTEX_3D_ROCK_ON v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,200) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(0.5,0.5,0) ,D3DCOLOR_RGBA(255,255,255,200) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,200) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,200) ,D3DXVECTOR2 (1.0f,1.0f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};

void InitRock_On(void)
{
LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, "デバイスが読み込めませんでした", "エラーメッセージ", MB_OK);
	}

	for(int i=0 ; i< ROCKON_MAX ;i++)
	{
		rock_on[i].use=false;
		rock_on[i].num=-1;
		rock_on[i].size=16;

	}



	HRESULT hr;


		hr = D3DXCreateTextureFromFile(
			pDevice,															// デバイス
			gr_aTexture.fileName,												// ファイル名（実行ファイルと同じ場所だったらそのまま）
			&gr_pTextures);													// テクスチャ保持アドレスのアドレス

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
			MessageBox(NULL, "テクスチャが読み込めませんでした", "エラーメッセージ", MB_OK);
		}
	

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_ROCK_ON) * 4, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D_ROCKON,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&rock_pVertexBuffer, //管理者のポインタ
								NULL);


	if( FAILED (hr) )
	{
		MessageBox(NULL, "頂点バッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}



	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&rock_pIndexBuffer, //管理者のポインタ
								NULL);
	if( FAILED (hr) )
	{
		MessageBox(NULL, "インデックスバッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}


	VERTEX_3D_ROCK_ON* pV;
	LPWORD pIndex;

	rock_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	rock_pVertexBuffer->Unlock();


	rock_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,Index,sizeof(Index));
	rock_pIndexBuffer->Unlock();

}
void UninitRock_On(void)
{
	if(rock_pVertexBuffer)
	{
		rock_pVertexBuffer->Release();
		rock_pVertexBuffer = NULL;

	}

	if(rock_pIndexBuffer)
	{
		rock_pIndexBuffer->Release();
		rock_pIndexBuffer = NULL;

	}

		if (gr_pTextures!= NULL)
		{// テクスチャ保持の開放
			gr_pTextures->Release();
			gr_pTextures = NULL;
		}
}
void UpdateRock_On(void)
{
	D3DXMatrixInverse(&g_mtxInvView,NULL,GetmtxView());

	g_mtxInvView._41 = 0.0f;
	g_mtxInvView._42 = 0.0f;
	g_mtxInvView._43 = 0.0f;

	for(int i = 0 ; i < ROCKON_MAX ; i++)
	{
		if(rock_on[i].use)
		{
			D3DXMatrixScaling(&k_mtxWorld,rock_on[i].size,rock_on[i].size,1);
			D3DXMatrixTranslation( &rock_on[i].g_mtxWorld, GetEnemyPos( rock_on[i].num).x ,GetEnemyPos( rock_on[i].num).y  ,GetEnemyPos( rock_on[i].num).z);
			rock_on[i].g_mtxWorld=k_mtxWorld*rock_on[i].g_mtxWorld;
			rock_on[i].g_mtxWorld=g_mtxInvView*rock_on[i].g_mtxWorld;

			if(rock_on[i].size>8)
			{
				rock_on[i].size-=0.5;
			}

			if(GetEnemyPos( rock_on[i].num).z<10)
			{
				 Destroty_Rock_On (i);
			}

		}
	}
}
void DrawRock_On(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D_ROCKON);//今から色と頂点を送るという意味

		pDevice->SetStreamSource(0,
		rock_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_ROCK_ON)); //１頂点分のサイズ

		pDevice->SetIndices(rock_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		gr_pTextures);						// テクスチャ保持アドレス

		pDevice->SetRenderState( D3DRS_LIGHTING, FALSE ); //ライティングオン
		


		//αテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,15);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

//---------描画処理------------------//


	for(int i = 0 ; i < ROCKON_MAX; i++)
	{
		if(rock_on[i].use)
		{
			//各種行列の設定(好きなタイミングで設定してOK)
			pDevice->SetTransform(D3DTS_WORLD,&rock_on[i].g_mtxWorld);

			pDevice->SetTexture(
			0,									// テクスチャステージ
			gr_pTextures);						// テクスチャ保持アドレス

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//プリミティブタイプ
										0,					//ベース
										0,					//インデックス最小
										4,					//頂点数
										0,
										2);				//プリミティブ数
		}

	}
}
void CreateRock_On(void)
{

	for(int i=0 ; i<ROCKON_MAX ; i++)
	{
		if(!rock_on[i].use)
		{

			for(int j=0 ; j<20 ; j++)
			{
				if(GetEnemyPos(j).z<80&&GetEnemyPos(j).z>5)
				{
					if(!GetEnemyRock(j))
					{
						rock_on[i].use=true;
						RockOn_Enemy(j,i);
						rock_on[i].pos=GetEnemyPos(j);
						rock_on[i].num=j;
						rock_on[i].size=16;
						break;
					}
				}
			}
			break;
		}
	}
}
void Destroty_Rock_On (int index)
{
	rock_on[index].use=false;
//	DestroyEnemy_rock(rock_on[index].num);
	rock_on[index].num=-1;
}

