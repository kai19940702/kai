//==========================================
// デバッグ
//==========================================
#include "main.h"
#include <d3dx9.h>
#include "input.h"
#include "debug.h"
#include <stdio.h>
#include "Renderer.h"

//#ifdef _DEBUG								// こちらでもよいが下のほうが正式
#if defined (_DEBUG) || defined(DEBUG)		// デバッグの時は有効、リリースの時は無効
static LPD3DXFONT g_pFont = NULL;
#endif

typedef struct 
{
	D3DXVECTOR4 pos;
	D3DXCOLOR color;
}DEBUG_VERTEX;

#define DEBUG_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//=================================================================================================
//	デバッグ初期化関数
//
//
//=================================================================================================
void InitDebugString(void)		// 文字は全部テクスチャー		これはデバッグのみ使う
{
	#if defined (_DEBUG) || defined(DEBUG)	//デバッグの時は有効、リリースの時は無効

		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
		if(pDevice == NULL)
		{
			return;
		}

		D3DXCreateFont(pDevice,
			18, 0, 0, 0, FALSE,		// 文字の高さ、幅、太さ、みっぷマップレベルの数
			SHIFTJIS_CHARSET,		// 
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			"Terminal",
			&g_pFont);				// リリース必須

	#endif

}

//=================================================================================================
//	デバッグ終了関数
//
//
//=================================================================================================
void UninitDebugString(void)
{
	#if defined (_DEBUG) || defined(DEBUG)	//デバッグの時は有効、リリースの時は無効

		if(g_pFont )					// これをやらないと他の人に悪影響　マナー　メモリは必ず返す
		{
			// デバイスの開放
			g_pFont -> Release();
			g_pFont= NULL ;
		}

	#endif
}

//=================================================================================================
//	デバッグ関数
//
//begin,endシーンの中で記入
//=================================================================================================
void DebugString(int x, int y, const char* pFormat, ...)
{
	#if defined (_DEBUG) || defined(DEBUG)	//デバッグの時は有効、リリースの時は無効

		va_list argp;
		char strBuf[256];							// 256文字まで
		va_start(argp, pFormat);
		vsprintf_s(strBuf, 256, pFormat, argp);		// 256は上の用意した配列の数と同じ
		va_end(argp);

		RECT rect = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};	// ベクターフォントがきれいだがメモリをバカ食い
		g_pFont->DrawText(NULL,								// スプライトクラス
						 strBuf,							// 文字列
						 -1,								// 文字列の表示する数	-1は全部
						 &rect,								// 範囲
						 DT_LEFT,							// フラグ
						 D3DCOLOR_RGBA(0, 255, 64, 255));				// フォントの色
	
	#endif
}
//=================================================================================================
//	デバッグポリゴン関数
//
//begin,endシーンの中で記入		// settextureを外すと映る　テクスチャーを使わない
//=================================================================================================
void DebugPolygon(int n, float x, float y, float r)
{
	#if defined (_DEBUG) || defined(DEBUG)	//デバッグの時は有効、リリースの時は無効

	const float R_C = D3DX_PI * 2.0f / n ;
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();	// デバイスゲット
	n = n+1;									// 円を一周書くために

	if(r < 1.0f)								// 半径が１の時終了
	{
		return;
	}

	if( pDevice == NULL )						// デバイス内がNULLなら終了
	{
		return;
	}

	DEBUG_VERTEX* pV;
	pV = (DEBUG_VERTEX*) malloc (sizeof(DEBUG_VERTEX) * n );

	for(int i = 0; i < n ; i++)
	{
		pV[i].pos.x = cosf(R_C * i) * r + x;
		pV[i].pos.y = sinf(R_C * i) * r + y;
		pV[i].pos.z = 0.0f;
		pV[i].pos.w = 1.0f;
		pV[i].color = D3DCOLOR_RGBA(32, 255, 64, 255);
	}

	pDevice->SetTexture(0,NULL);
	pDevice->SetFVF(DEBUG_FVF);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, n, pV, sizeof(DEBUG_VERTEX));

	free(pV);
	
	#endif
}
