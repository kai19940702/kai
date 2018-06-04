#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")


#include<tchar.h>


#include "Renderer.h"

LPDIRECT3D9		Renderer::m_D3D = NULL;

LPDIRECT3DDEVICE9	Renderer::m_D3DDevice = NULL;




void Renderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);


	// デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS d3dpp;

	m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	ZeroMemory(&d3dpp, sizeof(d3dpp)); //ゼロで初期化
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
	

	// デバイスの生成
	// [デバイス作成制御]<描画>と<頂点処理>を
	m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,
						hWnd,
						D3DCREATE_HARDWARE_VERTEXPROCESSING,
						&d3dpp,
						&m_D3DDevice); // important!!
	
		// messagebox

		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェア
		//if (FAILED(g_pD3D->CreateDevice()))
		//{
		//}


	// alpha setting
	// レンダーステートパラメータの設定
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// αブレンドを行う
	// SRC…今から描くもの。つまりポリゴンにテクスチャを貼ったもの
	// DESR…すでに描画されている画面のこと。
	// SRC_RGB * SRC_α + DEST_RGB * (1-SRC_α)
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// α
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// α


	m_D3DDevice->SetTextureStageState(
					0,// ゼロ
					D3DTSS_ALPHAOP,//演算子
					D3DTOP_MODULATE);

	m_D3DDevice->SetTextureStageState(
		0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	m_D3DDevice->SetTextureStageState(
		0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// UV座標
	// テクスチャアドレス外を参照した時どうするが設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}
void Renderer::Uninit()
{
	if (m_D3DDevice != NULL)
	{ // デバイスの開放
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}

	if (m_D3D != NULL)
	{ // Direct3Dオブジェクトの開放
		m_D3D->Release();
		m_D3D = NULL;
	}
}
void Renderer::DrawBegin()
{
	m_D3DDevice->Clear( // 画面のクリア、一回しか読んでない
		0, NULL,
		(D3DCLEAR_TARGET | // クリアのこと
			D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 158, 180, 155), // 何色でクリアする
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