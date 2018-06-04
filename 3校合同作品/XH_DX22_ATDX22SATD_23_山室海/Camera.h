//******************************************************************
//						[Camera.h]											
//			AuthorÅF	çÏê¨ì˙ÅF2017/10/31			
//******************************************************************

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>

void CameraInit(void);
void CameraUninit(void);
void CameraUpdate(void);
D3DXMATRIX* GetmtxView(void);
D3DXVECTOR3* Getg_at(void);
D3DXVECTOR3* Getg_eye(void);

#endif