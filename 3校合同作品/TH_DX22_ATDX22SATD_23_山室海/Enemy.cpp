#include "Enemy.h"
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "xnamath.h"
#include "BillBoard.h"
#include "Effect.h"
#include <time.h>
#include <math.h>
#include "Sound.h"
#include "Rock_On.h"

#define FilePass (texture\\)

static LPD3DXMESH g_pMesh = NULL;
static DWORD g_nMaterialNum = 0;
static LPD3DXBUFFER g_pMaterials = NULL;


static D3DXMATRIX g_mtxWorld2;
static D3DXMATRIX k_mtxWorld;

static D3DMATERIAL9*		pMeshMat;	// マテリアル情報
static LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ


//-----------------------------------------------------//

static LPD3DXMESH g_pMesh2 = NULL;
static DWORD g_nMaterialNum2 = 0;
static LPD3DXBUFFER g_pMaterials2 = NULL;


static D3DXMATRIX g_mtxWorld22;
static D3DXMATRIX k_mtxWorld2;

static D3DMATERIAL9*		pMeshMat2;	// マテリアル情報
static LPDIRECT3DTEXTURE9*	pMeshTex2;	// メッシュのテクスチャ



typedef struct
{
	D3DXMATRIX g_mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 pos_before;
	D3DXVECTOR3 front;
	D3DXVECTOR3 front_now;
	D3DXVECTOR3 up;
	D3DXVECTOR3 up_now;
	float spin;
	bool spin_flag;
	bool type;
	float spin2;
	bool spin_flag2;
	bool use;
	float deg;
	bool rock;
	int rock_num;

}ENEMY;

ENEMY enemy[20];


int count=0;

void InitEnemy(void)
{
	count=0;

	for(int i=0 ;i<20 ; i++)
	{
		enemy[i].use=false;
		enemy[i].pos=D3DXVECTOR3(0,0,100);
		enemy[i].deg=0;
		enemy[i].rock=false;
		enemy[i].rock_num=-1;
	}

	srand(time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;

	hr = D3DXLoadMeshFromX("enemy_blue.x",
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
//			MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
		}

	hr = D3DXLoadMeshFromX("enemy_red.x",
						   D3DXMESH_MANAGED,
						   pDevice,
						   &pAdjacency,
						   &g_pMaterials2,NULL,
						   &g_nMaterialNum2,
						   &g_pMesh2);

	if ( FAILED (hr) )
	{// ★エラーチェック絶対やる★
		MessageBox(NULL, "モデルが読み込めませんでした", "エラーメッセージ", MB_OK);
	}

	


		hr = g_pMesh2->OptimizeInplace(D3DXMESHOPT_COMPACT|
							 D3DXMESHOPT_ATTRSORT|
							 D3DXMESHOPT_VERTEXCACHE,
							 (DWORD*)pAdjacency->GetBufferPointer(),
							 NULL,
							 NULL,
							 NULL);

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
//			MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
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

	//----------------------------------------------

	LPD3DXMESH pCloneMesh2;
	D3DVERTEXELEMENT9 elements2[MAXD3DDECLLENGTH+1];

	g_pMesh2->GetDeclaration(elements2);
	g_pMesh2->CloneMesh(D3DXMESH_MANAGED|
					   D3DXMESH_WRITEONLY,
					   elements2,
					   pDevice,
					   &pCloneMesh2);

	g_pMesh2->Release();

	g_pMesh2 = pCloneMesh2;



	D3DXMATERIAL* d3Mat= (D3DXMATERIAL*)g_pMaterials -> GetBufferPointer();

	pMeshMat = new D3DMATERIAL9[ g_nMaterialNum ];		// メッシュ情報を確保
	pMeshTex = new LPDIRECT3DTEXTURE9[ g_nMaterialNum ];// テクスチャを確保


	D3DXMATERIAL* d3Mat2= (D3DXMATERIAL*)g_pMaterials2 -> GetBufferPointer();

	pMeshMat2 = new D3DMATERIAL9[ g_nMaterialNum2 ];		// メッシュ情報を確保
	pMeshTex2 = new LPDIRECT3DTEXTURE9[ g_nMaterialNum2 ];// テクスチャを確保

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
		//		MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
			}
		}
		
		
	}


	for(int  i = 0; i < g_nMaterialNum2; i++ )
	{
		pMeshMat2[i] = d3Mat2[i].MatD3D;			// マテリアル情報セット
		pMeshTex2[i] = NULL;	// テクスチャ初期化
	
		if( d3Mat2[i].pTextureFilename != NULL  )
		{
				// テクスチャ読み込み
				hr=D3DXCreateTextureFromFile(
								pDevice,
								d3Mat2[i].pTextureFilename,
								&pMeshTex2[i] );

			if ( FAILED (hr) )
			{// ★エラーチェック絶対やる★
		//		MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
			}
		}
		
		
	}



//	g_pMaterials->Release();

}
void UninitEnemy(void)
{
	
	DWORD	i;


	for(int i=0 ;i<20 ; i++)
	{
		enemy[i].use=false;
		enemy[i].pos=D3DXVECTOR3(0,0,100);
		enemy[i].deg=0;
	}

	// テクスチャ開放
	for( i = 0; i < g_nMaterialNum; i++ )
	{
//		pMeshTex[i]->Release();
//		pMeshTex[i]	= NULL;
	}
	delete [] pMeshTex;
	pMeshTex	= NULL;
	delete [] pMeshMat;
	pMeshMat	= NULL;



	for(int i=0 ;i<20 ; i++)
	{
		enemy[i].use=false;
		enemy[i].pos=D3DXVECTOR3(0,0,100);
		enemy[i].deg=0;
	}

}
void DrawEnemy(void)
{



	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();


	for(int i=0 ; i <20 ; i++)
	{
		if(enemy[i].use)
		{
			pDevice->SetTransform(D3DTS_WORLD,&enemy[i].g_mtxWorld);

			pDevice->LightEnable(0,TRUE);

			pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //ライティングオン

			if(enemy[i].type)
			{

				for(int i= 0 ; i < g_nMaterialNum ; i++)
				{
					pDevice->SetMaterial( &pMeshMat[i] );
					pDevice->SetTexture(0,pMeshTex[i]);
					g_pMesh->DrawSubset(i);
				}
			}
			else
			{
				for(int i= 0 ; i < g_nMaterialNum ; i++)
				{
					pDevice->SetMaterial( &pMeshMat2[i] );
					pDevice->SetTexture(0,pMeshTex2[i]);
					g_pMesh2->DrawSubset(i);
				}
			}
		}
	}

}

void UpdateEnemy(void)
{

	//count++;
	if(rand()%60==1)
	{

		CreateEnemy(true);
	}
	if(rand()%60==2)
	{
		CreateEnemy(false);
	}

	for(int i=0 ; i<20 ; i++)
	{
		if(enemy[i].use)
		{
			enemy[i].pos_before=enemy[i].pos;

			enemy[i].pos.z-=0.1;
			enemy[i].deg+=0.02;
			if(count>600)
			{
				enemy[i].pos.y+=sin(enemy[i].deg)/5;
			
			}
			if(count>1200)
			{
				enemy[i].pos.z-=0.1;
			}

			if(count>1800)
			{
				enemy[i].pos.z-=0.1;
			}
			D3DXMatrixTranslation(&k_mtxWorld,enemy[i].pos.x,enemy[i].pos.y,enemy[i].pos.z);

			//サイズ調整
			D3DXMatrixScaling (&enemy[i].g_mtxWorld,1.5,1.5,1.5);
			enemy[i].g_mtxWorld*=k_mtxWorld;

			if(enemy[i].pos.z<-2)
			{
				DestroyEnemy(i);

			}
		}
	}

}

void CreateEnemy(bool type)
{
	for (int i=0 ; i<20 ; i++)
	{
		if(!enemy[i].use)
		{
			enemy[i].use=true;
			enemy[i].pos=D3DXVECTOR3(rand()%20,rand()%20+2,70.0f);
			if(rand()%2==1)
			{
				enemy[i].pos.x*=-1;
			}
			enemy[i].front=enemy[i].front_now=D3DXVECTOR3(0.0f,0.0f,-1.0f);
			enemy[i].up=enemy[i].up_now=D3DXVECTOR3(0.0f,1.0f,0.0f);
			enemy[i].type=type;
			enemy[i].spin=0.0f;
			D3DXMatrixIdentity(&enemy[i].g_mtxWorld);
			break;
		}
	}
}
void DestroyEnemy(int index)
{
	enemy[index].use=false;
	enemy[index].rock=false;

}

D3DXVECTOR3 GetEnemyPos(int index)
{
	return enemy[index].pos;
}

D3DXVECTOR3* GetEnemyfront(int index)
{
	return &enemy[index].front_now;
}
bool GetEnemyType(int index)
{
	return enemy[index].type;
}

bool GetEnemyRock(int index)
{
	return enemy[index].rock;
}
void RockOn_Enemy (int index,int num)
{
	enemy[index].rock=true;
	enemy[index].rock_num=num;
}

void DestroyEnemy_rock(int index)
{
	enemy[index].rock=false;

	if(enemy[index].rock_num!=-1)
	{
		Destroty_Rock_On(enemy[index].rock_num);
		enemy[index].rock_num=-1;
	}
}
