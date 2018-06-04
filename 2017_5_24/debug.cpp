//==========================================
// �f�o�b�O
//==========================================
#include "main.h"
#include <d3dx9.h>
#include "input.h"
#include "debug.h"
#include <stdio.h>
#include "Renderer.h"

//#ifdef _DEBUG								// ������ł��悢�����̂ق�������
#if defined (_DEBUG) || defined(DEBUG)		// �f�o�b�O�̎��͗L���A�����[�X�̎��͖���
static LPD3DXFONT g_pFont = NULL;
#endif

typedef struct 
{
	D3DXVECTOR4 pos;
	D3DXCOLOR color;
}DEBUG_VERTEX;

#define DEBUG_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//=================================================================================================
//	�f�o�b�O�������֐�
//
//
//=================================================================================================
void InitDebugString(void)		// �����͑S���e�N�X�`���[		����̓f�o�b�O�̂ݎg��
{
	#if defined (_DEBUG) || defined(DEBUG)	//�f�o�b�O�̎��͗L���A�����[�X�̎��͖���

		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
		if(pDevice == NULL)
		{
			return;
		}

		D3DXCreateFont(pDevice,
			18, 0, 0, 0, FALSE,		// �����̍����A���A�����A�݂��Ճ}�b�v���x���̐�
			SHIFTJIS_CHARSET,		// 
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			"Terminal",
			&g_pFont);				// �����[�X�K�{

	#endif

}

//=================================================================================================
//	�f�o�b�O�I���֐�
//
//
//=================================================================================================
void UninitDebugString(void)
{
	#if defined (_DEBUG) || defined(DEBUG)	//�f�o�b�O�̎��͗L���A�����[�X�̎��͖���

		if(g_pFont )					// ��������Ȃ��Ƒ��̐l�Ɉ��e���@�}�i�[�@�������͕K���Ԃ�
		{
			// �f�o�C�X�̊J��
			g_pFont -> Release();
			g_pFont= NULL ;
		}

	#endif
}

//=================================================================================================
//	�f�o�b�O�֐�
//
//begin,end�V�[���̒��ŋL��
//=================================================================================================
void DebugString(int x, int y, const char* pFormat, ...)
{
	#if defined (_DEBUG) || defined(DEBUG)	//�f�o�b�O�̎��͗L���A�����[�X�̎��͖���

		va_list argp;
		char strBuf[256];							// 256�����܂�
		va_start(argp, pFormat);
		vsprintf_s(strBuf, 256, pFormat, argp);		// 256�͏�̗p�ӂ����z��̐��Ɠ���
		va_end(argp);

		RECT rect = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};	// �x�N�^�[�t�H���g�����ꂢ�������������o�J�H��
		g_pFont->DrawText(NULL,								// �X�v���C�g�N���X
						 strBuf,							// ������
						 -1,								// ������̕\�����鐔	-1�͑S��
						 &rect,								// �͈�
						 DT_LEFT,							// �t���O
						 D3DCOLOR_RGBA(0, 255, 64, 255));				// �t�H���g�̐F
	
	#endif
}
//=================================================================================================
//	�f�o�b�O�|���S���֐�
//
//begin,end�V�[���̒��ŋL��		// settexture���O���Ɖf��@�e�N�X�`���[���g��Ȃ�
//=================================================================================================
void DebugPolygon(int n, float x, float y, float r)
{
	#if defined (_DEBUG) || defined(DEBUG)	//�f�o�b�O�̎��͗L���A�����[�X�̎��͖���

	const float R_C = D3DX_PI * 2.0f / n ;
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();	// �f�o�C�X�Q�b�g
	n = n+1;									// �~������������߂�

	if(r < 1.0f)								// ���a���P�̎��I��
	{
		return;
	}

	if( pDevice == NULL )						// �f�o�C�X����NULL�Ȃ�I��
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
