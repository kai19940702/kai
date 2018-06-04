
#ifndef _SCORE_H_
#define _SCORE_H_

#define LOCATESCOREX	(0.0f)
#define LOCATESCOREY	(8.0f)

void InitScore(void);
void AddScore(void);
void DrawScore(float x, float y, bool bZero, bool bLeft);// 桁数、ｘ、ｙ、0埋めするか、左詰めにするか
void ChangeScore(int num);
int NowScore(void);


#endif	// _SCORE_H_