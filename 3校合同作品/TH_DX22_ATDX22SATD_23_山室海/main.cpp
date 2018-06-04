//**********************************************************************
//
//						�wDirectX�A3D�`��x
//		�N���X�L���FAT-12D-246		�o�Ȕԍ��F25		
//		�w�Дԍ��F65089				�����F�R���@�C
//
//**********************************************************************

//*************************************************************************************************************************
// �C���N���[�h
//*************************************************************************************************************************
#include<math.h>
#include "main.h"
#include "Polygon.h"
#include "Polygon3DTset.h"
#include "Camera.h"
#include "grid.h"
#include "Input.h"
#include "light.h"
#include "model.h"
#include "MeshFiled.h"
#include "BillBoard.h"
#include "shadow.h"
#include "Explosion.h"
#include "Scene.h"
#include "Effect.h"
#include "Enemy.h"
#include "Sound.h"

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3D9	g_pD3D = NULL;	// Direct3D�C���^�[�t�F�[�X
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// Direct3D�f�o�C�X


#ifdef _DEBUG
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;
#endif


//=========================================================================================================================
// WinMain�֐�
//=========================================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	long lWindowWidth = 0;
	long lWindowHeight = 0;
	long lDesktopWidth = 0;
	long lDesktopHeight = 0;
	int nWindowX = 0;
	int nWindowY = 0;
	MSG msg;
	DWORD dStyle = (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) ^ WS_MAXIMIZEBOX;

	// �\���̂̏�����
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),			// ���̍\���̂̃T�C�Y
		CS_VREDRAW | CS_HREDRAW,	// �X�^�C��
		WndProc,					// �֐��|�C���^�i���b�Z�[�W���[�v�̂Ƃ��ɌĂ΂��֐��j
		0,							// �g�p���Ȃ��̂�0
		0,							// �g�p���Ȃ��̂�0
		hInstance,					// ������
		NULL,						// �A�C�R���n���h��
		LoadCursor(NULL,IDC_ARROW),	// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),	// �N���C�A���g�̈�̐F
		NULL,						// ���j���[�n���h��
		CLASS_NAME,					// �E�B���h�E�N���X��
		NULL						// �~�j�A�C�R���n���h��
	};
	/* �\���̂ɑ��
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	�`
	*/

	// RECT�\���̂̐���
	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT dr;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̃T�C�Y�����߂�
	AdjustWindowRect(&wr, dStyle, false);

	// �N���C�A���g�̈�̃T�C�Y��ϐ��ɑ��
	lWindowWidth = wr.right - wr.left;
	lWindowHeight = wr.bottom - wr.top;

	// �f�X�N�g�b�v�̃T�C�Y�����߂�
	GetWindowRect(GetDesktopWindow(), &dr);

	// �f�X�N�g�b�v�̃T�C�Y��ϐ��ɑ��
	lDesktopWidth = dr.right;
	lDesktopHeight = dr.bottom;

	nWindowX = lDesktopWidth < lWindowWidth ? 0 : ((int)lDesktopWidth - (int)lWindowWidth) / 2;				// ? ��������
	nWindowY = lDesktopHeight < lWindowHeight ? 0 : ((int)lDesktopHeight - (int)lWindowHeight) / 2;			// : �����łȂ����

	// �E�B���h�E�쐬
	HWND hWnd = CreateWindowEx(
		0,							// �g���E�B���h�E�X�^�C��
		CLASS_NAME,
		WINDOW_NAME,
		dStyle,						// �E�B���h�E�X�^�C��
		nWindowX,					// �E�B���h�E�̍���x���W
		nWindowY,					// �E�B���h�E�̍���y���W
		lWindowWidth,				// ��
		lWindowHeight,				// ����
		NULL,						// �e�E�B���h�E�ւ̃n���h��
		NULL,						// ���j���[�n���h��
		hInstance,
		NULL);

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nShowCmd);		// �E�B���h�E�A���
	
	// �E�B���h�E�̍X�V
	UpdateWindow(hWnd);

	DWORD dwExecLastTime = 0;		// �O�t���[���̃Q�[���������I���������
	DWORD dwCurrentTime = 0;		// ���݂̎���

	// ����\��ݒ�
	timeBeginPeriod(1);

	if (!Init(hInstance, hWnd, TRUE))
	{
		MessageBox(hWnd, "�������ł��Ȃ�����", "�G���[���b�Z�[�W", MB_OK);
		exit(0);
	}

	// ���b�Z�[�W���[�v
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))		// �^��������
		{// �E�B���h�E���b�Z�[�W����
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��v��
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)	// 60fps�i1/60�b�o���Ă�����j
			{// �Q�[������
				Update();
				Draw();
				dwExecLastTime = dwCurrentTime;
			}
		}
	} while (msg.message != WM_QUIT);

	Uninit();
	// ����\��߂�
	timeEndPeriod(1);
	// ���^�[��
	return (int)msg.wParam;

}

//=========================================================================================================================
// �E�B���h�E�v���V�[�W��
//=========================================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	// switch�P�[�X
	switch (uMsg)
	{
	
	case WM_DESTROY:				// �����ŃE�B���h�E��{���ɏI��点�邩�𔻒f�B���̌�Ƀ��b�Z�[�W�{�b�N�X���o���΂悢�B
		PostQuitMessage(0);			// WM_QUIT���b�Z�[�W�̑��M
		break;

	case WM_CLOSE:					// ����{�^���������ꂽ
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_KEYDOWN:				// �L�[�������ꂽ
		switch (wParam)
		{// switch�P�[�X
		case VK_ESCAPE:				// �yESC�z�L�[���������i�K���I���͂���j
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}//	switch�I��
		break;

	case WM_LBUTTONDOWN:
	{// �}�E�X�����N���b�N����
		SetFocus(hWnd);
		break;
	}

	default:
		break;

	}// switch�I��

	// ���^�[��
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		// ��{�I�Ȃ��Ƃ�����Ă����

}

//=========================================================================================================================
// ����������
//=========================================================================================================================
bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	
	D3DDISPLAYMODE d3ddm;
	// Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth				 = SCREEN_WIDTH;
	d3dpp.BackBufferHeight				 = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat				 = d3ddm.Format;
	d3dpp.BackBufferCount				 = 1;
	d3dpp.SwapEffect					 = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil		 = TRUE;
	d3dpp.AutoDepthStencilFormat		 = D3DFMT_D16;
	d3dpp.Windowed						 = bWindow;
	d3dpp.FullScreen_RefreshRateInHz	 = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval			 = D3DPRESENT_INTERVAL_DEFAULT;

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// {�f�o�C�X�쐬����}<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,														// �f�o�C�X�^�C�v
		hWnd,																// �t�H�[�J�X����E�B���h�E�̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,								// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,																// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))													// ���f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^��
	{
		MessageBox(hWnd, "Direct3D�f�o�C�X����邱�Ƃ��o���܂���ł���", "�G���[���b�Z�[�W", MB_OK);
		return false;
	}
	
	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�i�`��̐ݒ��؂�ւ���j
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		// �������F�X�C�b�`

	// ���u�����h���s��
	// SRC... ������`�����́A�܂�|���S���Ƀe�N�X�`����\�������́B
	// DEST...���łɕ`�悳��Ă����ʂ̂��ƁB
	// SRC_RGB * SRC_�� + DEST_RGB * (1 - SRC_��)
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �e�N�X�`���X�e�[�W�X�e�[�g
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// ��Z�̍���
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		// ��Z�̉E��

	// �Z�b�g�T���v���[�X�e�[�g
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`���A�h���X�O���Q�Ƃ����Ƃ���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �ǂ�������悢���i�t�A�u�jWRAP�F����

	// �e�N�X�`���t�B���^�����O
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// ���ۂ̃T�C�Y��菬�����Ȃ����Ƃ��ɂ�����t�B���^�����O�A���`�ۊ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// ���ۂ̃T�C�Y���傫���Ȃ����Ƃ��Ƀt�B���^�����O
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);		// MIPMAP�Ԃ�ۊ�(NONE�ɂ���Ǝg��Ȃ��Ȃ�)
	

	HRESULT hr;
	// �|���S��������	
	InitKeyboard(hInstance,hWnd);
	PolygonInit(hWnd);
	Polygon3DTestInit(hWnd);
	hr=InitSound(hWnd);
	InitScene();
	CameraInit();
	GridInit();
	InitLight();
	InitBillBoard();
	InitExplosion();
	InitEnemy();
	MeshfFiledFileInit(500,200,1);
	InitShadow();
	InitEffect();


	return true;
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void Uninit(void)
{


	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	UninitKeyboard();
	UninitScene();
	CameraUninit();
	PolygonUninit();
	Polygon3DTestUninit();
	UninitModel();
	MeshfFiledUninit();
//	UninitBillBoard();
	UninitShadow();
	UninitExplosion();
	UninitEffect();
	UninitEnemy();

}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void Update(void)
{
	UpdateKeyboard();
	UpdateScene();

}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void Draw(void)
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 150, 255, 255), 1.0f, 0);	// 1�t���[����1��
	
	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))		// 1�t���[����1��
	{


		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));

		DrawScene();	

		
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();					// 1�t���[����1��
	}


	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);	// 1�t���[����1��
}

LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}
