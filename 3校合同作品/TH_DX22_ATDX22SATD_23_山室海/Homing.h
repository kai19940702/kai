#ifndef _HOMING_H_
#define _HOMING_H_

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_HOMING (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHWは変換フラグなので抜く

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_HOMING;


void InitHoming(void);
void UninitHoming(void);
void UpdateHoming(void);
void DrawHoming(void);
void  CreateHoming(bool type);
bool HitCircle3(float x0, float y0 , float z0 ,float r0, float x1, float y1, float z1 , float r1);
void AddMeter(void);

#endif _HOMING_H_