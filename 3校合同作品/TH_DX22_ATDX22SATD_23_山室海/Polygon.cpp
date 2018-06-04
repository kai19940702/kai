//==========================================
// ポリゴン描画
//==========================================

#include <d3d9.h>
#include <d3dx9.h>
#include "Polygon.h"
#include "main.h"

//==========================================================================================
// グローバル変数
//==========================================================================================

static LPDIRECT3DDEVICE9 g_pDevice ;
static LPDIRECT3DTEXTURE9 g_pTextures[12];				// テクスチャー
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;			// これも使ったらリリース

#define ARRAYCOUNT(x)	sizeof(x)/sizeof(x[0])
static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_aTexture);	// 定数　const

static D3DCOLOR g_Color;
static int   g_nPolygonTextureNum;
static float g_fScaleX = 1.0f;
static float g_fScaleY = 1.0f;
static float g_fScaleOffsetX = 0.0f;
static float g_fScaleOffsetY = 0.0f;
static float g_fAngle = 0.0f;
static float g_fRotationOffsetX = 0.0f;
static float g_fRotationOffsetY = 0.0f;


static void CreateVertex( float dx, float dy, int tcx, int tcy, int tcw, int tch );			// ローカルなのでヘッダーには書かない
static void CreateVertexAffine( float dx, float dy, int tcx, int tcy, int tcw, int tch );			// ローカルなのでヘッダーには書かない

//static float g_uv;												// uvスクロール技法
//static int x = 0;
//static int y = 0;
//static bool frag = true;

//==========================================================================================
// 構造体
//==========================================================================================
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1)		// 頂点の種類　　　TEX0は映らない

//=================================================================================================
//	ポリゴン描画初期化処理関数
//
//
//=================================================================================================
bool PolygonInit( HWND hWnd )
{
	// デバイスの取得
	g_pDevice = GetD3DDevice();
	// デバイスの取得ができなかったら
	if( g_pDevice == NULL )
	{
		return false;
	}
	
	//----------------------------------------
	// テクスチャーファイルの読み込み
	//----------------------------------------
	HRESULT hr;

	for(int i = 0; i < 12; i++)
	{
		hr = D3DXCreateTextureFromFile(
			g_pDevice ,
			g_aTexture[i].fileName,			// ファイル名
			&g_pTextures[i]);				// アドレスのアドレス

		if( FAILED (hr) )
		{
			// テクスチャーの読み込みの失敗時のメッセージ
			MessageBox (hWnd/*NULL*/, "テクスチャーが読み込めなかった", "エラー",MB_OK); // 第一引数をNULLか引数を与える
			return false;
		}
	}

	//----------------------------------------
	// バッファー
	//----------------------------------------
	hr = g_pDevice->CreateVertexBuffer(		// 動的にメモリの確保
		sizeof(VERTEX_2D) * 4,				// 頂点のサイズ×４			借りたい量		ここをいじる
		D3DUSAGE_WRITEONLY,					// 頂点バッファーへの書き込み専用
		FVF_VERTEX_2D,						// (設定しなくても実は大丈夫)
		D3DPOOL_MANAGED,					// どうやって管理するか
		&g_pVertexBuffer,					// ノートのある場所
		NULL								// 謎のもの
		);

	if( FAILED(hr) )
	{
		MessageBox( NULL , "バッファーの作成に失敗しました", "エラー", MB_OK);
	}

}

//=================================================================================================
//	ポリゴン描画終了処理関数
//
//
//=================================================================================================
void PolygonUninit(void)
{

	if( g_pVertexBuffer )
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	for(int i = 0 ; i < 12 ; i++){

		if (g_pTextures[i] != NULL)					// これをやらないと他の人に悪影響　マナー　メモリは必ず返す
		{
			// デバイスの開放
			g_pTextures[i] -> Release();
			g_pTextures[i] = NULL ;
		}

	}
}

//=================================================================================================
//	ポリゴン描画更新処理関数
//
//
//=================================================================================================
void PolygonUpdate(void)
{
	

}
	//g_fScale += g_fScaleAdd;					// 実行中にテクスチャーのサイズを変える
	//if( g_fScale >= 3.0f )
	//{
	//	g_fScale = 3.0f;
	//	g_fScaleAdd = -g_fScaleAdd;
	//}
	//else if( g_fScale < 0.125f )
	//{
	//	g_fScale = 0.125f;
	//	g_fScaleAdd = -g_fScaleAdd;
	//}

	/*if(x == 100)
				{
					frag = false;
				}
				if(x == 0)
				{
					frag =true ;
				}
				if(frag == true)
				{
					x++;
					y++;
				}
				if(frag == false)
				{
					x--;
					y--;
				}*/

	// uvスクロール技法
	//g_uv += 0.01f;


//=================================================================================================
//	ポリゴン描画描画処理関数
//
//
//=================================================================================================
void PolygonDraw(float dx , float dy , int tcx, int tcy, int tcw, int tch, bool bAffine)	// デフォルト引数はプロトタイプ宣言のみ
{
	// デバイスの有無
	if( g_pDevice == NULL ) 
	{
		return;
	}

	// アフィン変数の使用の有無（回転、拡大など）
	if(bAffine)
	{
		CreateVertexAffine(dx,dy,tcx,tcy,tcw,tch);
	}
	else
	{
		CreateVertex(dx,dy,tcx,tcy,tcw,tch);
	}

	// FVF（今から使用する頂点情報）の設定
	g_pDevice->SetFVF(FVF_VERTEX_2D);	//   頂点 ｜ 色  構造体を用意すると便利

	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_2D));	// ナンバー、どのバッファー、どこから、１ストライド

	g_pDevice->SetTexture(0, g_pTextures[g_nPolygonTextureNum]);

	g_pDevice->DrawPrimitive(			// 何度でも
		D3DPT_TRIANGLESTRIP,			// プリミティブタイプ
		0,								// どこから
		2								// プリミティブの数
		);				//

	//g_pDevice->DrawPrimitiveUP(		// 何度でも
	//	D3DPT_TRIANGLESTRIP,			// プリミティブタイプ
	//	2,								// プリミティブの数
	//	&vtx4[0],						//
	//	sizeof(VERTEX_2D));				//

}

//=================================================================================================
// カラー関数
//=================================================================================================
void SetPolygonColor(D3DCOLOR color)		// テクスチャーカラーの設定
{
	g_Color = color;
}

//=================================================================================================
// 拡大縮小関数
//
//	＝＝引数＝＝
//	(x軸方向にどのくらい伸ばすか、y軸方向にどれくらい伸ばすか、)
//=================================================================================================
void SetPolygonScale(float cx, float cy,float sx, float sy)
{
	g_fScaleX = cx;
	g_fScaleY = cy;
	g_fScaleOffsetX = sx;
	g_fScaleOffsetY = sy;
}
//=================================================================================================
// 回転関数
//
//	＝＝引数＝＝
//	(x軸方向にどれくらいずらすか、y軸方向にどれくらいずらすか、どのくらいのスピードで回転させるか)
//=================================================================================================

void SetPolygonRotation(float cx, float cy, float angle)
{
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
	g_fAngle = angle;
}

//=================================================================================================
// テクスチャーナンバー関数
//=================================================================================================
void SetPolygonTexture(int TexNum)	// テクスチャーナンバー
{
	g_nPolygonTextureNum = TexNum;
}

//=================================================================================================
// 頂点作成関数
//=================================================================================================
void CreateVertex( float dx, float dy, int tcx, int tcy, int tcw, int tch )	// バッファーのロック　擬似のアドレス
{
	VERTEX_2D* pV;			// 擬似アドレスの格納先

	g_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);		// ロックの選択範囲　0なら全選択	pVにアドレス入らなかったら最後の引数に０

	pV[0].pos = D3DXVECTOR4(-0.5f + dx      , -0.5f + dy      , 1.0f , 1.0f);
	pV[1].pos = D3DXVECTOR4(-0.5f + dx + tcw, -0.5f + dy      , 1.0f , 1.0f);
	pV[2].pos = D3DXVECTOR4(-0.5f + dx      , -0.5f + dy + tch, 1.0f , 1.0f);
	pV[3].pos = D3DXVECTOR4(-0.5f + dx + tcw, -0.5f + dy + tch, 1.0f , 1.0f);

	pV[0].color = 
	pV[1].color = 
	pV[2].color = 
	pV[3].color = g_Color;

	int tw = g_aTexture[g_nPolygonTextureNum].width;
	int th = g_aTexture[g_nPolygonTextureNum].height;

	float u0 = (float)tcx / tw ;			// 左上
	float v0 = (float)tcy / th ;			// 右下
	float u1 = (float)(tcx + tcw) / tw;		// 
	float v1 = (float)(tcy + tch) / th;		// 

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}

//=================================================================================================
// 頂点作成（アフィン変数）関数
//=================================================================================================
void CreateVertexAffine( float dx, float dy, int tcx, int tcy, int tcw, int tch )	// バッファーのロック　擬似のアドレス
{
	VERTEX_2D* pV;			// 擬似アドレスの格納先

	g_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);		// ロックの選択範囲　0なら全選択	pVにアドレス入らなかったら最後の引数に０

	float x   = ( 0.0f - g_fScaleOffsetX ) * g_fScaleX + g_fScaleOffsetX ;		// 拡大縮小はRotationOffsetの前に
	float x_w = ( tcw  - g_fScaleOffsetX ) * g_fScaleX + g_fScaleOffsetX ;		// 中心座標にセットしてから元に戻す
	float y   = ( 0.0f - g_fScaleOffsetY ) * g_fScaleY + g_fScaleOffsetY ;
	float y_h = ( tch  - g_fScaleOffsetY ) * g_fScaleY + g_fScaleOffsetY ;

	float fRotationOffsetX = ( g_fRotationOffsetX - g_fScaleOffsetX ) * g_fScaleX ;
	float fRotationOffsetY = ( g_fRotationOffsetY - g_fScaleOffsetY ) * g_fScaleY ;// 回転の中心座標

	x    -= fRotationOffsetX ;
	x_w  -= fRotationOffsetX ;
	y    -= fRotationOffsetY ;
	y_h  -= fRotationOffsetY ;
	dx += fRotationOffsetX - 0.5f;
	dy += fRotationOffsetY - 0.5f;

	pV[0].pos = D3DXVECTOR4( x   * cosf(g_fAngle) - y   * sinf(g_fAngle) + dx,
							 x   * sinf(g_fAngle) + y   * cosf(g_fAngle) + dy, 0.0f , 1.0f);
	pV[1].pos = D3DXVECTOR4( x_w * cosf(g_fAngle) - y   * sinf(g_fAngle) + dx, 
							 x_w * sinf(g_fAngle) + y   * cosf(g_fAngle) + dy, 0.0f , 1.0f);
	pV[2].pos = D3DXVECTOR4( x   * cosf(g_fAngle) - y_h * sinf(g_fAngle) + dx, 
							 x   * sinf(g_fAngle) + y_h * cosf(g_fAngle) + dy, 0.0f , 1.0f);
	pV[3].pos = D3DXVECTOR4( x_w * cosf(g_fAngle) - y_h * sinf(g_fAngle) + dx, 
							 x_w * sinf(g_fAngle) + y_h * cosf(g_fAngle) + dy, 0.0f , 1.0f);

	pV[0].color = 
	pV[1].color = 
	pV[2].color = 
	pV[3].color = g_Color;

	int tw = g_aTexture[g_nPolygonTextureNum].width;
	int th = g_aTexture[g_nPolygonTextureNum].height;

	float u0 = (float)tcx / tw ;			// 左上
	float v0 = (float)tcy / th ;			// 右下
	float u1 = (float)(tcx + tcw) / tw;		// 
	float v1 = (float)(tcy + tch) / th;		// 

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}
