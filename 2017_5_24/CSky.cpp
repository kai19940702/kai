#include "CSky.h"
#include "Main.h"
#include "Renderer.h"
#include <d3d9.h>
#include <d3dx9.h>


#define FilePass (texture\\)






CSky::CSky(int Priority):Scene(Priority)
{
	g_pMesh = NULL;
	g_nMaterialNum = 0;
	g_pMaterials = NULL;
}
CSky::~CSky()
{
}


void CSky::Init()
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;

	hr = D3DXLoadMeshFromX("sky_dome_27.x",
						   D3DXMESH_MANAGED,
						   pDevice,
						   &pAdjacency,
						   &g_pMaterials,NULL,
						   &g_nMaterialNum,
						   &g_pMesh);

	if ( FAILED (hr) )
	{// ★エラーチェック絶対やる★
		MessageBox(NULL, "モデルが読み込めませんでした", "エラーメッセージ", MB_OK);
	}



		hr = g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT|
							 D3DXMESHOPT_ATTRSORT|
							 D3DXMESHOPT_VERTEXCACHE,
							 (DWORD*)pAdjacency->GetBufferPointer(),
							 NULL,
							 NULL,
							 NULL);

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
			MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
		}

	LPD3DXMESH pCloneMesh;
	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH+1];

	g_pMesh->GetDeclaration(elements);
	g_pMesh->CloneMesh(D3DXMESH_MANAGED|
					   D3DXMESH_WRITEONLY,
					   elements,
					   pDevice,
					   &pCloneMesh);

	g_pMesh->Release();

	g_pMesh = pCloneMesh;

	D3DXMATERIAL* d3Mat= (D3DXMATERIAL*)g_pMaterials -> GetBufferPointer();

	pMeshMat = new D3DMATERIAL9[ g_nMaterialNum ];		// メッシュ情報を確保
	pMeshTex = new LPDIRECT3DTEXTURE9[ g_nMaterialNum ];// テクスチャを確保

	for(int  i = 0; i < g_nMaterialNum; i++ )
	{
		pMeshMat[i] = d3Mat[i].MatD3D;			// マテリアル情報セット
		pMeshTex[i] = NULL;	// テクスチャ初期化
	
		if( d3Mat[i].pTextureFilename != NULL  )
		{
				// テクスチャ読み込み
				hr=D3DXCreateTextureFromFile(
								pDevice,
								d3Mat[i].pTextureFilename,
								&pMeshTex[i] );

			if ( FAILED (hr) )
			{// ★エラーチェック絶対やる★
				MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
			}
		}
		
		
	}

	D3DXMatrixIdentity(&g_mtxWorld);
//	g_pMaterials->Release();

}
void CSky::Uninit()
{


	// テクスチャ開放
	for(int i = 0; i < g_nMaterialNum; i++ )
	{
		if(pMeshTex[i]	!= NULL)
		{
			pMeshTex[i]->Release();
			pMeshTex[i]	= NULL;
		}
	}
	delete [] pMeshTex;
	pMeshTex	= NULL;
	delete [] pMeshMat;
	pMeshMat	= NULL;

}
void CSky::Draw()
{



	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();


	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

	pDevice->LightEnable(0,TRUE);

	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //ライティングオン


	for(int i= 0 ; i < g_nMaterialNum ; i++)
	{
		pDevice->SetMaterial( &pMeshMat[i] );
		pDevice->SetTexture(0,pMeshTex[i]);
		g_pMesh->DrawSubset(i);
	}

}

void CSky::Update()
{
	D3DXMatrixRotationY(&g_mtxWorld2,0.0002f);
	g_mtxWorld*=g_mtxWorld2;
}

CSky* CSky::Create()
 {
	 CSky* Scene = new CSky(2);
	 Scene->Init();
	 return Scene;
 }