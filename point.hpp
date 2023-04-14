
#ifndef POINT_HPP
#define POINT_HPP

// This class' only purpose is to hold coordinates in row, column form

class Point {
public:
    Point(int row, int column);
    ~Point() = default;
    int getRow() const;
    int getColumn() const;

    void setRow(int row);
    void setColumn(int column);

    friend bool operator== (const Point& p1, const Point& p2);

private:
    int row_;
    int column_;
};

#endif // POINT_HPP
