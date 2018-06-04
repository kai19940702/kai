#ifndef BILLBOARD_H_
#define BILLBOARD_H_



#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_BILLBOARD (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_BILLBOARD;


void InitBillBoard(void);
void UninitBillBoard(void);
void UpdateBillBoard(void);
void DrawBillBoard(void);
void CreateVertex_b(void);
void CreateBuullet(bool type,float x);
/*
bool IsBullet(int index);
*/

#endif