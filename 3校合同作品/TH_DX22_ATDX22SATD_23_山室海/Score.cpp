//==========================================
// �X�R�A
//==========================================
#include "Polygon.h"
#include "main.h"
//#include <math.h>
#include <d3dx9.h>
#include "number.h"
#include "score.h"
#include "string.h"

#define DIGIT	(10)

static int score = 0;		// �X�R�A

//=================================================================================================
//	�X�R�A�����������֐�
//
//
//=================================================================================================
void InitScore(void)
{
	score = 0;
}

//=================================================================================================
//	�X�R�A���Z�����֐�
//
//
//=================================================================================================
void AddScore(void)
{
	score += 150;
}

//=================================================================================================
//	�X�R�A�`�揈���֐�
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

		onedig = subscore % 10;		// �_����10�Ŋ���A�]�������		�� subscore 16728 onedig 8
		subscore -= onedig;			// �_����������Z����				�� 16720
		subscore /= 10;				// �_�����P�O�Ŋ���					�� 1672
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