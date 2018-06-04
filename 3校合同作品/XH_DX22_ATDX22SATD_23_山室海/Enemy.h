#ifndef _ENEMY_H_
#define _ENEMY_H_

#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])

#include <d3d9.h>
#include <d3dx9.h>

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_ENEMY;

void InitEnemy(void);
void UninitEnemy(void);
void DrawEnemy(void);
bool UpdateEnemy(void);
void CreateEnemy(bool type);
D3DXVECTOR3 GetEnemyPos(int index);
D3DXVECTOR3* GetPlayerfront(int index);
void DestroyEnemy(int index);
bool GetEnemyType(int index);
#endif