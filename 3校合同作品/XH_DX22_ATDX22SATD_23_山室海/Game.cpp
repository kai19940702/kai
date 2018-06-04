//=======================================
//	Gameä÷êî
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
//	ÉQÅ[ÉÄèâä˙âªèàóùä÷êî
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
//	ÉQÅ[ÉÄçXèIóπèàóùä÷êî
//
//
//=================================================================================================
void UninitGame(void)
{

}

//=================================================================================================
//	ÉQÅ[ÉÄçXêVèàóùä÷êî
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
//	ÉQÅ[ÉÄï`âÊèàóùä÷êî
//
//
//=================================================================================================
void DrawGame( void )
{
		//GridDraw();
		DrawModel();
		DrawEnemy();
		MeshfFiledDraw();
		
		Polygon3DTestDraw();//âe

		DrawBillBoard();
		DrawExplosion();
		DrawEffect();
		DrawScore( 0, 0, false, false);
		DrawChange();
}


