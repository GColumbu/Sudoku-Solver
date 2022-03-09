#include "game.h"
void showBoard(int board[9][9]) {
	for (int i = 0; i<9; i++) {
		for (int j = 0; j<9; j++) {
			std::cout << board[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}
bool breaksRow(int board[9][9], int row, int val) {
	for (int i = 0; i<9; i++) {
		if (val == board[row][i]) {
			return true;
		}
	}
	return false;
}
bool breaksCol(int board[9][9], int col, int val) {
	for (int i = 0; i<9; i++) {
		if (val == board[i][col]) {
			return true;
		}
	}
	return false;
}
bool breaksSub(int board[9][9], int row, int col, int val) {
	int aux[3][3] = {
		{ 0, 1, 2 },
		{ 3, 4, 5 },
		{ 6, 7, 8 }
	};
	int subRow, subCol;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			if (aux[i][j] == row) {
				subRow = i;
			}
			if (aux[i][j] == col) {
				subCol = i;
			}
		}
	}
	for (int i = aux[subRow][0]; i <= aux[subRow][2]; i++) {
		for (int j = aux[subCol][0]; j <= aux[subCol][2]; j++) {
			if (val == board[i][j]) {
				return true;
			}
		}
	}
	return false;
}
void recursive(int board[9][9], int solvedBoard[9][9], int x, int y) {
	if (x == 8 && y == 9) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				solvedBoard[i][j] = board[i][j];
			}
		}
		return;
	}
	if (y == 9) {
		x++;
		y = 0;
	}
	if (board[x][y] == 0) {
		for (int i = 1; i <= 9; i++) {
			if (!breaksRow(board, x, i) && !breaksCol(board, y, i) && !breaksSub(board, x, y, i)) {
				board[x][y] = i;
				y++;
				recursive(board, solvedBoard, x, y);
				y--;
				board[x][y] = 0;
			}
		}
		if (board[x][y] == 0) {
			return;
		}
	}
	y++;
	recursive(board, solvedBoard, x, y);
	y--;
	return;
}

int main(){
	int board[9][9] = {
		{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
		{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
		{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
		{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
		{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
		{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
		{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
		{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
		{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }
	};
	int solvedBoard[9][9];
	int x = 0, y = 0;
	bool solutionStart = false;
	recursive(board, solvedBoard, x, y);
	game myGame(board);
	myGame.initBoard();
	//game loop
	while (myGame.isRunning()) {
		//update
		myGame.update(solvedBoard);
		//render
		myGame.render();
	}
	return 0;
}