#include "includes.h"
#include "board.h"
#include <conio.h>

#define COUNT_OF_SHUFFLES 100
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

Board::Board(int dimension)
{
	vector<vector<Cell>> boardNums;
	this->dimension = dimension;

	int counter = 1;
	for (int i = 0; i < dimension; i++)
	{
		vector<Cell> tempRow;

		for (int j = 0; j < dimension; j++)
		{
			Cell cell;
			if (counter == dimension * dimension)
			{
				cell.setNumber(" ");
			}
			else
			{
				cell.setNumber(to_string(counter));
			}

			tempRow.push_back(cell);
			counter++;
		}
		boardNums.push_back(tempRow);
	}
	this->boardNums = boardNums;
}
vector<vector<Cell>> Board::getBoardNums()
{
	return boardNums;
}
ostream& operator<<(ostream& out, Board& board)
{
	for (int i = 0; i < board.boardNums.size(); i++)
	{
		for (int j = 0; j < board.boardNums[i].size(); j++)
		{
			cout << board.boardNums[i][j].getNumber() << "\t";
		}
		cout << "\n";
	}

	return out;
}
bool Board::operator==(const Board& board)
{
	for (int i = 0; i < board.boardNums.size(); i++)
	{
		for (int j = 0; j < board.boardNums[i].size(); j++)
		{
			if (this->boardNums[i][j] != board.boardNums[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
Board::~Board(){}

void Board::updatePositionOfFreeCell()
{
	for (int i = 0; i < this->boardNums.size(); i++)
	{
		for (int j = 0; j < this->boardNums[i].size(); j++)
		{
			if (this->boardNums[i][j].isFree())
			{
				this->freeCellCoords.first = i;
				this->freeCellCoords.second = j;
				return;
			}
		}
	}
}
void Board::updatePossibleMoves()
{
	this->possibleMoves.clear();

	this->updatePositionOfFreeCell();
	int i = this->freeCellCoords.first;
	int j = this->freeCellCoords.second;

	if (i > 0)
	{
		possibleMoves.push_back(DOWN);
	}
	// why < does not work?
	if (i != dimension - 1)
	{
		possibleMoves.push_back(UP);
	}
	if (j > 0)
	{
		possibleMoves.push_back(RIGHT);
	}
	if (j != dimension - 1)
	{
		possibleMoves.push_back(LEFT);
	}
}

void Board::moveUp()
{
	Cell tempCell(this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second]);
	this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second] = this->boardNums[this->freeCellCoords.first + 1][this->freeCellCoords.second];
	this->boardNums[this->freeCellCoords.first + 1][this->freeCellCoords.second] = tempCell;
}
void Board::moveDown()
{
	Cell tempCell(this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second]);
	this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second] = this->boardNums[this->freeCellCoords.first - 1][this->freeCellCoords.second];
	this->boardNums[this->freeCellCoords.first - 1][this->freeCellCoords.second] = tempCell;
}
void Board::moveLeft()
{
	Cell tempCell(this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second]);
	this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second] = this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second + 1];
	this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second + 1] = tempCell;
}
void Board::moveRight()
{
	Cell tempCell(this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second]);
	this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second] = this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second - 1];
	this->boardNums[this->freeCellCoords.first][this->freeCellCoords.second - 1] = tempCell;
}

void Board::makeMove(char currentCh)
{
	if (currentCh == UP)
		this->moveUp();
	if (currentCh == DOWN)
		this->moveDown();
	if (currentCh == LEFT)
		this->moveLeft();
	if (currentCh == RIGHT)
		this->moveRight();
}
void Board::makeRandomMove()
{	
	this->updatePossibleMoves();
	int randomIndex = rand() % this->possibleMoves.size();
	
	this->updatePositionOfFreeCell();
	makeMove(this->possibleMoves[randomIndex]);
}
void Board::shuffle()
{
	srand(time(NULL));
	for (int i = 0; i < COUNT_OF_SHUFFLES; i++)
	{
		this->makeRandomMove();
	}
}
bool Board::isEndgame()
{
	Board testBoard(dimension);
	return (*this) == testBoard;
}
void Board::clearAndShow()
{
	system("cls");
	cout << *this;
}
void Board::start()
{
	this->shuffle();
	this->clearAndShow();

	int counter = 0;
	while (!this->isEndgame())
	{
		this->updatePossibleMoves();
		this->updatePositionOfFreeCell();
		
		char currentCh = _getch();
		
		if (find(possibleMoves.begin(), possibleMoves.end(), currentCh) != possibleMoves.end())
		{
			makeMove(currentCh);
		}

		this->clearAndShow();
		counter++;
	}

	cout << "Congradulations! You completed solving game!" << "\n";
	cout << "You completed in " << counter << " moves";
}