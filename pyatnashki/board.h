#pragma once
#include "includes.h"
#include "cell.h"

class Board
{
private:
	vector<vector<Cell>> boardNums;
	int dimension;
	pair<int, int> freeCellCoords;
	vector<char> possibleMoves;
public:
	Board(int dimension);
	vector<vector<Cell>> getBoardNums();
	friend ostream& operator<<(ostream& out, Board& board);
	bool operator==(const Board& board);
	~Board();
	void updatePositionOfFreeCell();
	void updatePossibleMoves();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void makeRandomMove();
	void shuffle();
	bool isEndgame();
	void makeMove(char currentCh);
	void clearAndShow();
	void start();
};