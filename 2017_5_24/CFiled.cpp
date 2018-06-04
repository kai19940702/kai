#include "CFiled.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Main.h"
#include "Renderer.h"
#include <time.h>
#include <random>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "CPlayer.h"



int  SIZE_Z =0;
int  SIZE_X =0;
int SIZE_PRIMITIVE =1;

int  SEPARATE_Z = 0;
int  SEPARATE_X = 0;
int  POS_NUM =0;
int  INDEX_NUM =0;    




	
// 配列数える

static LPDIRECT3DTEXTURE9 g_pTextures[1]; 



D3DXVECTOR3 Pos[100*100];

CFiled::CFiled(int Priority):Scene(Priority)
{
	 f_pVertexBuffer=NULL;
	 f_pIndexBuffer =NULL;
}
CFiled::~CFiled()
{

}

void CFiled::Init(int size_x , int size_Z ,int quads_size)
{
	int i=0;

	 srand((unsigned)time(NULL));

	HRESULT hr;
	SIZE_Z=size_Z;
	SIZE_X=size_x;
	SEPARATE_Z = (size_Z/quads_size);
    SEPARATE_X = (size_x/quads_size);

	POS_NUM = ((SEPARATE_Z+1)*(SEPARATE_X+1));
	INDEX_NUM = (POS_NUM + ((SEPARATE_Z-1)*(SEPARATE_X+1))+((SEPARATE_Z-1)*2));


	v = new VERTEX_3D[ POS_NUM ];		// メッシュ情報を確保
	Index_Filed = new WORD[ INDEX_NUM ];// テクスチャを確保

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();


	

		hr = D3DXCreateTextureFromFile(
			pDevice,															// デバイス
			"filed.jpg",												// ファイル名（実行ファイルと同じ場所だったらそのまま）
			&g_pTextures[i]);													// テクスチャ保持アドレスのアドレス

		if ( FAILED (hr) )
		{// ★エラーチェック絶対やる★
			MessageBox(NULL, "テクスチャが読み込めませんでした", "エラーメッセージ", MB_OK);
		}
	


		


	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *((SEPARATE_Z+1)*(SEPARATE_X+1)), //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								FVF_VERTEX_3D_FILED,//FVF指定（設定しなくてもよい）
								D3DPOOL_MANAGED, //システムに管理を任せる
								&f_pVertexBuffer, //管理者のポインタ
								NULL);
	if( FAILED(hr) )
	{
		MessageBox(NULL, "頂点バッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}


	 hr = pDevice->CreateIndexBuffer(sizeof(WORD) *(((SEPARATE_Z+1)*(SEPARATE_X+1))+((SEPARATE_Z-1)*(SEPARATE_X+1))+((SEPARATE_Z-1)*2)), //頂点の数分のメモリ
								D3DUSAGE_WRITEONLY, //使用用途　（今回は書き込み専用）
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED, //システムに管理を任せる
								&f_pIndexBuffer, //管理者のポインタ
								NULL);

	 if( FAILED (hr) )
	{
		MessageBox(NULL, "INDEXバッファが作成されませんでした", "エラーメッセージ", MB_OK);
	}
	 

	float pos_z=(float)(SEPARATE_Z+1)/2;
	float pos_x=-(float)((SEPARATE_X+1)/2);
	int index_x=0;
	int index_y=0;




	while(i!=POS_NUM)
	{
		v[i].pos.x=Pos[i].x=pos_x;
		v[i].pos.z=Pos[i].z=pos_z;
		v[i].pos.y=0;
		v[i].normal = D3DXVECTOR3(0.0,1.0,0.0);
		v[i].color = D3DCOLOR_RGBA(255,255,255,255);
		v[i].texcoord.x = index_x; 
		v[i].texcoord.y = index_y;

	

		pos_x++;
		index_x++;


		
		
		if(pos_x>(SEPARATE_X+1)/2)
		{

			index_y++;
			pos_z--;
			pos_x=-(float)((SEPARATE_X+1)/2);
			index_x=0;
		}
		i++;
	}

	pos_z=(float)(SEPARATE_Z+1)/2;
	pos_x=-(float)((SEPARATE_X+1)/2);
	index_x=0;
	index_y=0;


/*
	for(int j=0 ; j <3 ; j++)
	{

		for(int i=1 ; i<POS_NUM;i++)
		{
			if(rand()%60==0)
			{
				v[i].pos.y+=1.0;
				v[i+1].pos.y+0.5;
				v[i-1].pos.y+=0.5;
				v[i+2].pos.y+=0.25;
				v[i-2].pos.y+=0.25;

			}
		}
	}
*/	

	for(int z=1 ; z<101 ; z++)
	{
		for(int x=1 ; x<101 ;x++)
		{
			if(x%25==5)
			{
				v[z*101+x].pos.y =2;
				v[z*101+x+1].pos.y =v[z*101+x-1].pos.y =1.8;
				v[z*101+x+2].pos.y =v[z*101+x-2].pos.y =1.6;
				v[z*101+x+3].pos.y =v[z*101+x-3].pos.y =1.4;
				v[z*101+x+4].pos.y =v[z*101+x-4].pos.y =1.2;
				v[z*101+x+5].pos.y =v[z*101+x-5].pos.y =1.0;
				v[z*101+x+6].pos.y =v[z*101+x-6].pos.y =0.8;
				v[z*101+x+7].pos.y =v[z*101+x-7].pos.y =0.6;
				v[z*101+x+8].pos.y =v[z*101+x-8].pos.y =0.4;
				v[z*101+x+9].pos.y =v[z*101+x-9].pos.y =0.2;


			}
		}
	}

	for(int i=0 ; i<POS_NUM; i++)
	{
		Pos[i].y=v[i].pos.y;
	}

	D3DXVECTOR3 vx,nx,nz,n;

	for(int z=1 ; z< SIZE_Z ;z++)
	{
		for(int x = 1 ; x<SIZE_X ; x++)
		{
			vx=v[z*(SIZE_X+1)+x+1].pos-v[z*(SIZE_X+1)+x-1].pos;
			nx.x = -vx.y;
			nx.y = vx.x;
			nx.z =0.0f;

			vx=v[(z+1)*(SIZE_X+1)+x].pos-v[(z-1)*(SIZE_X+1)+x].pos;

			//nz.x = 0.0f;
			//nz.y = vx.z;
			//nz.z =-vx.y;

			nz.x = 0.0f;
			nz.y = vx.z;
			nz.z =-vx.y;

			n=nx+nz;
			D3DXVec3Normalize(&n,&n);
			v[z*(SIZE_X+1)+x].normal = n;
		}
	}
/*
		vx=vertex[z*5+x+1].Position-vertex[z*5+x-1].Position;
		nx.x = -vx.y;
		nx.y = vx.x;
		nx.z = 0.0f;



		n= nx+nz;
		D3DXVec3Normalize(&n,&n);
		Vertex[z*5+x].Normal = n;
		*/

	i=0;

	int count = (SEPARATE_X+1);
	int count2 = 0;


	while(i!=INDEX_NUM)
	{
		Index_Filed[ i ] = count;
		i++;
		Index_Filed[ i ] = count2;

		if( (count2+1) % (SEPARATE_X+1) ==  0 && i!=(INDEX_NUM-1) )
		{
			i++;
			Index_Filed[ i ] = count2;
			i++;
			Index_Filed[ i ] = (count+1);
		}

		count++;
		count2++;

		i++;
		
	}

	VERTEX_3D* pV;
	LPWORD f_pIndex;

	f_pVertexBuffer->Lock(0,0,(void**)&pV,D3DLOCK_DISCARD);

	memcpy(pV,v,sizeof(VERTEX_3D)*POS_NUM);
	f_pVertexBuffer->Unlock();


	f_pIndexBuffer->Lock(0,0,(void**)&f_pIndex,D3DLOCK_DISCARD);
	memcpy(f_pIndex,Index_Filed,sizeof(WORD)*INDEX_NUM);
	f_pIndexBuffer->Unlock();

}
void CFiled::Uninit(void)
{
	if(f_pVertexBuffer)
	{
		f_pVertexBuffer->Release();
		f_pVertexBuffer = NULL;

	}

	if(f_pIndexBuffer)
	{
		f_pIndexBuffer->Release();
		f_pIndexBuffer = NULL;

	}

}
void CFiled::Update(void)
{
	D3DXMatrixIdentity( &g_mtxWorld);

	D3DXVECTOR3 p0,p,v0p,v1p,v2p,c0,c1,c2,v01,v12,v20,n;
	float c0_s,c1_s,c2_s,pos_y;


	p = CPlayer::GetPlayerPos();

	for(int z=0 ; z< SIZE_Z ; z++)
	{
		for(int x=0; x< SIZE_X ;x++)
		{
		
			v0p= p-Pos[(z+1)*(SIZE_X+1)+x];//p0
			v1p= p-Pos[z*(SIZE_X+1)+x]; //p1
			v2p= p-Pos[z*(SIZE_X+1)+(x+1)];//p2
			v01= Pos[z*(SIZE_X+1)+x]-Pos[(z+1)*(SIZE_X+1)+x];
			v12 =Pos[z*(SIZE_X+1)+(x+1)]-Pos[z*(SIZE_X+1)+x];
			v20 =Pos[(z+1)*(SIZE_X+1)+x]-Pos[z*(SIZE_X+1)+(x+1)];
			c0_s=v01.x*v0p.z-v01.z*v0p.x;
			c1_s=v12.x*v1p.z-v12.z*v1p.x;
			c2_s=v20.x*v2p.z-v20.z*v2p.x;


			if(c0_s<=0.0f&&c1_s<=0.0f&&c2_s<=0.0f)
			{
				D3DXVec3Cross(&n,&v01,&v12);
				p0 = Pos[(z+1)*(SIZE_X+1)+x];
				pos_y = p0.y-(((n.x*(p.x-p0.x)+n.z*(p.z-p0.z))/n.y));
				CPlayer::SetPlayer_y(pos_y+1);


			}
		}
	}



	
	for(int z=1 ; z< SIZE_Z+1 ; z++)
	{
		for(int x=1; x< SIZE_X+1 ;x++)
		{
		
			v0p= p-Pos[z*(SIZE_X+1)+x];//p0
			v1p= p-Pos[(z-1)*(SIZE_X+1)+x]; //p1
			v2p= p-Pos[z*(SIZE_X+1)+(x-1)];//p2
			v01= Pos[(z-1)*(SIZE_X+1)+x]-Pos[z*(SIZE_X+1)+x];
			v12 =Pos[z*(SIZE_X+1)+(x-1)]-Pos[(z-1)*(SIZE_X+1)+x];
			v20 =Pos[z*(SIZE_X+1)+x]-Pos[z*(SIZE_X+1)+(x-1)];
			c0_s=v01.x*v0p.z-v01.z*v0p.x;
			c1_s=v12.x*v1p.z-v12.z*v1p.x;
			c2_s=v20.x*v2p.z-v20.z*v2p.x;


			if(c0_s<=0.0f&&c1_s<=0.0f&&c2_s<=0.0f)
			{
				D3DXVec3Cross(&n,&v01,&v12);
				p0 = Pos[z*(SIZE_X+1)+x];
				pos_y = p0.y-(((n.x*(p.x-p0.x)+n.z*(p.z-p0.z))/n.y));
				CPlayer::SetPlayer_y(pos_y+1);
			}
		}
	}
	
}
void CFiled::Draw(void)
{
	//マテリアル作成
	D3DMATERIAL9 mat;
	//ゼロ初期化
	ZeroMemory(&mat,sizeof(mat));

	//マテリアルカラー
	mat.Diffuse.r=1.0f;
	mat.Diffuse.g=1.0f;
	mat.Diffuse.b=1.0f;
	mat.Diffuse.a=1.0f;

	//環境光
	mat.Ambient.r=0.6f;
	mat.Ambient.g=0.6f;
	mat.Ambient.b=0.6f;
	mat.Ambient.a=1.0f;

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D_FILED);//今から色と頂点を送るという意味


	pDevice->SetMaterial(&mat);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);//法線正規化
	pDevice->SetRenderState(D3DRS_AMBIENT,D3DXCOLOR(0.3f,0.3f,0.3f,1.0f));

		pDevice->SetStreamSource(0,
		f_pVertexBuffer,
		0,
		sizeof(VERTEX_3D)); //１頂点分のサイズ

		pDevice->SetIndices(f_pIndexBuffer);

		pDevice->SetTexture(
		0,									// テクスチャステージ
		g_pTextures[0]);						// テクスチャ保持アドレス

		//pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

//---------描画処理------------------//




		//各種行列の設定(好きなタイミングで設定してOK)
		pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブタイプ
									0,					//ベース
									0,					//インデックス最小
									(SEPARATE_Z+1)*(SEPARATE_X+1),					//頂点数
									0,
									((SEPARATE_Z)*(SEPARATE_X)*2+((SEPARATE_Z-1)*4)));				//プリミティブ数


}

CFiled* CFiled::Create()
 {
	 CFiled* Scene = new CFiled(4);
	 Scene->Init(100,100,1);
	 return Scene;
 }


void CFiled::Up(D3DXVECTOR3* pos)
{
}

/*-----------------------------------------------------


for(int z = 1 ; z<4 ; z++)
{
	for(int x =1 ; x<4 ;x++)
	{
		vx=vertex[z*5+x+1].Position-vertex[z*5+x-1].Position;
		nx.x = -vx.y;
		nx.y = vx.x;
		nx.z = 0.0f;



		n= nx+nz;
		D3DXVec3Normalize(&n,&n);
		Vertex[z*5+x].Normal = n;

		:
		:
		:

	外積で求める

N = Vz * Vx(dot)

------------------------------------------------------*/
