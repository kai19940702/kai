#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Main.h"





class Renderer
{
private:
	static LPDIRECT3D9 m_D3D;
	static LPDIRECT3DDEVICE9 m_D3DDevice;
public:
	static void Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit();
	static void DrawBegin();
	static void DrawEnd();
	static LPDIRECT3DDEVICE9 GetDevice();
};


#endif