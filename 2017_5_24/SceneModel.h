#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_



#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])


#include "Main.h"

class Model: public Scene
{
private:
	LPD3DXMESH g_pMesh;
	DWORD g_nMaterialNum;
	LPD3DXBUFFER g_pMaterials;
	
	D3DXMATRIX g_mtxWorld;
	D3DXMATRIX g_mtxWorld2;
	
	D3DMATERIAL9*		pMeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ

public:
	Model(int Priority);
	~Model();
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static Model* Create(); 

};






#endif