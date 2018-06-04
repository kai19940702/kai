//******************************************************************
//
//							[ポリゴン描画.cpp]											
//			Author：Takahisa Tabuchi	作成日：2017/06/05			
//******************************************************************


//*************************************************************************************************************************
// インクルード
//*************************************************************************************************************************
#include "Main.h"
#include "Scene2D.h"
#include "Renderer.h"


//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************




//=========================================================================================================================
// ポリゴン初期化処理
//=========================================================================================================================
Scene2D::Scene2D(int Priority):Scene(Priority)
{
	g_PolygonColor = 0xffffffff;
	m_Texture = NULL;

}
Scene2D::~Scene2D()
{

}

void Scene2D::Init()
{
	LPDIRECT3DDEVICE9 device = Renderer::GetDevice();

	D3DXCreateTextureFromFile(device,															// デバイス
							"Kobeni.png",												// ファイル名（実行ファイルと同じ場所だったらそのまま）
							&m_Texture);													// テクスチャ保持アドレスのアドレス

}

void Scene2D::Uninit()
{
		if (m_Texture != NULL)
		{// テクスチャ保持の開放
			m_Texture->Release();
			m_Texture = NULL;
		}
}

void Scene2D::Update()
{
}

void Scene2D::Draw()
{
	LPDIRECT3DDEVICE9 device = Renderer::GetDevice();

	VERTEX_2D vtx[] = {// 頂点のセット（右回りに設定、STRIPはＺ）
		 { D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),  g_PolygonColor, D3DXVECTOR2(0, 0) },
		 { D3DXVECTOR4(200.0f,0.0f,1.0f, 1.0f),  g_PolygonColor, D3DXVECTOR2(1, 0) },
		 { D3DXVECTOR4(0.0f,200.0f, 1.0f, 1.0f),   g_PolygonColor, D3DXVECTOR2(0, 1) },
		 { D3DXVECTOR4(200,200,1.0f, 1.0f),    g_PolygonColor, D3DXVECTOR2(1, 1) }
	};

	device->SetTexture(0,m_Texture);
	device->SetFVF(FVF_VERTEX_2D);
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,vtx,sizeof(VERTEX_2D));
}

Scene2D* Scene2D::Create()
{
	Scene2D* Scene = new Scene2D(0);
	Scene->Init();
	return Scene;
}