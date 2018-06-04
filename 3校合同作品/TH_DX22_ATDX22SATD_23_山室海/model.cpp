#include "model.h"
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "xnamath.h"
#include "BillBoard.h"
#include "Effect.h"
#include "Change.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Homing.h"
#include "Sound.h"
#include "Rock_On.h"

#define FilePass (texture\\)


static int count=0;

static bool Change_flag=false;

static LPD3DXMESH g_pMesh = NULL;
static DWORD g_nMaterialNum = 0;
static LPD3DXBUFFER g_pMaterials = NULL;

static D3DMATERIAL9*		pMeshMat;	// マテリアル情報
static LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ



static LPD3DXMESH g_pMesh2 = NULL;
static DWORD g_nMaterialNum2 = 0;
static LPD3DXBUFFER g_pMaterials2 = NULL;

static D3DMATERIAL9*		pMeshMat2;	// マテリアル情報
static LPDIRECT3DTEXTURE9*	pMeshTex2;

//-----------------そら--------------------------//

static LPD3DXMESH g_pMesh_s = NULL;
static DWORD g_nMaterialNum_s = 0;
static LPD3DXBUFFER g_pMaterials_s = NULL;

static D3DMATERIAL9*		pMeshMat_s;	// マテリアル情報
static LPDIRECT3DTEXTURE9*	pMeshTex_s;	// メッシュのテクスチャ




static D3DXMATRIX g_mtxWorld;
static D3DXMATRIX g_mtxWorld2;
static D3DXMATRIX k_mtxWorld;
static D3DXMATRIX g_mtxWorld_s;


static bool fin_flag=false;



static int rock_on_count=0;
static int count2=0;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 pos_before;
	D3DXVECTOR3 front;
	D3DXVECTOR3 front_now;
	D3DXVECTOR3 up;
	D3DXVECTOR3 up_now;
	float spin;
	bool spin_flag;

	float spin2;
	bool spin_flag2;

	bool use;

}PLAYER;

PLAYER player;

void InitModel(void)
{
	player. spin_flag=false;
	player.use=true;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;

	//----------------空------------------------//


	hr = D3DXLoadMeshFromX("sora.x",
						   D3DXMESH_MANAGED,
						   pDevice,
						   &pAdjacency,
						   &g_pMaterials_s,NULL,
						   &g_nMaterialNum_s,
						   &g_pMesh_s);

	if ( FAILED (hr) )
	{// ★エラーチェック絶対やる★
		MessageBox(NULL, "モデルが読み込めませんでした", "エラーメッセージ", MB_OK);
	}

	hr = D3DXLoadMeshFromX("hikouki2.x",
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

	hr = D3DXLoadMeshFromX("hikouki.x",
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




		hr = g_pMesh2->OptimizeInplace(D3DXMESHOPT_COMPACT|
							 D3DXMESHOPT_ATTRSORT|
							 D3DXMESHOPT_VERTEXCACHE,
							 (DWORD*)pAdjacency->GetBufferPointer(),
							 NULL,
							 NULL,
							 NULL);

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
	//		MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
		}

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


//---------------------------------------------------------------//
/*
	hr = g_pMesh_s->OptimizeInplace(D3DXMESHOPT_COMPACT|
						 D3DXMESHOPT_ATTRSORT|
						 D3DXMESHOPT_VERTEXCACHE,
						 (DWORD*)pAdjacency->GetBufferPointer(),
						 NULL,
						 NULL,
						 NULL);
*/
	if ( FAILED (hr) )
	{// ★エラーチェック絶対やる★
		MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
	}


	LPD3DXMESH pCloneMesh_s;
	D3DVERTEXELEMENT9 elements_s[MAXD3DDECLLENGTH+1];

	g_pMesh_s->GetDeclaration(elements_s);
	g_pMesh_s->CloneMesh(D3DXMESH_MANAGED|
					   D3DXMESH_WRITEONLY,
					   elements_s,
					   pDevice,
					   &pCloneMesh_s);

	g_pMesh_s->Release();

	g_pMesh_s = pCloneMesh_s;
	
	
//-----------------------------------------------------------------------------//

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
			//	MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
			}
		}
		
		
	}

//------------------------------------------------------------------------//



	D3DXMATERIAL* d3Mat2= (D3DXMATERIAL*)g_pMaterials2 -> GetBufferPointer();

	pMeshMat2 = new D3DMATERIAL9[ g_nMaterialNum2 ];		// メッシュ情報を確保
	pMeshTex2 = new LPDIRECT3DTEXTURE9[ g_nMaterialNum2 ];// テクスチャを確保

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
			//	MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
			}
		}
		
		
	}

	D3DXMATERIAL* d3Mat_s= (D3DXMATERIAL*)g_pMaterials_s -> GetBufferPointer();

	pMeshMat_s = new D3DMATERIAL9[ g_nMaterialNum_s ];		// メッシュ情報を確保
	pMeshTex_s = new LPDIRECT3DTEXTURE9[ g_nMaterialNum_s ];// テクスチャを確保


	for(int  i = 0; i < g_nMaterialNum_s; i++ )
	{
		pMeshMat_s[i] = d3Mat_s[i].MatD3D;			// マテリアル情報セット
		pMeshTex_s[i] = NULL;	// テクスチャ初期化
	
		if( d3Mat_s[i].pTextureFilename != NULL  )
		{
				// テクスチャ読み込み
				hr=D3DXCreateTextureFromFile(
								pDevice,
								d3Mat_s[i].pTextureFilename,
								&pMeshTex_s[i] );

			if ( FAILED (hr) )
			{// ★エラーチェック絶対やる★
				MessageBox(NULL, "メッシュ", "エラーメッセージ", MB_OK);
			}
		}
		
		
	}
	player.pos=D3DXVECTOR3(0.0f,1.0f,0.0f);
	player.front=player.front_now=D3DXVECTOR3(0.0f,0.0f,1.0f);
	player.up=player.up_now=D3DXVECTOR3(0.0f,1.0f,0.0f);

	player.spin=0.0f;
	D3DXMatrixIdentity(&g_mtxWorld);

	player.use=true;
	fin_flag=false;
//	g_pMaterials->Release();

}
void UninitModel(void)
{
	player. spin_flag=false;
	player.use=true;

	DWORD	i;

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

}
void DrawModel(void)
{



	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();


	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

	pDevice->LightEnable(0,TRUE);

	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //ライティングオン

	
	if(player.use)
	{
		if(!Change_flag)
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
			for(int i= 0 ; i < g_nMaterialNum2 ; i++)
			{
				pDevice->SetMaterial( &pMeshMat2[i] );
				pDevice->SetTexture(0,pMeshTex2[i]);
				g_pMesh2->DrawSubset(i);
			}
		}
	}
		
	
}

bool UpdateModel(void)
{
	if(GetKeyboardPress(DIK_S))
	{
		rock_on_count++;
		if(rock_on_count>30)
		{
			CreateRock_On();
			//CreateHoming(Change_flag);
			//PlaySound(SOUND_LABEL_BEAM);
			rock_on_count=0;
			count2++;
		}

	}

		if(GetKeyboardRelease(DIK_S)&&count2>0)
		{
			CreateHoming(Change_flag);
			PlaySound(SOUND_LABEL_BEAM);
			count2=0;
		}

	if(GetKeyboardTrigger(DIK_A))
	{
		CreateRock_On();
	}
	count++;

	if(count>20)
	{
		if(!fin_flag)
		{
			CreateBuullet(Change_flag,player.pos.x-0.15);
			CreateBuullet(Change_flag,player.pos.x+0.15);
			PlaySound(SOUND_LABEL_SHOT);
			count=0;
		}
	}
	player.pos_before=player.pos;

	player.spin_flag=false;
	player.spin_flag2=false;

	player.pos.z+=0;


	if(GetKeyboardTrigger(DIK_SPACE))
	{
		

		if(CreateChage(player.pos,Change_flag))
		{
			PlaySound(SOUND_LABEL_ORA);
			if(Change_flag)
			{
				Change_flag=false;
			}
			else
			{
				Change_flag=true;
			}
		}
		  
	}

	//CreatEffect(player.pos.x+1.5, player.pos.y-0.2,player.pos.z, 100, false);

//---------------上下回転----------------//
	if(GetKeyboardPress(DIK_UP))
	{
		player.spin_flag2=true;
		player.spin2-=0.05;

		if(player.spin2<-0.5)
		{
			player.spin2+=0.05;
		}
		else
		{
			D3DXMatrixRotationX( &g_mtxWorld2,(-0.05));
			D3DXVec3TransformNormal(&player.front_now,&player.front_now,&g_mtxWorld2);	
		}
		player.pos.y+=0.1;

	}

	//右
	else if(GetKeyboardPress(DIK_DOWN))
	{
		player.spin_flag2=true;
		player.spin2+=0.05;

		if(player.spin2>0.5)
		{
			player.spin2-=0.05;
		}
		else
		{
			D3DXMatrixRotationX( &g_mtxWorld2,(0.05));
			D3DXVec3TransformNormal(&player.front_now,&player.front_now,&g_mtxWorld2);	
		}
		player.pos.y-=0.1;
	}

	if(player.front_now!=player.front&&!player.spin_flag2)
	{
		if(player.spin2>0)
		{
			player.spin2-=0.05;

			D3DXMatrixRotationX( &g_mtxWorld2,(-0.05));
		}
		else if(player.spin2<0)
		{
			player.spin2+=0.05;

			D3DXMatrixRotationX( &g_mtxWorld2,(0.05));
		}
		D3DXVec3TransformNormal(&player.front_now,&player.front_now,&g_mtxWorld2);
		float dot =D3DXVec3Dot(&player.front_now,&player.front);

		if(dot<=1&&dot>0.99)
		{
			player.front_now=player.front;
			player.spin2=0;
		}
	}

//------------------左右回転-------------------------------------//

//右
	 if(GetKeyboardPress(DIK_RIGHT))
	{
		player.spin_flag=true;
		player.spin-=0.05;
		if(player.spin<-0.5)
		{
			player.spin+=0.05;

		}
		else
		{
			D3DXMatrixRotationZ( &g_mtxWorld2,(-0.05));
			D3DXVec3TransformNormal(&player.up_now,&player.up_now,&g_mtxWorld2);	
		}
		player.pos.x+=0.1;
	}

//左	
	else if(GetKeyboardPress(DIK_LEFT))
	{
		player.spin_flag=true;
		player.spin+=0.05;

		if(player.spin>0.5)
		{
			player.spin-=0.05;
		}
		else
		{
			D3DXMatrixRotationZ( &g_mtxWorld2,(0.05));
			D3DXVec3TransformNormal(&player.up_now,&player.up_now,&g_mtxWorld2);	
		}
		player.pos.x-=0.1;
	}
	
	

	if(player.up_now!=player.up&&!player.spin_flag)
	{
		if(player.spin>0)
		{
			player.spin-=0.05;

			D3DXMatrixRotationZ( &g_mtxWorld2,(-0.05));
	
		}
		else if(player.spin<0)
		{
			player.spin+=0.05;

			D3DXMatrixRotationZ( &g_mtxWorld2,(0.05));
		}
		D3DXVec3TransformNormal(&player.up_now,&player.up_now,&g_mtxWorld2);
		float dot =D3DXVec3Dot(&player.up_now,&player.up);

		if(dot<=1&&dot>0.99)
		{
			player.up_now=player.up;
			player.spin=0;
		}
	}

	if(player.pos.y<1||player.pos.y>25)
	{
		player.pos=player.pos_before;
	}



	if(player.pos.x<-15||player.pos.x>15)
	{
		player.pos=player.pos_before;
	}

	// CreatEffect( player.pos.x, player.pos.y , player.pos.z ,30, false);
	

	D3DXMatrixTranslation(&g_mtxWorld_s,20,20,20);

	//サイズ調整
	D3DXMatrixScaling (&g_mtxWorld,0.3,0.3,0.3);

	//向き調整
	D3DXMatrixRotationY( &k_mtxWorld,-1.57);
	g_mtxWorld*=k_mtxWorld;

	//左右回転
	D3DXMatrixRotationZ( &k_mtxWorld,player.spin);

	g_mtxWorld*=k_mtxWorld;

	//上下回転
	D3DXMatrixRotationX( &k_mtxWorld,player.spin2);

	g_mtxWorld*=k_mtxWorld;

	D3DXMatrixTranslation( &k_mtxWorld,player.pos.x,player.pos.y,player.pos.z);

	g_mtxWorld*=k_mtxWorld;



	if(!fin_flag)
	{
		for(int i=0 ; i<20 ; i++)
		{
			if(HitCircle2(player.pos.x,player.pos.y,player.pos.z,1,GetEnemyPos(i).x,GetEnemyPos(i).y,GetEnemyPos(i).z,2))
			{
				CreateExplosion(player.pos);
				player.use=false;
				fin_flag=true;
				break;
			}

		}
	}



	
	return fin_flag;

}

D3DXVECTOR3* GetPlayerPos(void)
{
	return &player.pos;
}

D3DXVECTOR3* GetPlayerfront(void)
{
	return &player.front_now;
}

bool HitCircle2(float x0, float y0 , float z0 ,float r0, float x1, float y1, float z1 , float r1)
{
	/*x0 - x0 = 0;
	y0 - y0 = 0;
	x1 - x0;
	y1 - y0;*/

	float x = x1 - x0;
	float y = y1 - y0;
	float z = z1 - z0;
	float l = x*x + y*y +z*z ;	// lは斜辺の二乗の長さ

	return l < (r0 + r1) * (r0 + r1);
	
}