#ifndef _HAIKEI_H_
#define  _HAIKEI_H_

#include <d3d9.h>
#include <d3dx9.h>


#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_HAIKEI (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_HAIKEI;

void InitHaikei(void);
void UninitHaikei(void);
void UpdateHaikei(void);
void DrawHaikei(void);




#endif _HAIKEI_H_