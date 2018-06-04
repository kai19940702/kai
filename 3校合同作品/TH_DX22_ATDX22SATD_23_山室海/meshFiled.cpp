#include "MeshFiled.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "polygon.h"


static int  SIZE_Z =0;
static int  SIZE_X =0;
static int SIZE_PRIMITIVE =1;

static int  SEPARATE_Z = 0;
static int  SEPARATE_X = 0;

static int  POS_NUM =0;
static int  INDEX_NUM =0; 


typedef struct
{// 頂点の構造体
	D3DXVECTOR3 pos;		// 座標
	D3DXVECTOR3 normal;		//法線
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}VERTEX_3D_FILED;


typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE2;

void CreateVertex_filed(void);

static LPDIRECT3DVERTEXBUFFER9 f_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 f_pIndexBuffer = NULL;


static VERTEX_3D_FILED* v;
static WORD* Index_Filed;


static D3DXMATRIX g_mtxWorld[5];



static const TEXTURE2 g_a_mTexture[] ={
				{"texture\\filed.jpg", 225,225},
	};
// 配列数える

static LPDIRECT3DTEXTURE9 g_pTextures[2]; 


void MeshfFiledFileInit(int size_x , int size_Z ,int quads_size)
{
	int i=0;

	HRESULT hr;
	SIZE_Z=size_Z;
	SIZE_X=size_x;
	SEPARATE_Z = (size_Z/quads_size);
    SEPARATE_X = (size_x/quads_size);

	POS_NUM = ((SEPARATE_Z+1)*(SEPARATE_X+1));
	INDEX_NUM = (POS_NUM + ((SEPARATE_Z-1)*(SEPARATE_X+1))+((SEPARATE_Z-1)*2));



	v = new VERTEX_3D_FILED[ POS_NUM ];		// メッシュ情報を確保
	Index_Filed = new WORD[ INDEX_NUM ];// テクスチャを確保

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (int i = 0; i < 1; i++)
	{
		hr = D3DXCreateTextureFromFile(
			pDevice,															// デバイス
			g_a_mTexture[i].fileName,												// ファイル名（実行ファイルと同じ場所だったらそのまま）
			&g_pTextures[i]);													// テクスチャ保持アドレスのアドレス

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
			MessageBox(NULL, "テクスチャが読み込めませんでした", "エラーメッセージ", MB_OK);
		}
	}


		


	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_FILED) *((SEPARATE_Z+1)*(SEPARATE_X+1)), //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D_FILED,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&f_pVertexBuffer, //管理者のポインタ
								NULL);
	if( FAILED(hr) )
	{
		MessageBox(NULL, "頂点バッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}


	 hr = pDevice->CreateIndexBuffer(sizeof(WORD) *(((SEPARATE_Z+1)*(SEPARATE_X+1))+((SEPARATE_Z-1)*(SEPARATE_X+1))+((SEPARATE_Z-1)*2)), //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&f_pIndexBuffer, //管理者のポインタ
								NULL);

	 if( FAILED (hr) )
	{
		MessageBox(NULL, "INDEXバッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}
	 

	float pos_z=(float)(SEPARATE_Z+1)/2;
	float pos_x=-(float)((SEPARATE_X+1)/2);
	int index_x=0;
	int index_y=0;

	while(i!=POS_NUM)
	{
		v[i].pos.x=pos_x;
		v[i].pos.z=pos_z;
		v[i].pos.y=0;
		v[i].normal = D3DXVECTOR3(0.0,1.0,0.0);
		v[i].color = D3DCOLOR_RGBA(255,255,255,255);
		v[i].texcoord.x = index_x; 
		v[i].texcoord.y = index_y;

		pos_x++;
		index_x++;
		
		if(pos_x>(SEPARATE_X+1)/2)
		{

			index_y++;
			pos_z--;
			pos_x=-(float)((SEPARATE_X+1)/2);
			index_x=0;
		}
		i++;
	}


	i=0;

	int count = (SEPARATE_X+1);
	int count2 = 0;


	while(i!=INDEX_NUM)
	{
		Index_Filed[ i ] = count;
		i++;
		Index_Filed[ i ] = count2;

		if( (count2+1) % (SEPARATE_X+1) ==  0 && i!=(INDEX_NUM-1) )
		{
			i++;
			Index_Filed[ i ] = count2;
			i++;
			Index_Filed[ i ] = (count+1);
		}

		count++;
		count2++;

		i++;
		
	}

	 CreateVertex_filed();

}
void MeshfFiledUninit(void)
{
		if(f_pVertexBuffer)
	{
		f_pVertexBuffer->Release();
		f_pVertexBuffer = NULL;

	}

	if(f_pIndexBuffer)
	{
		f_pIndexBuffer->Release();
		f_pIndexBuffer = NULL;

	}

}
void MeshfFiledUpdate(void)
{
	D3DXMatrixIdentity( &g_mtxWorld[0]);


}
void MeshfFiledDraw(void)
{
	//マテリアル作成
	D3DMATERIAL9 mat;
	//ゼロ初期化
	ZeroMemory(&mat,sizeof(mat));

	//マテリアルカラー
	mat.Diffuse.r=1.0f;
	mat.Diffuse.g=1.0f;
	mat.Diffuse.b=1.0f;
	mat.Diffuse.a=1.0f;

	//環境光
	mat.Ambient.r=0.6f;
	mat.Ambient.g=0.6f;
	mat.Ambient.b=0.6f;
	mat.Ambient.a=1.0f;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D_FILED);//今から色と頂点を送るという意味


	pDevice->SetMaterial(&mat);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);//法線正規化
	pDevice->SetRenderState(D3DRS_AMBIENT,D3DXCOLOR(0.3f,0.3f,0.3f,1.0f));

		pDevice->SetStreamSource(0,
		f_pVertexBuffer,
		0,
		sizeof(VERTEX_3D_FILED)); //１頂点分のサイズ

		pDevice->SetIndices(f_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures[0]);						// テクスチャ保持アドレス

//		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

//---------描画処理------------------//




		//各種行列の設定(好きなタイミングで設定してOK)
		pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld[0]);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブタイプ
									0,					//ベース
									0,					//インデックス最小
									(SEPARATE_Z+1)*(SEPARATE_X+1),					//頂点数
									0,
									((SEPARATE_Z)*(SEPARATE_X)*2+((SEPARATE_Z-1)*4)));				//プリミティブ数

	

}

void CreateVertex_filed(void)
{
	VERTEX_3D_FILED* pV;
	LPWORD f_pIndex;

	f_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(VERTEX_3D_FILED)*POS_NUM);
	f_pVertexBuffer->Unlock();


	f_pIndexBuffer->Lock(0,0,(void**)&f_pIndex,D3DLOCK_DISCARD);
	memcpy(f_pIndex,Index_Filed,sizeof(WORD)*INDEX_NUM);
	f_pIndexBuffer->Unlock();
}