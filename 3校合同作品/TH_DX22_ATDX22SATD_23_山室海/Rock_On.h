#ifndef _ROCKON_H_
#define _ROCKON_H_


#include <d3d9.h>
#include <d3dx9.h>

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_ROCKON (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_ROCKON;

void InitRock_On(void);
void UninitRock_On(void);
void UpdateRock_On(void);
void DrawRock_On(void);
void CreateRock_On(void);
void Destroty_Rock_On (int index);

#endif