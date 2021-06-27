#include "matrix.h"

Matrix::Matrix(const int rows, const int columns)
{
    _rows = rows;
    _columns = columns;
    try
    {
        _data = new double* [rows];
        for (int i = 0; i < rows; i++)
        {
            _data[i] = new double [columns];
        }
    }
    catch (std::bad_alloc)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Ошибка выделения памяти!");
        messageBox.setFixedSize(500,200);
        exit(1);
    }
    this->makeZero();
}

Matrix::Matrix(const Matrix& mtx)
{
    _rows = mtx.get_count_rows();
    _columns = mtx.get_count_columns();
    try
    {
        _data = new double*[_rows];
        for (int i = 0; i < _rows; i++)
        {
            _data[i] = new double[_columns];
            for (int j = 0; j < _columns; j++)
                _data[i][j] = mtx[i][j];
        }
    }
    catch (std::bad_alloc)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Ошибка выделения памяти!");
        messageBox.setFixedSize(500,200);
        exit(1);
    }
}

void Matrix::makeZero()
{
    for (int i = 0; i < _rows; i++)
        for (int j = 0; j < _columns; j++)
            _data[i][j] = 0;
}

Matrix::~Matrix()
{
    for (int i = 0; i < _rows; i++)
    {
        delete [] _data[i];
    }
    delete [] _data;
}

void Matrix::makeIdentity()
{
    if (_rows == _columns)
    {
        for (int i = 0; i < _rows; i++)
        {
            for (int j = 0; j < _columns; j++)
            {
                if (i == j)
                    _data[i][j] = 1;
                else
                    _data[i][j] = 0;
            }
        }
    }
}

double* Matrix::operator [] (int index)
{
    if (index < _rows)
        return _data[index];

    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка","Ошибка выделения памяти!");
    messageBox.setFixedSize(500,200);
    exit(1);
}

const double* Matrix::operator [] (const int index) const
{
    if (index < _rows)
        return _data[index];

    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка","Неверный индекс!");
    messageBox.setFixedSize(500,200);
    exit(1);
}

Matrix Matrix::operator * (const double &num)
{
    Matrix mtx(_rows, _columns);
    mtx = *this;
    for (int i = 0; i < _rows; i++)
        for (int j = 0; j < _columns; j++)
            mtx._data[i][j] *= num;
    return mtx;
}

Matrix Matrix::operator * (const Matrix& mtx)
{
    if (_columns == mtx.get_count_rows())
    {
        Matrix res(_rows, mtx.get_count_columns());
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < mtx.get_count_columns(); j++)
                for (int k = 0; k < _columns; k++)
                    res._data[i][j] += _data[i][k] * mtx._data[k][j];
        return res;
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка","Неверный индекс!");
    messageBox.setFixedSize(500,200);
    exit(1);
}

Matrix Matrix::operator + (const Matrix &mtx)
{
    if (_columns == mtx.get_count_columns())
    {
        Matrix res(*this);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _columns; j++)
                res._data[i][j] += mtx._data[i][j];
        return res;
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка","Ошибка размерностей матриц!");
    messageBox.setFixedSize(500,200);
    exit(1);
}

Matrix Matrix::operator - (const Matrix &mtx)
{
    if (_columns == mtx.get_count_columns())
    {
        Matrix res(*this);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _columns; j++)
                res._data[i][j] -= mtx._data[i][j];
        return res;
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка","Ошибка размерностей матриц!");
    messageBox.setFixedSize(500,200);
    exit(1);
}

Matrix& Matrix::operator = (const Matrix& mtx)
{
    if (this == &mtx)
        return *this;

    if (mtx._rows != _rows || mtx._columns != _columns)
    {
        for (int i = 0; i < _rows; i++)
        {
            delete [] _data[i];
        }
        delete [] _data;
        _rows = mtx._rows;
        _columns = mtx._columns;
        try
        {
            _data = new double*[_rows];
        }
        catch (std::bad_alloc)
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Ошибка","Ошибка размерностей матриц!");
            messageBox.setFixedSize(500,200);
            exit(1);
        }
    }
    for (int i = 0; i < _rows; i++)
    {
        _data[i] = new double[_columns];
        for (int j = 0; j < _columns; j++)
            _data[i][j] = mtx._data[i][j];
    }
    return *this;
}

bool Matrix::isZero()
{
    for (int i = 0; i < _rows; i++)
        for (int j = 0; j < _columns; j++)
            if (fabs(_data[i][j]) < 0.00001)
                return false;
    return true;
}

int Matrix::get_count_rows() const
{
    return _rows;
}

int Matrix::get_count_columns() const
{
    return _columns;
}

void Matrix::print_matrix()
{
    for (int i = 0; i < this->get_count_rows(); i++)
    {
        for (int j = 0; j < this->get_count_columns(); j++)
            std::cout << (*this)[i][j] << " ";
        std::cout << std::endl;
    }

}
