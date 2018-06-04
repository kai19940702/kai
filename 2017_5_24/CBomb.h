#ifndef _BOMB_H_
#define _BOMB_H_

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define BOMB_MAX (10)

#include "Main.h"
#include "Scene.h"

class CBomb : public Scene
{
private:

	LPD3DXMESH g_pMesh;
	DWORD g_nMaterialNum;
	LPD3DXBUFFER g_pMaterials;

	D3DMATERIAL9*		pMeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ


public:
	CBomb(int Priority);
	~CBomb();
	void Init(void);
	void Uninit(void);
	void Draw(void);
	void Update(void);
	static CBomb* Create();
	static void CBomb::CreateBomb();
};
#endif