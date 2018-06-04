#include "Main.h"
#include "Scene3D.h"
#include "Scene2D.h"
#include "Renderer.h"



// �z�񐔂���


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
			pDevice,															// �f�o�C�X
			"horoCube.png",												// �t�@�C�����i���s�t�@�C���Ɠ����ꏊ�������炻�̂܂܁j
			&g_pTextures3D[i]);													// �e�N�X�`���ێ��A�h���X�̃A�h���X


	}

	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *4, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								FVF_VERTEX_3D,//FVF�w��i�ݒ肵�Ȃ��Ă��悢�j
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&g_pVertexBuffer, //�Ǘ��҂̃|�C���^
								NULL);


	hr = pDevice->CreateIndexBuffer(sizeof(WORD) *6, //���_�̐����̃�����
								D3DUSAGE_WRITEONLY, //�g�p�p�r�@�i����͏������ݐ�p�j
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //�V�X�e���ɊǗ���C����
								&g_pIndexBuffer, //�Ǘ��҂̃|�C���^
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
		{// �e�N�X�`���ێ��̊J��
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


	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE ); //���C�e�B���O�I��

	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);//������F�ƒ��_�𑗂�Ƃ����Ӗ�


		pDevice->SetStreamSource(0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_3D)); //�P���_���̃T�C�Y

		pDevice->SetIndices(g_pIndexBuffer);

		pDevice->SetTexture(
		0,									// �e�N�X�`���X�e�[�W
		g_pTextures3D[0]);						// �e�N�X�`���ێ��A�h���X

//---------�`�揈��------------------//

		//�e��s��̐ݒ�(�D���ȃ^�C�~���O�Őݒ肵��OK)
		pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,//�v���~�e�B�u�^�C�v
									0,					//�x�[�X
									0,					//�C���f�b�N�X�ŏ�
									4,					//���_��
									0,
									2);				//�v���~�e�B�u��

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
			if(�Փ˔���)
			{

			}
		}
	}
}
*/