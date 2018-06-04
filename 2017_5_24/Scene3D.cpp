#include "Main.h"
#include "Scene3D.h"
#include "Scene2D.h"
#include "Renderer.h"



// 配列数える


Scene3D::Scene3D(int Priority):Scene(Priority)
{
	v[0].pos = D3DXVECTOR3(-0.5,0.0,-0.5);v[0].color=D3DCOLOR_RGBA(255,255,255,255);v[0].texcoord=D3DXVECTOR2(0.25f,0.25f);
	v[1].pos = D3DXVECTOR3(-0.5,0.0,0.5); v[1].color=D3DCOLOR_RGBA(255,255,255,255);v[1].texcoord=D3DXVECTOR2(0.25f,0.0f);
	v[2].pos = D3DXVECTOR3(0.5,0.0,-0.5); v[2].color=D3DCOLOR_RGBA(255,255,255,255);v[2].texcoord=D3DXVECTOR2(0.5f,0.25f);
	v[3].pos = D3DXVECTOR3(0.5,0.0,0.5);  v[3].color=D3DCOLOR_RGBA(255,255,255,255);v[3].texcoord=D3DXVECTOR2(0.5f,0.0f);

	 index[0]= 0;index[1]= 1;index[2]= 2;index[3]= 1;index[4]= 3;index[5]= 2;


}
Scene3D::~Scene3D()
{

}

void Scene3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();


	HRESULT hr;

	for (int i = 0; i < 1; i++)
	{
		hr = D3DXCreateTextureFromFile(
			pDevice,															// デバイス
			"horoCube.png",												// ファイル名（実行ファイルと同じ場所だったらそのまま）
			&g_pTextures3D[i]);													// テクスチャ保持アドレスのアドレス


	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *4, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&g_pVertexBuffer, //管理者のポインタ
								NULL);


	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&g_pIndexBuffer, //管理者のポインタ
								NULL);

	VERTEX_3D* pV;
	LPWORD pIndex;

	g_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(v));
	g_pVertexBuffer->Unlock();


	g_pIndexBuffer->Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);
	memcpy(pIndex,index,sizeof(index));
	g_pIndexBuffer->Unlock();

}

void Scene3D::Uninit()
{
	if(g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;

	}

	if(g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;

	}
	for (int i = 0; i < 1; i++)
	{
		if (g_pTextures3D[i] != NULL)
		{// テクスチャ保持の開放
			g_pTextures3D[i]->Release();
			g_pTextures3D[i] = NULL;
		}
	}
}

void Scene3D::Update()
{
	D3DXMatrixIdentity( &g_mtxWorld );
	D3DXMatrixScaling( &g_mtxWorld, 5 , 1 , 5 );
}

void Scene3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();


	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //ライティングオン

	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D);//今から色と頂点を送るという意味


		pDevice->SetStreamSource(0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_3D)); //１頂点分のサイズ

		pDevice->SetIndices(g_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures3D[0]);						// テクスチャ保持アドレス

//---------描画処理------------------//

		//各種行列の設定(好きなタイミングで設定してOK)
		pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//プリミティブタイプ
									0,					//ベース
									0,					//インデックス最小
									4,					//頂点数
									0,
									2);				//プリミティブ数

}

Scene3D* Scene3D::Create()
 {
	 Scene3D* Scene = new Scene3D(1);
	 Scene->Init();
	 return Scene;
 }


/*
void CBullet::Update()
{
	for()
	{
		if(m_Scene[i]->GetType()==SCENE_TYPE_ENEMY)
		{
			CEnemy *enemy = (CEnemy*)m_Scene[i]
			enemyPosition = enemy->GetPosition();
			if(衝突判定)
			{

			}
		}
	}
}
*/