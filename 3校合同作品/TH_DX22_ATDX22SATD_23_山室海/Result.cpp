//=======================================
//	Result関数
//=======================================
#include "Result.h"
#include "Scene.h"
#include "input.h"
#include "Polygon.h"
#include "Score.h"




//=================================================================================================
//	結果初期化処理関数
//
//
//=================================================================================================
void InitResult(void)
{

}

//=================================================================================================
//	結果終了処理関数
//
//
//=================================================================================================
void UninitResult(void)
{

}

//=================================================================================================
//	結果更新処理関数
//
//
//=================================================================================================
void UpdateResult(void)
{


	 if(GetKeyboardTrigger(DIK_SPACE))
	{
 		ChangeScene(SCENE_TITLE);
	}


}

//=================================================================================================
//	結果描画処理関数
//
//わかるように一つはる
//=================================================================================================
void DrawResult(void)
{
	SetPolygonTexture(11);
	SetPolygonScale(20.0f,20.0f,1.0f,1.0f);
	PolygonDraw(0,0,0,0,100,100,true);


	SetPolygonTexture(5);
	SetPolygonScale(1.5f,1.5f,1.0f,1.0f);
	PolygonDraw(100,200,0,0,284,76,true);

	DrawScore( 250, 400, false, false);
}