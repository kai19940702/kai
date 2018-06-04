#ifndef _SHADOW_H_
#define _SHADOW_H_

#define FVF_VERTEX_3D_SHADOW (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_SHADOW;

void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
void CreateShadow(void);

#endif