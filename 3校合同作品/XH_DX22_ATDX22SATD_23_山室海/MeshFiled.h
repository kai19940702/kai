#ifndef _MESH_FILED_
#define _MESH_FILED_

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
#define FVF_VERTEX_3D_FILED (D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_TEX1|D3DFVF_NORMAL)	// RHW‚Í•ÏŠ·ƒtƒ‰ƒO‚È‚Ì‚Å”²‚­



typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_FILED;


void MeshfFiledFileInit(int size_x , int size_Z ,int quads_size);
void MeshfFiledUninit(void);
void MeshfFiledUpdate(void);
void MeshfFiledDraw(void);



#endif