#include "Main.h"
#include "CPlayer.h"
#include "Renderer.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "CBomb.h"

D3DXVECTOR3 GetPlayerPos(void);

#define FilePass (texture\\)

D3DXVECTOR3 g_pos = D3DXVECTOR3(0,0.5,0);
D3DXVECTOR3 g_pos_before = D3DXVECTOR3(0,0,0);
D3DXVECTOR3 g_front = D3DXVECTOR3(0,0,1);
D3DXVECTOR3 g_rot = D3DXVECTOR3(0,0,0);
D3DXVECTOR3 g_scal = D3DXVECTOR3(1,1,1);
D3DXMATRIX  g_matrix;



CPlayer::CPlayer(int Priority):Scene(Priority)
{
	g_pMesh = NULL;
	g_nMaterialNum = 0;
	g_pMaterials = NULL;
	player.pos = D3DXVECTOR3(0,1,0);
	player.front_now = D3DXVECTOR3(0.f,0.f,-1.f);
}
CPlayer::~CPlayer()
{
}


void CPlayer::Init()
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;

	hr = D3DXLoadMeshFromX("robo.x",
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



		hr = g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT|
							 D3DXMESHOPT_ATTRSORT|
							 D3DXMESHOPT_VERTEXCACHE,
							 (DWORD*)pAdjacency->GetBufferPointer(),
							 NULL,
							 NULL,
							 NULL);

		if ( FAILED (hr) )
		{// ���G���[�`�F�b�N��΂�遚
			MessageBox(NULL, "���b�V��", "�G���[���b�Z�[�W", MB_OK);
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
				MessageBox(NULL, "���b�V��", "�G���[���b�Z�[�W", MB_OK);
			}
		}
		
		
	}
	D3DXMatrixRotationY(&g_matrix,180);
//	g_pMaterials->Release();

}
void CPlayer::Uninit()
{


	// �e�N�X�`���J��
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
void CPlayer::Draw()
{



	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();


	pDevice->SetTransform(D3DTS_WORLD,&g_matrix);

	pDevice->LightEnable(0,TRUE);

	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //���C�e�B���O�I��


	for(int i= 0 ; i < g_nMaterialNum ; i++)
	{
		pDevice->SetMaterial( &pMeshMat[i] );
		pDevice->SetTexture(0,pMeshTex[i]);
		g_pMesh->DrawSubset(i);
	}

}

void CPlayer::Update()
{
	D3DXMATRIX t_matrix,s_matrix,u_matrix;
	D3DXMatrixTranslation( &s_matrix , 0 , 0 , 0.0f );

	if(GetKeyboardTrigger(DIK_SPACE))
	{
		CBomb::CreateBomb();
	}

	if(GetKeyboardPress(DIK_DOWN))
	{
		D3DXMatrixTranslation( &s_matrix , 0 , 0 , 0.2f ); 
	}
	if(GetKeyboardPress(DIK_UP))
	{                                              
		D3DXMatrixTranslation( &s_matrix , 0 , 0 , -0.2f ); //  �ړ��}�g���N�X�̍쐬 

	}                                              
		if(GetKeyboardPress(DIK_RIGHT)) //  �E�L�[����                          
	{                                              
		g_rot.y += 0.1f;        //  Y�������ɂO�D�Q�������Z��] 
		D3DXMatrixRotationY(&u_matrix,0.1f);
		D3DXVec3TransformNormal(&g_front,&g_front,&u_matrix);	

	}                                              
	if(GetKeyboardPress(DIK_LEFT))  //  ���L�[����                          
	{                                              
		g_rot.y -= 0.1f;        //  Y�������ɂO�D�Q�������Z��] 
		D3DXMatrixRotationY(&u_matrix,-0.1f);
		D3DXVec3TransformNormal(&g_front,&g_front,&u_matrix);	
	}
	//  ���f����\�����邽�߂̃}�g���N�X�쐬                                         
	D3DXMatrixTranslation(&g_matrix , g_pos.x , g_pos.y ,g_pos.z);              //  �ړ��}�g���N�X�̍쐬     
	D3DXMatrixRotationYawPitchRoll(&t_matrix , g_rot.y+3.14 , g_rot.x , g_rot.z);    //  ��]�}�g���N�X�̍쐬
	
	//  �����ňړ��}�g���N�X�Ɖ�]�}�g���N�X�A�ړ��J�n�_�}�g���N�X����������@�����Ԃɒ���                                      
	g_matrix = s_matrix * t_matrix * g_matrix;                                                                                             
	D3DXMatrixScaling(&t_matrix , g_scal.x , g_scal.y ,g_scal.z);               //  �g��k���}�g���N�X�̍쐬   

	//  �����ňړ����g��k���}�g���N�X�Ɖ�]�}�g���N�X����������                                       

	g_matrix = t_matrix * g_matrix;                                            

	//  ���W�̍X�V                                              


	g_pos.x = g_matrix._41;                                            
	g_pos.y = g_matrix._42;                                            
	g_pos.z = g_matrix._43;


	D3DXVec3Normalize(&g_front,&g_front);
	

	

}

CPlayer* CPlayer::Create()
 {
	 CPlayer* Scene = new CPlayer(2);
	 Scene->Init();
	 return Scene;
 }
D3DXVECTOR3 CPlayer::GetPlayerPos()
{
	return g_pos;
}
D3DXVECTOR3 CPlayer::GetPlayerfront()
{
	return g_front;
}
void CPlayer::SetPlayer_y(float y)
{
	g_pos.y = y;
}
