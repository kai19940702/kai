#include "model.h"
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "xnamath.h"
#include "BillBoard.h"
#include "Effect.h"
#include "Change.h"


#define FilePass (texture\\)


static int count=0;

static bool Change_flag=false;

static LPD3DXMESH g_pMesh = NULL;
static DWORD g_nMaterialNum = 0;
static LPD3DXBUFFER g_pMaterials = NULL;

static D3DMATERIAL9*		pMeshMat;	// �}�e���A�����
static LPDIRECT3DTEXTURE9*	pMeshTex;	// ���b�V���̃e�N�X�`��

static D3DXMATRIX g_mtxWorld;
static D3DXMATRIX g_mtxWorld2;
static D3DXMATRIX k_mtxWorld;


static LPD3DXMESH g_pMesh2 = NULL;
static DWORD g_nMaterialNum2 = 0;
static LPD3DXBUFFER g_pMaterials2 = NULL;

static D3DMATERIAL9*		pMeshMat2;	// �}�e���A�����
static LPDIRECT3DTEXTURE9*	pMeshTex2;

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

}PLAYER;

PLAYER player;

void InitModel(void)
{
	player. spin_flag=false;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;

	hr = D3DXLoadMeshFromX("hikouki2.x",
						   D3DXMESH_MANAGED,
						   pDevice,
						   &pAdjacency,
						   &g_pMaterials,NULL,
						   &g_nMaterialNum,
						   &g_pMesh);

	if ( FAILED (hr) )
	{// ���G���[�`�F�b�N��΂�遚
		MessageBox(NULL, "���f�����ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

	hr = D3DXLoadMeshFromX("hikouki.x",
						   D3DXMESH_MANAGED,
						   pDevice,
						   &pAdjacency,
						   &g_pMaterials2,NULL,
						   &g_nMaterialNum2,
						   &g_pMesh2);

	if ( FAILED (hr) )
	{// ���G���[�`�F�b�N��΂�遚
		MessageBox(NULL, "���f�����ǂݍ��߂܂���ł���", "�G���[���b�Z�[�W", MB_OK);
	}

		hr = g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT|
							 D3DXMESHOPT_ATTRSORT|
							 D3DXMESHOPT_VERTEXCACHE,
							 (DWORD*)pAdjacency->GetBufferPointer(),
							 NULL,
							 NULL,
							 NULL);

		if ( FAILED (hr) )
		{// ���G���[�`�F�b�N��΂�遚
//			MessageBox(NULL, "���b�V��", "�G���[���b�Z�[�W", MB_OK);
		}

		hr = g_pMesh2->OptimizeInplace(D3DXMESHOPT_COMPACT|
							 D3DXMESHOPT_ATTRSORT|
							 D3DXMESHOPT_VERTEXCACHE,
							 (DWORD*)pAdjacency->GetBufferPointer(),
							 NULL,
							 NULL,
							 NULL);

		if ( FAILED (hr) )
		{// ���G���[�`�F�b�N��΂�遚
	//		MessageBox(NULL, "���b�V��", "�G���[���b�Z�[�W", MB_OK);
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

//-----------------------------------------------------------------------------//

	D3DXMATERIAL* d3Mat= (D3DXMATERIAL*)g_pMaterials -> GetBufferPointer();

	pMeshMat = new D3DMATERIAL9[ g_nMaterialNum ];		// ���b�V�������m��
	pMeshTex = new LPDIRECT3DTEXTURE9[ g_nMaterialNum ];// �e�N�X�`�����m��

	for(int  i = 0; i < g_nMaterialNum; i++ )
	{
		pMeshMat[i] = d3Mat[i].MatD3D;			// �}�e���A�����Z�b�g
		pMeshTex[i] = NULL;	// �e�N�X�`��������
	
		if( d3Mat[i].pTextureFilename != NULL  )
		{
				// �e�N�X�`���ǂݍ���
				hr=D3DXCreateTextureFromFile(
								pDevice,
								d3Mat[i].pTextureFilename,
								&pMeshTex[i] );

			if ( FAILED (hr) )
			{// ���G���[�`�F�b�N��΂�遚
			//	MessageBox(NULL, "���b�V��", "�G���[���b�Z�[�W", MB_OK);
			}
		}
		
		
	}

//------------------------------------------------------------------------//



	D3DXMATERIAL* d3Mat2= (D3DXMATERIAL*)g_pMaterials2 -> GetBufferPointer();

	pMeshMat2 = new D3DMATERIAL9[ g_nMaterialNum2 ];		// ���b�V�������m��
	pMeshTex2 = new LPDIRECT3DTEXTURE9[ g_nMaterialNum2 ];// �e�N�X�`�����m��

	for(int  i = 0; i < g_nMaterialNum2; i++ )
	{
		pMeshMat2[i] = d3Mat2[i].MatD3D;			// �}�e���A�����Z�b�g
		pMeshTex2[i] = NULL;	// �e�N�X�`��������
	
		if( d3Mat2[i].pTextureFilename != NULL  )
		{
				// �e�N�X�`���ǂݍ���
				hr=D3DXCreateTextureFromFile(
								pDevice,
								d3Mat2[i].pTextureFilename,
								&pMeshTex2[i] );

			if ( FAILED (hr) )
			{// ���G���[�`�F�b�N��΂�遚
			//	MessageBox(NULL, "���b�V��", "�G���[���b�Z�[�W", MB_OK);
			}
		}
		
		
	}
	player.pos=D3DXVECTOR3(0.0f,1.0f,0.0f);
	player.front=player.front_now=D3DXVECTOR3(0.0f,0.0f,1.0f);
	player.up=player.up_now=D3DXVECTOR3(0.0f,1.0f,0.0f);

	player.spin=0.0f;
	D3DXMatrixIdentity(&g_mtxWorld);
//	g_pMaterials->Release();

}
void UninitModel(void)
{
	
	DWORD	i;

	// �e�N�X�`���J��
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

	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //���C�e�B���O�I��

	
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

void UpdateModel(void)
{


	count++;

	if(count>20)
	{
		CreateBuullet(Change_flag,player.pos.x-0.15);
		CreateBuullet(Change_flag,player.pos.x+0.15);
		count=0;
	}
	player.pos_before=player.pos;

	player.spin_flag=false;
	player.spin_flag2=false;

	player.pos.z+=0.0;


	if(GetKeyboardTrigger(DIK_SPACE))
	{
		

		if(CreateChage(player.pos,Change_flag))
		{
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

//---------------�㉺��]----------------//
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

	//�E
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

//------------------���E��]-------------------------------------//

//�E
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

//��	
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


	
	

	

	//�T�C�Y����
	D3DXMatrixScaling (&g_mtxWorld,0.3,0.3,0.3);

	//��������
	D3DXMatrixRotationY( &k_mtxWorld,-1.57);
	g_mtxWorld*=k_mtxWorld;

	//���E��]
	D3DXMatrixRotationZ( &k_mtxWorld,player.spin);

	g_mtxWorld*=k_mtxWorld;

	//�㉺��]
	D3DXMatrixRotationX( &k_mtxWorld,player.spin2);

	g_mtxWorld*=k_mtxWorld;

	D3DXMatrixTranslation( &k_mtxWorld,player.pos.x,player.pos.y,player.pos.z);

	g_mtxWorld*=k_mtxWorld;
	
}

D3DXVECTOR3* GetPlayerPos(void)
{
	return &player.pos;
}

D3DXVECTOR3* GetPlayerfront(void)
{
	return &player.front_now;
}