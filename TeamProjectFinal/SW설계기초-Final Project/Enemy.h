#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "BackGround.h"
#ifndef ENEMY_H
#define ENEMY_H

//적 우주선 및 총알
#define ENEMY 2
#define ENEMYDAMAGE 2
#define ENEMYBULLET 3

//적 우주선 위치 및 이동방향
int ENEMY_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int ENEMY_POS_Y = GAMEBOARD_ORIGIN_Y + 1;
int direction = 0;

//적 우주선 모델링
char EnemyModel[3][5] = { {' ','A','V','A',' '},{'<','O','O','O','>'},{' ','V','A','V',' '} };
char EnemyUniModel[3][5] = { {0,ENEMY,ENEMY,ENEMY,0},{ENEMY,ENEMY,ENEMY,ENEMY,ENEMY},{0,ENEMY,ENEMY,ENEMY,0} };

//적 유니보드 위치 갱신 함수
void EraseEnemy() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (EnemyUniModel[i][j] == ENEMY) UniBoard[ENEMY_POS_Y - GAMEBOARD_ORIGIN_Y + i][ENEMY_POS_X - GAMEBOARD_ORIGIN_X + j] = 0;
		}
	}
}
void InsertEnemy() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (EnemyUniModel[i][j] == ENEMY) UniBoard[ENEMY_POS_Y - GAMEBOARD_ORIGIN_Y + i][ENEMY_POS_X - GAMEBOARD_ORIGIN_X + j] = ENEMY;
		}
	}
}

//적 출력 및 삭제 함수
void HideEnemy() {
	COORD ptr = { ENEMY_POS_X,ENEMY_POS_Y };
	EraseEnemy();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SetCurrentCursorPos(ptr.X + j, ptr.Y + i);
			if (EnemyModel[i][j] != ' ') printf(" ");
		}
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
}
void ShowEnemy() {
	COORD ptr = { ENEMY_POS_X,ENEMY_POS_Y };
	InsertEnemy();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SetCurrentCursorPos(ptr.X + j, ptr.Y + i);
			if (EnemyModel[i][j] != ' ') printf("%c", EnemyModel[i][j]);
		}
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
}

int DetectCollision_Enemy(int x, int y) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (EnemyUniModel[i][j] == ENEMY) {
				if (UniBoard[y - GAMEBOARD_ORIGIN_Y + i][x - GAMEBOARD_ORIGIN_X + j] == 1) return 1;
			}
		}
	}
	return 0;
}

//적 위치 변환 함수
void shiftEnemyLeft() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X - 1, ENEMY_POS_Y)) { ENEMY_POS_X--; direction = 0; }
	else direction = 1;
	ShowEnemy();
}
void shiftEnemyRight() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X + 1, ENEMY_POS_Y)) { ENEMY_POS_X++; direction = 1; }
	else direction = 0;
	ShowEnemy();
}

//적 갱신 함수
void InvalidateEnemy() {
	if (direction) shiftEnemyRight();
	else shiftEnemyLeft();
}
#endif // !ENEMY_H