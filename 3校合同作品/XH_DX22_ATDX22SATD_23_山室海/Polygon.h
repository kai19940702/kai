

#include <stdio.h>
#include <d3dx9.h>

#ifndef _POLYGON_H_
#define _POLYGON_H_

typedef struct{				//テクスチャー情報構造体　ファイルネーム、幅、高さ
	char fileName[256];
	int width;
	int height;
}TEXTURE_POLYGON;

// テクスチャーデータ
static const TEXTURE_POLYGON g_aTexture[] ={
	{"texture\\number.jpg"	,269, 185},
	{"texture\\COLOR.png",411,106},
	{"texture\\SHOOTING.png",645,106},
	{"texture\\Press-Enter-key2.png",236,26},
	{"texture\\black.jpg",467,140},
	{"texture\\RESULT.png",284,76}
};

// テクスチャ列挙


//============================================
// プロトタイプ宣言
//============================================

bool PolygonInit(/*void*/ HWND hWnd);		//
void PolygonUninit(void);					//
void PolygonUpdate(void);					//


void SetPolygonRotation(float cx, float cy, float angle);		// 回転
void SetPolygonColor(D3DCOLOR color);							// カラー
void SetPolygonScale(float cx, float cy,float sx, float sy);	// スケール		1.0,1.0で等倍
void SetPolygonTexture(int TexNum);					// 画像の番号、
void PolygonDraw( float dx, float dy, int tcx, int tcy, int tcw, int tch, bool bAffine = false);		
				//左上のｘ、左上のｙ、テクスチャー切り取り初めｘ、ｙ、幅、高さ、回転の有無

#endif			//_POLYGON_H_