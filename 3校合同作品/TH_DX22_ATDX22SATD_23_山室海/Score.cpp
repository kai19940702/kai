//==========================================
// スコア
//==========================================
#include "Polygon.h"
#include "main.h"
//#include <math.h>
#include <d3dx9.h>
#include "number.h"
#include "score.h"
#include "string.h"

#define DIGIT	(10)

static int score = 0;		// スコア

//=================================================================================================
//	スコア初期化処理関数
//
//
//=================================================================================================
void InitScore(void)
{
	score = 0;
}

//=================================================================================================
//	スコア加算処理関数
//
//
//=================================================================================================
void AddScore(void)
{
	score += 150;
}

//=================================================================================================
//	スコア描画処理関数
//
//
//=================================================================================================
void DrawScore(float x, float y, bool bZero, bool bLeft)
{
	SetPolygonTexture(11);
	SetPolygonScale(10.0f,1.0f,1.0f,1.0f);
	PolygonDraw(0,0,0,0,100,46,true);

	int subscore = score;
	int onedig = 0;
	for(int counter = 0; counter < DIGIT; counter++)
	{
		float scoreX = x + ((NUMBER_WIDTH / 2) * (DIGIT - (counter + 1)));
		float scoreY = y;

		onedig = subscore % 10;		// 点数を10で割り、余りを入れる		例 subscore 16728 onedig 8
		subscore -= onedig;			// 点数から引き算する				例 16720
		subscore /= 10;				// 点数を１０で割る					例 1672
		if(onedig == 0)
		{
			onedig = 10;
		}
		DrawNumber(onedig, scoreX, scoreY);

	}
}

void ChangeScore(int num)
{
	score=num;
}


int NowScore(void)
{
	return score;
}