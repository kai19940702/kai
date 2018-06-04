#ifndef _SCENE_
#define _SCENE_

#include "main.h"


//*************************************************************************************************************************
// 構造体
//*************************************************************************************************************************

enum SCENE_TYPE
{
	SCENE_TYPE_NONE,
	SCENE_TYPE_2D,
	SCENE_TYPE_3D
};





class Scene
{
protected:
	D3DXVECTOR3 m_Postion;
	D3DCOLOR g_PolygonColor;

	static Scene *m_Scene[10];
	SCENE_TYPE m_Type;


		typedef struct
	{// 頂点の構造体
		D3DXVECTOR3 pos;		// 座標
		D3DXVECTOR3 normal;		//法線
		D3DCOLOR color;			// 色
		D3DXVECTOR2 texcoord;	// テクスチャ座標
	}VERTEX_3D;


public:
	Scene(int Priority);
	virtual~Scene(){};
	virtual void Init(){};
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void Uninit()=0;
	static void UpdateAll();
	static void DrawAll();
	static void ReleaseAll();
	void SetPostion(D3DXVECTOR3 Pos){m_Postion=Pos;}
	void Relese();
	SCENE_TYPE GetType();
};





#endif _SCENE_