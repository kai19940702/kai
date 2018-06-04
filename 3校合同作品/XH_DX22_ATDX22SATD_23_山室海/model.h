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
void UpdateModel(void);
D3DXVECTOR3* GetPlayerPos(void);
D3DXVECTOR3* GetPlayerfront(void);

#endif