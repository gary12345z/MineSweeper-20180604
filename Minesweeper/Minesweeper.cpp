// Minesweeper.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

#define BROAD_SIZE 8
#define MINE_NUM 10
#define SIZE BROAD_SIZE +2

int MineMap[SIZE][SIZE], GameBroad[SIZE][SIZE];

void SetMine() {
	//Sec1
	int i,j;//$t0 $t1
	i = 0;
	do {//Loop1
		j = 0;
		do {//Loop2
			MineMap[i][j] = -2;
			GameBroad[i][j] = 0;
			j++;
		} while (j != SIZE);
		i++;
	} while (i != SIZE);

	
	//Sec2
	i = 1;
	do {//Loop3
		j = 1;
		do {//Loop4
			MineMap[i][j] = 0;
			j++;
		} while (j <= BROAD_SIZE);
		i++;
	} while (i <= BROAD_SIZE);

	//Sec3
	srand(15);
	int count = MINE_NUM;//$t0
	do {//Loop5
		int n = rand() % (BROAD_SIZE*BROAD_SIZE);
		int x = (n / BROAD_SIZE) + 1, y = (n % BROAD_SIZE) + 1;
		if (MineMap[x][y] == 0) {//IfNot1
			MineMap[x][y] = -1;
			count--;
		}
	}while (count);
}

int Count(int x, int y) {//$a0 $a1
	//$sp[0]=$t0 ~ $sp[8]=$t2
	int i, j, count;//$t0 $t1 $t2
	count = 0;
	i = x-1;
	do {//Loop8
		j = y-1;
		do {//Loop9
			if (MineMap[i][j] == -1)//IfNot3
				count++;
			j++;
		} while (j <= y + 1);
		i++;
	} while (i <= x + 1);
	return count;
}

void CountMine() {
	int i, j;//$t0 $t1
	i = 1;
	do {//Loop6
		j = 1;
		do {//Loop7
			if (MineMap[i][j] == 0)//IfNot2
				MineMap[i][j] = Count(i, j);
			j++;
		} while (j <= BROAD_SIZE);
		i++;
	} while (i <= BROAD_SIZE);
}

bool ShowBroad() {
	//$sp[0]=$t0 ~ $sp[8]=$t2
	int i, j, count;//$t0 $t1 $t2
	count = 0;
	i = 1;
	do {//Loop10
		j = 1;
		do {//Loop11
			if (GameBroad[i][j] == 0) {//IfNot4
				printf("# ");
				count++;
			}
			else if (MineMap[i][j] >= 0)//IfNot5
				printf("%d ", MineMap[i][j]);
			else//IfNot6
				printf("X ");
			j++;
		} while (j <= BROAD_SIZE);
		printf("\n");
		i++;
	} while (i <= BROAD_SIZE);

	if (count == MINE_NUM)return true;//IfNot7
	return false;
}

bool Step(int x,int y) {//$a0 $a1
	GameBroad[x][y] = 1;
	if (MineMap[x][y] == -1)return true;//NotMine
	else if (MineMap[x][y] != 0)return false;//MineMapZero
	else {
		int i, j;//$t2 $t3
		i = x - 1;
		do {//Loop12
			j = y - 1;
			do {//Loop13
				if (MineMap[i][j] >= 0 && GameBroad[i][j] == 0)//NotStep
					Step(i, j);
				j++;
			} while (j <= y + 1);
			i++;
		} while (i <= x + 1);
	}
	return false;
}

int main()
{
	SetMine();
	CountMine();
	for (int i = 1; i <= BROAD_SIZE; i++) {
		for (int j = 1; j <= BROAD_SIZE; j++)
			printf("%d\t", MineMap[i][j]);
		printf("\n");
	}

	bool gameover = false;//$t0
	int X, Y;//$t1 $t2

	do{//MainLoop
		if (ShowBroad())break;//EndGame
		printf(">> 請依序輸入座標(X,Y)範圍為 1 ~ 8:  ");
		scanf_s("%d %d", &X, &Y);
		if( X <= 0 || X > BROAD_SIZE || Y <= 0 || Y > BROAD_SIZE)//InputCorrect
			printf("*****輸入錯誤，請重新輸入*****\n");
		else {
			gameover = Step(X, Y);
		}//ExitIf
	} while (!gameover);

	if (gameover) {//NotLose
		ShowBroad();
		printf("\t\tLOSE...");
	}
	else {
		printf("\t\tWIN~~~");
	}
	while (true);
	//Exit
    return 0;
}

