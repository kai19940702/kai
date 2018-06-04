#ifndef _SCENESKY_H_
#define _SCENESKY_H_



#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])


#include "Main.h"

class CSky: public Scene
{
private:
	LPD3DXMESH g_pMesh;
	DWORD g_nMaterialNum;
	LPD3DXBUFFER g_pMaterials;
	
	D3DXMATRIX g_mtxWorld;
	D3DXMATRIX g_mtxWorld2;
	
	D3DMATERIAL9*		pMeshMat;	// �}�e���A�����
	LPDIRECT3DTEXTURE9*	pMeshTex;	// ���b�V���̃e�N�X�`��

public:
	CSky(int Priority);
	~CSky();
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CSky* Create(); 

};






#endif