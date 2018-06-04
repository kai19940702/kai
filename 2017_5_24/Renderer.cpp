#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")


#include<tchar.h>


#include "Renderer.h"

LPDIRECT3D9		Renderer::m_D3D = NULL;

LPDIRECT3DDEVICE9	Renderer::m_D3DDevice = NULL;




void Renderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);


	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;

	m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	ZeroMemory(&d3dpp, sizeof(d3dpp)); //�[���ŏ�����
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat			 = d3ddm.Format;
	d3dpp.BackBufferCount			 = 1;
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil	 = TRUE;
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;
	d3dpp.Windowed					 = TRUE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;
	

	// �f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>��
	m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,
						hWnd,
						D3DCREATE_HARDWARE_VERTEXPROCESSING,
						&d3dpp,
						&m_D3DDevice); // important!!
	
		// messagebox

		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A
		//if (FAILED(g_pD3D->CreateDevice()))
		//{
		//}


	// alpha setting
	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// ���u�����h���s��
	// SRC�c������`�����́B�܂�|���S���Ƀe�N�X�`����\��������
	// DESR�c���łɕ`�悳��Ă����ʂ̂��ƁB
	// SRC_RGB * SRC_�� + DEST_RGB * (1-SRC_��)
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ��
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// ��


	m_D3DDevice->SetTextureStageState(
					0,// �[��
					D3DTSS_ALPHAOP,//���Z�q
					D3DTOP_MODULATE);

	m_D3DDevice->SetTextureStageState(
		0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	m_D3DDevice->SetTextureStageState(
		0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// UV���W
	// �e�N�X�`���A�h���X�O���Q�Ƃ������ǂ����邪�ݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}
void Renderer::Uninit()
{
	if (m_D3DDevice != NULL)
	{ // �f�o�C�X�̊J��
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}

	if (m_D3D != NULL)
	{ // Direct3D�I�u�W�F�N�g�̊J��
		m_D3D->Release();
		m_D3D = NULL;
	}
}
void Renderer::DrawBegin()
{
	m_D3DDevice->Clear( // ��ʂ̃N���A�A��񂵂��ǂ�łȂ�
		0, NULL,
		(D3DCLEAR_TARGET | // �N���A�̂���
			D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 158, 180, 155), // ���F�ŃN���A����
		1.0f, 0);
	m_D3DDevice->BeginScene();
}
void Renderer::DrawEnd()
{
	m_D3DDevice->EndScene();
	m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}
LPDIRECT3DDEVICE9 Renderer::GetDevice()
{
	return m_D3DDevice;
}