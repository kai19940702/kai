//=======================================
//	Main関数
//=======================================
#include "title.h"
#include "Scene.h"
#include <d3dx9.h>
#include "main.h"
#include "Game.h"
#include "Polygon.h"
#include "Scene.h"
#include<math.h>
#include "Polygon3DTset.h"
#include "Camera.h"
#include "Input.h"
#include "Effect.h"
#include "model.h"
#include "Sound.h"


typedef struct
{// 頂点の構造体
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}VERTEX_3D_TITLE;

static int alpha=0;

static D3DXMATRIX g_mtxWorld;
static D3DXMATRIX k_mtxWorld;

static bool fade_flag=false;
static D3DXMATRIX g_mtxInvView;

static LPDIRECT3DVERTEXBUFFER9 ti_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 ti_pIndexBuffer = NULL;

static const TEXTURE_TITLE g_a_pTexture[]={
								{"texture\\COLOR.png",467,140},
								{"texture\\SHOOTING.png",467,140},
								{"texture\\Press-Enter-key2.png",467,140},
								{"texture\\black.jpg",467,140},
								};
static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(g_aTexture);

static LPDIRECT3DTEXTURE9 g_pTextures[ 4 ]; 

static VERTEX_3D_TITLE v[4]={ {D3DXVECTOR3(-0.5,0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (0.0f,0.0f)  },
								  {D3DXVECTOR3(1.3,0.5,0) ,D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0f,0.0f) },
								  {D3DXVECTOR3(-0.5,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
								  {D3DXVECTOR3(1.3,-0.5,0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2 (1.0,1.0f)}
								};


static WORD Index[6]={0,1,2,
					  1,3,2};

static int count=0;

//=================================================================================================
//	タイトル初期化処理関数
//
//
//=================================================================================================
void InitTitle(void)
{
	count=0;
}

//=================================================================================================
//	タイトル終了処理関数
//
//
//=================================================================================================
void UninitTitle(void)
{
	fade_flag=false;
	alpha=0;
}

//=================================================================================================
//	タイトル更新処理関数
//
//
//=================================================================================================
void UpdateTitle(void)
{
	

  	if(GetKeyboardTrigger(DIK_SPACE))
	{
		fade_flag=true;
		PlaySound(SOUND_LABEL_KETTEI);
	}

	if(fade_flag)
	{
		alpha+=2;
		count++;
	}

	if(alpha>=255)
	{
		alpha=255;
		ChangeScene(SCENE_GAME);
	}

	
	
}

//=================================================================================================
//	タイトル描画処理関数
//
//
//=================================================================================================
void DrawTitle(void)
{

	SetPolygonTexture(1);
	SetPolygonScale(1.0f,1.0f,1.0f,1.0f);
	PolygonDraw(50,100,0,0,411,106,true);

	SetPolygonTexture(2);
	SetPolygonScale(0.9f,0.9f,1.0f,1.0f);
	PolygonDraw(160,220,0,0,645,106,true);


	if(!fade_flag||count>10)
	{
		SetPolygonTexture(3);
		SetPolygonScale(1.5f,1.5f,1.0f,1.0f);
		PolygonDraw(230,450,0,0,236,26,true);
		count=0;
	}
	SetPolygonColor(D3DCOLOR_RGBA(255,255,255,alpha));
	SetPolygonTexture(4);
	SetPolygonScale(10.0f,40.0f,1.0f,1.0f);
	PolygonDraw(0,0,0,0,236,26,true);
	
	SetPolygonColor(D3DCOLOR_RGBA(255,255,255,255));

}

