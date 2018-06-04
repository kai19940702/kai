//==========================================
// �|���S���`��
//==========================================

#include <d3d9.h>
#include <d3dx9.h>
#include "Polygon.h"
#include "main.h"

//==========================================================================================
// �O���[�o���ϐ�
//==========================================================================================

static LPDIRECT3DDEVICE9 g_pDevice ;
static LPDIRECT3DTEXTURE9 g_pTextures[12];				// �e�N�X�`���[
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;			// ������g�����烊���[�X

#define ARRAYCOUNT(x)	sizeof(x)/sizeof(x[0])
static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_aTexture);	// �萔�@const

static D3DCOLOR g_Color;
static int   g_nPolygonTextureNum;
static float g_fScaleX = 1.0f;
static float g_fScaleY = 1.0f;
static float g_fScaleOffsetX = 0.0f;
static float g_fScaleOffsetY = 0.0f;
static float g_fAngle = 0.0f;
static float g_fRotationOffsetX = 0.0f;
static float g_fRotationOffsetY = 0.0f;


static void CreateVertex( float dx, float dy, int tcx, int tcy, int tcw, int tch );			// ���[�J���Ȃ̂Ńw�b�_�[�ɂ͏����Ȃ�
static void CreateVertexAffine( float dx, float dy, int tcx, int tcy, int tcw, int tch );			// ���[�J���Ȃ̂Ńw�b�_�[�ɂ͏����Ȃ�

//static float g_uv;												// uv�X�N���[���Z�@
//static int x = 0;
//static int y = 0;
//static bool frag = true;

//==========================================================================================
// �\����
//==========================================================================================
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1)		// ���_�̎�ށ@�@�@TEX0�͉f��Ȃ�

//=================================================================================================
//	�|���S���`�揉���������֐�
//
//
//=================================================================================================
bool PolygonInit( HWND hWnd )
{
	// �f�o�C�X�̎擾
	g_pDevice = GetD3DDevice();
	// �f�o�C�X�̎擾���ł��Ȃ�������
	if( g_pDevice == NULL )
	{
		return false;
	}
	
	//----------------------------------------
	// �e�N�X�`���[�t�@�C���̓ǂݍ���
	//----------------------------------------
	HRESULT hr;

	for(int i = 0; i < 12; i++)
	{
		hr = D3DXCreateTextureFromFile(
			g_pDevice ,
			g_aTexture[i].fileName,			// �t�@�C����
			&g_pTextures[i]);				// �A�h���X�̃A�h���X

		if( FAILED (hr) )
		{
			// �e�N�X�`���[�̓ǂݍ��݂̎��s���̃��b�Z�[�W
			MessageBox (hWnd/*NULL*/, "�e�N�X�`���[���ǂݍ��߂Ȃ�����", "�G���[",MB_OK); // ��������NULL��������^����
			return false;
		}
	}

	//----------------------------------------
	// �o�b�t�@�[
	//----------------------------------------
	hr = g_pDevice->CreateVertexBuffer(		// ���I�Ƀ������̊m��
		sizeof(VERTEX_2D) * 4,				// ���_�̃T�C�Y�~�S			�؂肽����		������������
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�[�ւ̏������ݐ�p
		FVF_VERTEX_2D,						// (�ݒ肵�Ȃ��Ă����͑��v)
		D3DPOOL_MANAGED,					// �ǂ�����ĊǗ����邩
		&g_pVertexBuffer,					// �m�[�g�̂���ꏊ
		NULL								// ��̂���
		);

	if( FAILED(hr) )
	{
		MessageBox( NULL , "�o�b�t�@�[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
	}

}

//=================================================================================================
//	�|���S���`��I�������֐�
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

		if (g_pTextures[i] != NULL)					// ��������Ȃ��Ƒ��̐l�Ɉ��e���@�}�i�[�@�������͕K���Ԃ�
		{
			// �f�o�C�X�̊J��
			g_pTextures[i] -> Release();
			g_pTextures[i] = NULL ;
		}

	}
}

//=================================================================================================
//	�|���S���`��X�V�����֐�
//
//
//=================================================================================================
void PolygonUpdate(void)
{
	

}
	//g_fScale += g_fScaleAdd;					// ���s���Ƀe�N�X�`���[�̃T�C�Y��ς���
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

	// uv�X�N���[���Z�@
	//g_uv += 0.01f;


//=================================================================================================
//	�|���S���`��`�揈���֐�
//
//
//=================================================================================================
void PolygonDraw(float dx , float dy , int tcx, int tcy, int tcw, int tch, bool bAffine)	// �f�t�H���g�����̓v���g�^�C�v�錾�̂�
{
	// �f�o�C�X�̗L��
	if( g_pDevice == NULL ) 
	{
		return;
	}

	// �A�t�B���ϐ��̎g�p�̗L���i��]�A�g��Ȃǁj
	if(bAffine)
	{
		CreateVertexAffine(dx,dy,tcx,tcy,tcw,tch);
	}
	else
	{
		CreateVertex(dx,dy,tcx,tcy,tcw,tch);
	}

	// FVF�i������g�p���钸�_���j�̐ݒ�
	g_pDevice->SetFVF(FVF_VERTEX_2D);	//   ���_ �b �F  �\���̂�p�ӂ���ƕ֗�

	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_2D));	// �i���o�[�A�ǂ̃o�b�t�@�[�A�ǂ�����A�P�X�g���C�h

	g_pDevice->SetTexture(0, g_pTextures[g_nPolygonTextureNum]);

	g_pDevice->DrawPrimitive(			// ���x�ł�
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�^�C�v
		0,								// �ǂ�����
		2								// �v���~�e�B�u�̐�
		);				//

	//g_pDevice->DrawPrimitiveUP(		// ���x�ł�
	//	D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�^�C�v
	//	2,								// �v���~�e�B�u�̐�
	//	&vtx4[0],						//
	//	sizeof(VERTEX_2D));				//

}

//=================================================================================================
// �J���[�֐�
//=================================================================================================
void SetPolygonColor(D3DCOLOR color)		// �e�N�X�`���[�J���[�̐ݒ�
{
	g_Color = color;
}

//=================================================================================================
// �g��k���֐�
//
//	������������
//	(x�������ɂǂ̂��炢�L�΂����Ay�������ɂǂꂭ�炢�L�΂����A)
//=================================================================================================
void SetPolygonScale(float cx, float cy,float sx, float sy)
{
	g_fScaleX = cx;
	g_fScaleY = cy;
	g_fScaleOffsetX = sx;
	g_fScaleOffsetY = sy;
}
//=================================================================================================
// ��]�֐�
//
//	������������
//	(x�������ɂǂꂭ�炢���炷���Ay�������ɂǂꂭ�炢���炷���A�ǂ̂��炢�̃X�s�[�h�ŉ�]�����邩)
//=================================================================================================

void SetPolygonRotation(float cx, float cy, float angle)
{
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
	g_fAngle = angle;
}

//=================================================================================================
// �e�N�X�`���[�i���o�[�֐�
//=================================================================================================
void SetPolygonTexture(int TexNum)	// �e�N�X�`���[�i���o�[
{
	g_nPolygonTextureNum = TexNum;
}

//=================================================================================================
// ���_�쐬�֐�
//=================================================================================================
void CreateVertex( float dx, float dy, int tcx, int tcy, int tcw, int tch )	// �o�b�t�@�[�̃��b�N�@�[���̃A�h���X
{
	VERTEX_2D* pV;			// �[���A�h���X�̊i�[��

	g_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);		// ���b�N�̑I��͈́@0�Ȃ�S�I��	pV�ɃA�h���X����Ȃ�������Ō�̈����ɂO

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

	float u0 = (float)tcx / tw ;			// ����
	float v0 = (float)tcy / th ;			// �E��
	float u1 = (float)(tcx + tcw) / tw;		// 
	float v1 = (float)(tcy + tch) / th;		// 

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}

//=================================================================================================
// ���_�쐬�i�A�t�B���ϐ��j�֐�
//=================================================================================================
void CreateVertexAffine( float dx, float dy, int tcx, int tcy, int tcw, int tch )	// �o�b�t�@�[�̃��b�N�@�[���̃A�h���X
{
	VERTEX_2D* pV;			// �[���A�h���X�̊i�[��

	g_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);		// ���b�N�̑I��͈́@0�Ȃ�S�I��	pV�ɃA�h���X����Ȃ�������Ō�̈����ɂO

	float x   = ( 0.0f - g_fScaleOffsetX ) * g_fScaleX + g_fScaleOffsetX ;		// �g��k����RotationOffset�̑O��
	float x_w = ( tcw  - g_fScaleOffsetX ) * g_fScaleX + g_fScaleOffsetX ;		// ���S���W�ɃZ�b�g���Ă��猳�ɖ߂�
	float y   = ( 0.0f - g_fScaleOffsetY ) * g_fScaleY + g_fScaleOffsetY ;
	float y_h = ( tch  - g_fScaleOffsetY ) * g_fScaleY + g_fScaleOffsetY ;

	float fRotationOffsetX = ( g_fRotationOffsetX - g_fScaleOffsetX ) * g_fScaleX ;
	float fRotationOffsetY = ( g_fRotationOffsetY - g_fScaleOffsetY ) * g_fScaleY ;// ��]�̒��S���W

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

	float u0 = (float)tcx / tw ;			// ����
	float v0 = (float)tcy / th ;			// �E��
	float u1 = (float)(tcx + tcw) / tw;		// 
	float v1 = (float)(tcy + tch) / th;		// 

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}
