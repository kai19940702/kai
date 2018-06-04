#include "CLight.h"
#include "Main.h"
#include "Renderer.h"

CLight::CLight()
{
	ZeroMemory(&light,sizeof(light));

	//ライトタイプ
	light.Type = D3DLIGHT_DIRECTIONAL;
}

CLight::~CLight()
{
}

void CLight::Init()
{
	

}
void CLight::Uninit()
{
}
void CLight::Update()
{

	//ライトの方向（単位ベクトル）
	D3DXVECTOR3 vecDir(-0.5f,-0.5f,1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction,&vecDir);

	//ライトの色
	light.Diffuse.r=1.0f;
	light.Diffuse.g=1.0f;
	light.Diffuse.b=1.0f;
	light.Diffuse.a=1.0f;

	light.Ambient.r=1.0f;
	light.Ambient.g=1.0f;
	light.Ambient.b=1.0f;
	light.Ambient.a=1.0f;


	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	pDevice->SetLight(0,&light);
	pDevice->LightEnable(0,TRUE);

	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //ライティングオン

	pDevice->SetRenderState(D3DRS_AMBIENT,D3DXCOLOR(0.3f,0.3f,0.3f,1.0f));
}
void CLight::Draw()
{
}