#include "light.h"
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h>


	//���C�g�쐬
	D3DLIGHT9 light;

void InitLight(void)
{

	ZeroMemory(&light,sizeof(light));

	//���C�g�^�C�v
	light.Type = D3DLIGHT_DIRECTIONAL;

	

}
void UninitLight(void)
{
}
void UpdateLight(void)
{

	//���C�g�̕����i�P�ʃx�N�g���j
	D3DXVECTOR3 vecDir(0.0f,-0.3f,1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction,&vecDir);

	//���C�g�̐F
	light.Diffuse.r=1.0f;
	light.Diffuse.g=1.0f;
	light.Diffuse.b=1.0f;
	light.Diffuse.a=1.0f;

	light.Ambient.r=1.0f;
	light.Ambient.g=1.0f;
	light.Ambient.b=1.0f;
	light.Ambient.a=1.0f;


	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetLight(0,&light);
	pDevice->LightEnable(0,TRUE);

	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //���C�e�B���O�I��

	pDevice->SetRenderState(D3DRS_AMBIENT,D3DXCOLOR(0.3f,0.3f,0.3f,1.0f));
}
void DrawLight(void)
{
}