#include "CManager.h"
#include "debug.h"
#include "CSky.h"
#include "Input.h"
#include "CBomb.h"


	Scene *Scene::m_Scene[10]={NULL};
	CCamera* camera = new CCamera;
	CLight* light = new CLight;

bool CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{	

	Renderer::Init(hInstance,hWnd,bWindow);

	//Scene2D::Create();
	//Scene3D::Create();
	//Model::Create();
	CSky::Create();
	CFiled::Create();
	CPlayer::Create();
	CBomb::Create();

	InitKeyboard(hInstance,hWnd);


	camera->Init(hWnd);
	light->Init();

	InitDebugString();



	return S_OK;
}
void CManager::Uninit(void)
{

	camera->Uninit();
	delete(camera);
	light->Uninit();
	delete(light);

	UninitKeyboard();


	Scene::ReleaseAll();


	Renderer::Uninit();

	UninitDebugString();

}
void CManager::Update(void)
{
	camera->Update();
	light->Update();

	UpdateKeyboard();

	Scene::UpdateAll();
}

void CManager::Draw(void)
{

	Renderer::DrawBegin();

	Scene::DrawAll();

	Renderer::DrawEnd();

}