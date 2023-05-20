#pragma once

class Cell
{
private:
	string number;
public:
	Cell();
	Cell(const Cell& cell);
	Cell(string number);
	string getNumber();
	void setNumber(string number);
	bool operator==(const Cell& cell);
	bool operator!=(const Cell& cell);
	bool isFree();
};