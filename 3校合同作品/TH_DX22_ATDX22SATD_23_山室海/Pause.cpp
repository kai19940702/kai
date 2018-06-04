#include "Pause.h"
#include "Polygon.h"
#include "Input.h"

void InitPause(void)
{
}
void UninitPause(void)
{
}
bool UpdatePause(void)
{
	if(GetKeyboardTrigger(DIK_P))
	{
		return false;
	}
	return true;
}
bool UpdatePause2(void)
{
	if(GetKeyboardTrigger(DIK_P))
	{
		return true;
	}
	return false;
}
void DrawPause(void)
{
}
