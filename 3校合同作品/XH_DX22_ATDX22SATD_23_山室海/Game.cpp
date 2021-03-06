//=======================================
//	Game関数
//=======================================
#include "main.h"
#include "Game.h"
#include "Polygon.h"
#include "Scene.h"
#include "Input.h"
#include<math.h>
#include "Polygon3DTset.h"
#include "Camera.h"
#include "grid.h"
#include "Input.h"
#include "light.h"
#include "model.h"
#include "MeshFiled.h"
#include "BillBoard.h"
#include "shadow.h"
#include "Explosion.h"
#include "Scene.h"
#include "Enemy.h"
#include "Effect.h"
#include "Score.h"
#include "Change.h"



static bool fin_flag=false;


//=================================================================================================
//	ゲーム初期化処理関数
//
//
//=================================================================================================
void InitGame(void)
{
	InitScore();
	InitChange();
	InitEnemy();
	InitBillBoard();
	InitExplosion();
	
}

//=================================================================================================
//	ゲーム更終了処理関数
//
//
//=================================================================================================
void UninitGame(void)
{

}

//=================================================================================================
//	ゲーム更新処理関数
//
//
//=================================================================================================
void UpdateGame( void )
{

	CameraUpdate();
	PolygonUpdate();
	UpdateModel();
	fin_flag=UpdateEnemy();
	Polygon3DTestUpdate();
	GridUpdate();
	UpdateLight();
	UpdateBillBoard();
	MeshfFiledUpdate();
	UpdateExplosion();
	UpdateShadow();
	UpdateEffect();
	UpdateChange();

	if(fin_flag)
	{
		ChangeScene(SCENE_RESULT);
	}
}

//=================================================================================================
//	ゲーム描画処理関数
//
//
//=================================================================================================
void DrawGame( void )
{
		//GridDraw();
		DrawModel();
		DrawEnemy();
		MeshfFiledDraw();
		
		Polygon3DTestDraw();//影

		DrawBillBoard();
		DrawExplosion();
		DrawEffect();
		DrawScore( 0, 0, false, false);
		DrawChange();
}


