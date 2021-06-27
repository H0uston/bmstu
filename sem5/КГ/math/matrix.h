#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>
#include <QMessageBox>

class Matrix
{
public:
    Matrix(const int rows, const int columns);
    Matrix(const Matrix& mtx);
    ~Matrix();
    int get_count_rows() const;
    int get_count_columns() const;
    void makeIdentity();
    void makeZero();
    bool isZero();
    double* operator [] (int index);
    const double* operator [] (const int index) const;
    Matrix operator * (const double& num);
    Matrix operator * (const Matrix& mtx);
    Matrix operator + (const Matrix& mtx);
    Matrix operator - (const Matrix& mtx);
    Matrix& operator = (const Matrix& mtx);
    void print_matrix();

private:
    double **_data;
    int _rows;
    int _columns;
};

#endif // MATRIX_H
