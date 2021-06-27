#ifndef RAILROAD_H
#define RAILROAD_H

#include "model.h"
#include "config.h"

class Railroad : public Model
{
public:
    Railroad(double x_start, double x_end, double y, double z);


private:
    void make_mound(double x, double y, double z);
    void make_wood_board(double x, double y, double z, double length=2, double width=6, double height=0.5);
    void make_rails(double x, double y, double z, double length=20, double width=0.5, double height=0.5);
    void make_tunnel(double x, double y, double z, double width=18, double height=18);
    QColor _color_mound = Qt::gray;
    QColor _color_wood = QColor(133,94,66);
    QColor _color_steel = QColor(67, 70, 75);
    QColor _color_tunel = QColor(0,0,0);
    double mound_length = 20;
    double mound_width = 12;
    double mound_height = 4;
};

#endif // RAILROAD_H
