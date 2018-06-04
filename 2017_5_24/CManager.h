#ifndef _CMANAGER_H_
#define _CMANAGER_H_



#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneModel.h"
#include "CFiled.h"
#include "Main.h"
#include "CPlayer.h"
#include "Camera.h"
#include "CLight.h"
#include "Renderer.h"
#include "Scene.h"

class CManager
{
	

public:
	static bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);

};


#endif