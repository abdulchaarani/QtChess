
#ifndef BOX_HPP
#define BOX_HPP
#include <QApplication>
#include <QPushButton>

class Box : public QPushButton

{
    Q_OBJECT

public:
    Box(int x, int y, QWidget *parent = nullptr);
    ~Box() = default;

private:
    int x_;
    int y_;

    int BOX_SIZE{150};
    int X_OFFSET{750};
    int Y_OFFSET{100};


    inline static bool counter_{false};

    void setColorWhite();
    void setColorBlack();
};


#endif // BOX_HPP
