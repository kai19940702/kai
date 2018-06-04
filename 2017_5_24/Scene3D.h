#ifndef _SCENE_3D_
#define _SCENE_3D_

#include "Main.h"
#include "Scene.h"


#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHWは変換フラグなので抜く




//*************************************************************************************************************************
// 構造体
//*************************************************************************************************************************





class Scene3D : public Scene
{
private:
	LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer ;
	D3DXMATRIX g_mtxWorld;



typedef struct 
{// 頂点の構造体
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR color;			// 色
	D3DXVECTOR2 texcoord;	// テクスチャ座標
}VERTEX_3D;

VERTEX_3D v[4];

WORD index[6];

LPDIRECT3DTEXTURE9 g_pTextures3D[1]; 



public:
	Scene3D(int Priority);
	~Scene3D();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static Scene3D* Create();

};





#endif _SCENE_3D_