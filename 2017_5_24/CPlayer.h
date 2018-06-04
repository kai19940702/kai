#ifndef _MODEL_H_
#define _MODEL_H_

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])

#include "Main.h"
#include "Scene.h"

class CPlayer : public Scene
{
private:
	int count;

	LPD3DXMESH g_pMesh;
	DWORD g_nMaterialNum;
	LPD3DXBUFFER g_pMaterials;

	D3DMATERIAL9*		pMeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	pMeshTex;	// メッシュのテクスチャ

	D3DXMATRIX g_mtxWorld;
	D3DXMATRIX g_mtxWorld2;



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

public:
	CPlayer(int Priority);
	~CPlayer();
	void Init(void);
	void Uninit(void);
	void Draw(void);
	void Update(void);
	static D3DXVECTOR3 GetPlayerPos(void);
	static D3DXVECTOR3 GetPlayerfront(void);
	static void SetPlayer_y(float y);
	static CPlayer* Create();
};
#endif