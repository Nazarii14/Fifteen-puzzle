#include "includes.h"
#include "cell.h"

Cell::Cell(const Cell& cell)
{
	this->number = cell.number;
}
Cell::Cell() {};
Cell::Cell(string number)
{
	this->number = number;
}
string Cell::getNumber()
{
	return number;
}
void Cell::setNumber(string number)
{
	this->number = number;
}
bool Cell::operator==(const Cell& cell)
{
	return this->getNumber() == cell.number;
}
bool Cell::operator!=(const Cell& cell)
{
	return this->getNumber() != cell.number;
}
bool Cell::isFree()
{
	return this->getNumber() == " ";
}