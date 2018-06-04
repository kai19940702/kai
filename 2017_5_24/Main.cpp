#include "CManager.h"
#include "Main.h"



//�@���ꂢ�ȃ\�[�X�R�[�h�������Ă�������
//�@�}�N����`
#define CLASS_NAME		"SAMPLE"
#define WINDOW_NAME		"directx"
#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)
#define SCREEN_STYLE	WS_OVERLAPPEDWINDOW^WS_MINIMIZEBOX^WS_MAXIMIZEBOX


//�@�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




// ���C���֐� 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wecx = {
		sizeof(WNDCLASSEX),			// ���̍\���́i���g�j�̃T�C�Y
		CS_VREDRAW | CS_HREDRAW,	// style
		WndProc,					// �A�h���X�̂��ƁF��Ń|�C���^�����܂�
		0,
		0,
		hInstance,					// WinMain�̃C���X�^���X�n���h��
		NULL,						// �A�C�R���n���h���i����Ȃ��j
		LoadCursor(NULL,IDC_ARROW), // �J�[�\���n���h��
		(HBRUSH)(COLOR_WINDOW+1),	// �E�C���h�E�̃N���C�A���g�̈�̔w�i�F
		NULL,						// ���j���[
		CLASS_NAME,					// �N���X�l�[���F��ŕϐ������
		NULL,						// �~�j�A�C�R��

	};								// �\���̂̏�����

	RegisterClassEx(&wecx);			// �E�B���h�E�N���X�̓o�^�i�e�E�B���h�E�j
	
	RECT wr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect(&wr, SCREEN_STYLE, false);
	//entering breaking point to check
	//use this kansuu to make sure size correct

	RECT dr;
	GetWindowRect(GetDesktopWindow(),&dr);
	// �p�\�R���̉�ʂ̉�͓x

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

	// �E�B���h�E�̕\��
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
			
			// �E�B���h�E���b�Z�[�W����
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			dwCurrentTime = timeGetTime();// �~���b�P��

			if ((dwCurrentTime - dwExceLastTime) * 60 >= 1000)

			{// �Q�[�������@�Q�[�����[�v


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
		PostQuitMessage(0); // WM_QUIT���b�Z�[�W�̑��M�i������Ԃ���������Ǘ��҂Ƀ��b�Z�[�W�𑗂�Ȃǁj
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					//ESC�L�[�������ꂽ��

		nID = MessageBox(hWnd, "�I�����܂����H", "GM", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	// �E�B���h�E��߂�
			}
			break;

		}

		break;


	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



