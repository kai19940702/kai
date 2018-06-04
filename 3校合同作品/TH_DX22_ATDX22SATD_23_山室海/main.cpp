//**********************************************************************
//
//						『DirectX、3D描画』
//		クラス記号：AT-12D-246		出席番号：25		
//		学籍番号：65089				氏名：山室　海
//
//**********************************************************************

//*************************************************************************************************************************
// インクルード
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
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3D9	g_pD3D = NULL;	// Direct3Dインターフェース
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// Direct3Dデバイス


#ifdef _DEBUG
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;
#endif


//=========================================================================================================================
// WinMain関数
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

	// 構造体の初期化
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),			// この構造体のサイズ
		CS_VREDRAW | CS_HREDRAW,	// スタイル
		WndProc,					// 関数ポインタ（メッセージループのときに呼ばれる関数）
		0,							// 使用しないので0
		0,							// 使用しないので0
		hInstance,					// メモリ
		NULL,						// アイコンハンドル
		LoadCursor(NULL,IDC_ARROW),	// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),	// クライアント領域の色
		NULL,						// メニューハンドル
		CLASS_NAME,					// ウィンドウクラス名
		NULL						// ミニアイコンハンドル
	};
	/* 構造体に代入
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	～
	*/

	// RECT構造体の生成
	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT dr;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウのサイズを求める
	AdjustWindowRect(&wr, dStyle, false);

	// クライアント領域のサイズを変数に代入
	lWindowWidth = wr.right - wr.left;
	lWindowHeight = wr.bottom - wr.top;

	// デスクトップのサイズを求める
	GetWindowRect(GetDesktopWindow(), &dr);

	// デスクトップのサイズを変数に代入
	lDesktopWidth = dr.right;
	lDesktopHeight = dr.bottom;

	nWindowX = lDesktopWidth < lWindowWidth ? 0 : ((int)lDesktopWidth - (int)lWindowWidth) / 2;				// ? だったら
	nWindowY = lDesktopHeight < lWindowHeight ? 0 : ((int)lDesktopHeight - (int)lWindowHeight) / 2;			// : そうでなければ

	// ウィンドウ作成
	HWND hWnd = CreateWindowEx(
		0,							// 拡張ウィンドウスタイル
		CLASS_NAME,
		WINDOW_NAME,
		dStyle,						// ウィンドウスタイル
		nWindowX,					// ウィンドウの左上x座標
		nWindowY,					// ウィンドウの左上y座標
		lWindowWidth,				// 幅
		lWindowHeight,				// 高さ
		NULL,						// 親ウィンドウへのハンドル
		NULL,						// メニューハンドル
		hInstance,
		NULL);

	// ウィンドウの表示
	ShowWindow(hWnd, nShowCmd);		// ウィンドウ、状態
	
	// ウィンドウの更新
	UpdateWindow(hWnd);

	DWORD dwExecLastTime = 0;		// 前フレームのゲーム処理が終わった時間
	DWORD dwCurrentTime = 0;		// 現在の時間

	// 分解能を設定
	timeBeginPeriod(1);

	if (!Init(hInstance, hWnd, TRUE))
	{
		MessageBox(hWnd, "初期化できなかった", "エラーメッセージ", MB_OK);
		exit(0);
	}

	// メッセージループ
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))		// 真だったら
		{// ウィンドウメッセージ処理
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を計る
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)	// 60fps（1/60秒経っていたら）
			{// ゲーム処理
				Update();
				Draw();
				dwExecLastTime = dwCurrentTime;
			}
		}
	} while (msg.message != WM_QUIT);

	Uninit();
	// 分解能を戻す
	timeEndPeriod(1);
	// リターン
	return (int)msg.wParam;

}

//=========================================================================================================================
// ウィンドウプロシージャ
//=========================================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	// switchケース
	switch (uMsg)
	{
	
	case WM_DESTROY:				// ここでウィンドウを本当に終わらせるかを判断。この後にメッセージボックスを出せばよい。
		PostQuitMessage(0);			// WM_QUITメッセージの送信
		break;

	case WM_CLOSE:					// 閉じるボタンが押された
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_KEYDOWN:				// キーが押された
		switch (wParam)
		{// switchケース
		case VK_ESCAPE:				// 【ESC】キーを押した（必ず終了はこれ）
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}//	switch終了
		break;

	case WM_LBUTTONDOWN:
	{// マウスを左クリックした
		SetFocus(hWnd);
		break;
	}

	default:
		break;

	}// switch終了

	// リターン
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		// 基本的なことをやってくれる

}

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	
	D3DDISPLAYMODE d3ddm;
	// Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	// デバイスのプレゼンテーションパラメータの設定
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

	// デバイスオブジェクトの生成
	// {デバイス作成制御}<描画>と<頂点処理>をハードウェアで行う
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
		D3DDEVTYPE_HAL,														// デバイスタイプ
		hWnd,																// フォーカスするウィンドウのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,								// デバイス作成制御の組み合わせ
		&d3dpp,																// デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))													// ★デバイスインターフェースへのポインタ★
	{
		MessageBox(hWnd, "Direct3Dデバイスを作ることが出来ませんでした", "エラーメッセージ", MB_OK);
		return false;
	}
	
	// レンダーステートパラメータの設定（描画の設定を切り替える）
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		// 第一引数：スイッチ

	// αブレンドを行う
	// SRC... 今から描くもの、つまりポリゴンにテクスチャを貼ったもの。
	// DEST...すでに描画されている画面のこと。
	// SRC_RGB * SRC_α + DEST_RGB * (1 - SRC_α)
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// テクスチャステージステート
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 乗算の左辺
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		// 乗算の右辺

	// セットサンプラーステート
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャアドレス外を参照したときに
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// どうしたらよいか（Ｕ、Ｖ）WRAP：反復

	// テクスチャフィルタリング
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// 実際のサイズより小さくなったときにかかるフィルタリング、線形保管
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// 実際のサイズより大きくなったときにフィルタリング
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);		// MIPMAP間を保管(NONEにすると使わなくなる)
	

	HRESULT hr;
	// ポリゴン初期化	
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
// 終了処理
//=========================================================================================================================
void Uninit(void)
{


	if(g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
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
// 更新処理
//=========================================================================================================================
void Update(void)
{
	UpdateKeyboard();
	UpdateScene();

}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void Draw(void)
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 150, 255, 255), 1.0f, 0);	// 1フレームに1回
	
	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))		// 1フレームに1回
	{


		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));

		DrawScene();	

		
		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();					// 1フレームに1回
	}


	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);	// 1フレームに1回
}

LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}
