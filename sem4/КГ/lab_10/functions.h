#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <math.h>
#define F_NUMBER 5

typedef double (*PFunction)(double, double);

struct surface_data
{
    PFunction func;
    double x_start;
    double x_end;
    double z_start;
    double z_end;
    double x_step;
    double z_step;
};

class Function
{
public:
    Function()
    {
        f_array[0] = &f1;
        f_array[1] = &f2;
        f_array[2] = &f3;
        f_array[3] = &f4;
        f_array[4] = &f5;
    }

    PFunction get_function(int index)
    {
        return f_array[index];
    }
    QString get_function_name(int index)
    {
        switch (index) {
        case 1:
            return "y = x^2 - z^2";
            break;
        case 2:
            return "sin(x^2+z^2) / (x^2 + z^2);";
            break;
        case 3:
            return "sin(x * x + z * z)";
            break;
        case 4:
            return "y = cos^2(x) + sin^2(z))";
            break;
        case 5:
            return "sin(x) * sin(x) * cos(z)";
            break;
        default:
            break;
        }
        return "";
    }

private:
    PFunction f_array[F_NUMBER];

    static double f1(double x, double z)
    {
        return x * x - z * z;
    }
    static double f2(double x, double z)
    {
        return sin(x*x+z*z) / (x * x + z * z);
    }
    static double f3(double x, double z)
    {
        return sin(x * x + z * z);
    }
    static double f4(double x, double z)
    {
        return cos(x) * cos(x) + sin(z) * sin(z);
    }
    static double f5(double x, double z)
    {
        return sin(x) * sin(x) * cos(z);
    }
};


#endif // FUNCTIONS_H
