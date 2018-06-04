#ifndef _MODEL_H_
#define _MODEL_H_

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])

#include <d3d9.h>
#include <d3dx9.h>

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE3;

void InitModel(void);
void UninitModel(void);
void DrawModel(void);
bool UpdateModel(void);
D3DXVECTOR3* GetPlayerPos(void);
D3DXVECTOR3* GetPlayerfront(void);
bool HitCircle2(float x0, float y0 , float z0 ,float r0, float x1, float y1, float z1 , float r1);

#endif