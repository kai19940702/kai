
#ifndef _NUMBER_H_
#define _NUMBER_H_

#define NUMBER_WIDTH		(54.0f)
#define NUMBER_HEIGHT		(92.5f)

void InitNumber(void);
void UninitNumber(void);
void UpdateNumber(void);
void DrawNumber(int n, float x, float y);

void CreateNumber(float x, float y);

#endif	//_NUMBER_H_