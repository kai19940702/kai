#ifndef _CHANGE_H_
#define _CHANGE_H_

#include <d3d9.h>
#include <d3dx9.h>

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_CHANGE (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_CHANGE;

void InitChange (void);
void UninitChange(void);
void UpdateChange(void);
void DrawChange(void);
bool CreateChage(D3DXVECTOR3 Pos, bool type);
void CreateVertex_ch(void);



#endif