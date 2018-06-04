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
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			MineMap[i][j] = -2;
			GameBroad[i][j] = 0;
		}
	for (int i = 1; i <= BROAD_SIZE; i++)
		for (int j = 1; j <= BROAD_SIZE; j++)
			MineMap[i][j] = 0;

	srand(time(NULL));
	int count = MINE_NUM;
	while (count) {
		int n = rand() % (BROAD_SIZE*BROAD_SIZE);
		int x = (n / BROAD_SIZE) + 1, y = (n % BROAD_SIZE) + 1;
		if (MineMap[x][y] == 0) {
			MineMap[x][y] = -1;
			count--;
		}
	}
}

int Count(int x, int y) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
			if (!(i == x && j == y) && MineMap[i][j] == -1)
				count++;
	return count;
}

void CountMine() {
	for (int i = 1; i <= BROAD_SIZE; i++)
		for (int j = 1; j <= BROAD_SIZE; j++)
			if (MineMap[i][j] == 0)
				MineMap[i][j] = Count(i, j);
}

bool ShowBroad() {
	int count = 0;
	for (int i = 1; i <= BROAD_SIZE; i++) {
		for (int j = 1; j <= BROAD_SIZE; j++)
			if (GameBroad[i][j] == 0) {
				printf("# ");
				count++;
			}
			else if(MineMap[i][j] >= 0)
				printf("%d ",MineMap[i][j]);
			else 
				printf("X ");
		printf("\n");
	}
	if (count == MINE_NUM)return true;
	return false;
}

bool Step(int x,int y) {
	GameBroad[x][y] = 1;
	if (MineMap[x][y] == -1)return true;
	else if (MineMap[x][y] > 0)return false;
	else {
		if (x > 0 && MineMap[x - 1][y] >= 0 && GameBroad[x - 1][y] == 0)Step(x - 1, y);
		if (x < SIZE - 1 && MineMap[x + 1][y] >= 0 && GameBroad[x + 1][y] == 0)Step(x + 1, y);
		if (y > 0 && MineMap[x][y - 1] >= 0 && GameBroad[x][y - 1] == 0)Step(x, y - 1);
		if (y < SIZE - 1 && MineMap[x][y + 1] >= 0 && GameBroad[x][y + 1] == 0)Step(x, y + 1);
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
	bool gameover = false;
	int X, Y;
	while (!gameover) {
		if (ShowBroad())break;
		printf(">> 請依序輸入座標(X,Y)範圍為 1 ~ %d:  ", BROAD_SIZE);
		scanf_s("%d %d", &X, &Y);
		if( X <= 0 || X > BROAD_SIZE || Y <= 0 || Y > BROAD_SIZE)
			printf("*****輸入錯誤，請重新輸入*****\n");
		else {
			gameover = Step(X, Y);
		}
	}
	if (gameover) {
		ShowBroad();
		printf("\t\tLOSE...");
	}
	else {
		printf("\t\tWIN~~~");
	}
	while (true);
    return 0;
}

