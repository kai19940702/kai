
#ifndef _SCORE_H_
#define _SCORE_H_

#define LOCATESCOREX	(0.0f)
#define LOCATESCOREY	(8.0f)

void InitScore(void);
void AddScore(void);
void DrawScore(float x, float y, bool bZero, bool bLeft);// �����A���A���A0���߂��邩�A���l�߂ɂ��邩
void ChangeScore(int num);
int NowScore(void);


#endif	// _SCORE_H_