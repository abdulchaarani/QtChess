
#include "point.hpp"

// This class' only purpose is to hold coordinates in row, column form

Point::Point(int row, int column) : row_{row}, column_{column} {}

int Point::getRow() const{ return row_; }
int Point::getColumn() const{ return column_; }

void Point::setRow(int row) { row_ = row; }
void Point::setColumn(int column) { column_ = column; }

bool  operator== (const Point& p1, const Point& p2)
{
    return (p1.getRow() == p2.getRow() && p1.getColumn() == p2.getColumn());
}
