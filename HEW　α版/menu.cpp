#include"main.h"

void menu(void)
{
	extern int stage;

	int key;
	int i;
	bool flag=0;

	COLOR(CORAL);
	LOCATE(35,10);
	printf("ステージ１");
	COLOR(WHITE);
	LOCATE(35,14);
	printf("ステージ２");

	LOCATE(28,2);
	printf(" ＳＴＡＧＥ　ＳＥＬＥＣＴ ");

	COLOR(BLUE);
	LOCATE(75,10);
	printf("■");
	COLOR(CORAL);
	LOCATE(73,10);
	printf("●");
	COLOR(BLUE);
	LOCATE(75,14);
	printf("■");
	COLOR(CORAL);
	LOCATE(73,14);
	printf("●");

	COLOR(WHITE);
	LOCATE(2,24);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");


	COLOR(BLUE);
	LOCATE(10,23);
	printf("■");
	COLOR(CORAL);
	LOCATE(10,22);
	printf("●");

	COLOR(WHITE);
	LOCATE(10,20);
	printf("↑↓で選択してエンターキーで決定！！");




		for(i=0;i<20;i+=2)
		{
			COLOR(BLUE);
			LOCATE(71-i,10);
			printf("●");
			COLOR(GRAY);
			LOCATE(73-i,10);
			printf("首");
			Sleep(20);
		}

	while(flag==0)
	{
		if(kbhit())
		{
			key=getch();

				switch(key)
				{
				case KEY_UP:
					{
						if(stage==1)
						{
							break;
						}
						COLOR(CORAL);
						LOCATE(35,10);
						printf("ステージ１");
						COLOR(WHITE);
						LOCATE(35,14);
						printf("ステージ２");
						stage=1;
						for(i=0;i<22;i+=2)
						{
							COLOR(CORAL);
							LOCATE(50+i,14);
							printf(" ●");
							COLOR(GRAY);
							LOCATE(53+i,14);
							printf("首");
							Sleep(20);
						}
						COLOR(BLUE);
						LOCATE(75,14);
						printf("■");
						COLOR(CORAL);
						LOCATE(71,14);
						printf("  ●");


						for(i=0;i<20;i+=2)
						{
							COLOR(CORAL);
							LOCATE(71-i,10);
							printf("●");
							COLOR(GRAY);
							LOCATE(73-i,10);
							printf("首");
							Sleep(20);
						}
						break;
					}
				case KEY_DOWN:
					{
						if(stage==2)
						{
							break;
						}
						COLOR(WHITE);
						LOCATE(35,10);
						printf("ステージ１");
						COLOR(CORAL);
						LOCATE(35,14);
						printf("ステージ２");
						stage=2;

						for(i=0;i<22;i+=2)
						{
							COLOR(CORAL);
							LOCATE(50+i,10);
							printf(" ●");
							COLOR(GRAY);
							LOCATE(53+i,10);
							printf("首");
							Sleep(20);
						}

						COLOR(BLUE);
						LOCATE(75,10);
						printf("■");
						COLOR(CORAL);
						LOCATE(71,10);
						printf("  ●");

						for(i=0;i<20;i+=2)
						{
							COLOR(CORAL);
							LOCATE(71-i,14);
							printf("●");
							COLOR(GRAY);
							LOCATE(73-i,14);
							printf("首");
							Sleep(20);
						}
						break;
					}
					case KEY_ENTER:
						{
							flag=1;
						}
				}
		}
	}

	CLS();

}