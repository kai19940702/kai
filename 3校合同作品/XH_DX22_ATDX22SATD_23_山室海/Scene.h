

#ifndef _SCENE_H_
#define _SCENE_H_

// enum
typedef enum
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_MAX

}SCENE_ID;


void InitScene(void);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);
SCENE_ID ChangeScene(SCENE_ID nextScene);

#endif	// _SCENE_H_