#ifndef _EFFECT_H_
#define _EFFECT_H_


#define EFFECT_MAX (4000)

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_EFFECT (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1)	// RHWは変換フラグなので抜く

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_EFFECT;

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void CreatEffect(float x, float y,float z,int nLife, bool type);		// 速度種類
void CreateVertex_ef(void);





#endif