#ifndef _CLIGHT_H_
#define _CLIGHT_H_

#include "Main.h"

class CLight
{
private:
	D3DLIGHT9 light;
public:
	CLight();
	~CLight();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


#endif