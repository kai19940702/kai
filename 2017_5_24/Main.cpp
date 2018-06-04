#include "CManager.h"
#include "Main.h"



//　きれいなソースコードを書いてください
//　マクロ定義
#define CLASS_NAME		"SAMPLE"
#define WINDOW_NAME		"directx"
#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)
#define SCREEN_STYLE	WS_OVERLAPPEDWINDOW^WS_MINIMIZEBOX^WS_MAXIMIZEBOX


//　プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




// メイン関数 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wecx = {
		sizeof(WNDCLASSEX),			// この構造体（自身）のサイズ
		CS_VREDRAW | CS_HREDRAW,	// style
		WndProc,					// アドレスのこと：後でポインタを作ります
		0,
		0,
		hInstance,					// WinMainのインスタンスハンドル
		NULL,						// アイコンハンドル（今回なし）
		LoadCursor(NULL,IDC_ARROW), // カーソルハンドル
		(HBRUSH)(COLOR_WINDOW+1),	// ウインドウのクライアント領域の背景色
		NULL,						// メニュー
		CLASS_NAME,					// クラスネーム：後で変数を作る
		NULL,						// ミニアイコン

	};								// 構造体の初期化

	RegisterClassEx(&wecx);			// ウィンドウクラスの登録（親ウィンドウ）
	
	RECT wr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect(&wr, SCREEN_STYLE, false);
	//entering breaking point to check
	//use this kansuu to make sure size correct

	RECT dr;
	GetWindowRect(GetDesktopWindow(),&dr);
	// パソコンの画面の解析度

	HWND hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		SCREEN_STYLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	// ウィンドウの表示
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	
	DWORD dwExceLastTime = 0;
	DWORD dwCurrentTime = 0;

	timeBeginPeriod(1);

	//before start anywhere
	CManager::Init(hInstance, hWnd, TRUE);
	


	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			
			// ウィンドウメッセージ処理
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			dwCurrentTime = timeGetTime();// ミリ秒単位

			if ((dwCurrentTime - dwExceLastTime) * 60 >= 1000)

			{// ゲーム処理　ゲームループ


				CManager::Update();
				CManager::Draw();

				dwExceLastTime = dwCurrentTime;

			}
		}
	}while(msg.message != WM_QUIT);

	//
	timeEndPeriod(1);
	CManager::Uninit();

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	
	switch (uMsg)
	{


	case WM_DESTROY:
		PostQuitMessage(0); // WM_QUITメッセージの送信（何か状態があったら管理者にメッセージを送るなど）
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					//ESCキーを押されたら

		nID = MessageBox(hWnd, "終了しますか？", "GM", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	// ウィンドウを閉める
			}
			break;

		}

		break;


	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



