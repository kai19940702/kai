#ifndef _MESH_FILED_
#define _MESH_FILED_



#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_FILED (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1|D3DFVF_NORMAL)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­

#include "Main.h"
#include "Scene.h"

class CFiled : public Scene
{
private:

	LPDIRECT3DVERTEXBUFFER9 f_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 f_pIndexBuffer;
	
	float* y;
	VERTEX_3D* v;
	WORD* Index_Filed;
	
	D3DXMATRIX g_mtxWorld;

public:
	CFiled(int Priority);
	~CFiled();
	void Init(int size_x , int size_Z ,int quads_size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFiled* Create();
	static void Up(D3DXVECTOR3* pos);

};








#endif