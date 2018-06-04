

#include <stdio.h>
#include <d3dx9.h>

#ifndef _POLYGON_H_
#define _POLYGON_H_

typedef struct{				//�e�N�X�`���[���\���́@�t�@�C���l�[���A���A����
	char fileName[256];
	int width;
	int height;
}TEXTURE_POLYGON;

// �e�N�X�`���[�f�[�^
static const TEXTURE_POLYGON g_aTexture[] ={
	{"texture\\number.jpg"	,269, 185},
	{"texture\\COLOR.png",411,106},
	{"texture\\SHOOTING.png",645,106},
	{"texture\\Press-Enter-key2.png",236,26},
	{"texture\\black.jpg",467,140},
	{"texture\\RESULT.png",284,76}
};

// �e�N�X�`����


//============================================
// �v���g�^�C�v�錾
//============================================

bool PolygonInit(/*void*/ HWND hWnd);		//
void PolygonUninit(void);					//
void PolygonUpdate(void);					//


void SetPolygonRotation(float cx, float cy, float angle);		// ��]
void SetPolygonColor(D3DCOLOR color);							// �J���[
void SetPolygonScale(float cx, float cy,float sx, float sy);	// �X�P�[��		1.0,1.0�œ��{
void SetPolygonTexture(int TexNum);					// �摜�̔ԍ��A
void PolygonDraw( float dx, float dy, int tcx, int tcy, int tcw, int tch, bool bAffine = false);		
				//����̂��A����̂��A�e�N�X�`���[�؂��菉�߂��A���A���A�����A��]�̗L��

#endif			//_POLYGON_H_