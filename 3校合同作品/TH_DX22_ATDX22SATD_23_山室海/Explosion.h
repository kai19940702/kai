#ifndef _EXPLOSION_H_
#define  _EXPLOSION_H_

#include <d3d9.h>
#include <d3dx9.h>


#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_EXPLOSION (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_EXPLOSION;

void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void CreateExplosion( D3DXVECTOR3 Pos);
void CreateVertex_ex(void);



#endif _EXPLOSION_H_