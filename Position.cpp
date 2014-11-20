#include "Position.h"


Position::Position()
{
    //ctor
}

Position::Position(int x,int y)
{
	SetX(x);
	SetY(y);
}

Position::~Position()
{
    //dtor
}

void Position::print(std::ostream& os)
{
	os << "[" << GetX() << " , " << GetY() << "]" ;
}

std::ostream& operator<<(std::ostream& os, Position& obj)
{
	obj.print(os);  
	return os; 
}
