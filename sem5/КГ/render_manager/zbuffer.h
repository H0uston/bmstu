#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <stdio.h>
#include <limits>
#include <assert.h>
#include <vector>

class ZBuffer
{
public:
    ZBuffer(int _width, int _height)
        :
        _width(_width),
        _height(_height),
        pBuffer(std::vector<std::vector<double>>(_height, std::vector<double>(_width, 100)))
    {}
    ~ZBuffer()
    {
    }

    void clear()
    {
        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
                pBuffer[i][j] = 100;
        }
    }

    const double& At(int x, int y) const
    {
        return pBuffer[y][x];
    }

    double& At(int x, int y)
    {
        assert(x >= 0);
        assert(x < _width);
        assert(y >= 0);
        assert(y < _height);
        return pBuffer[y][x];
    }

    void set(int x, int y, double z)
    {
        double& depth = At(x, y);
        depth = z;
    }
private:
    int _width;
    int _height;
    std::vector<std::vector<double>> pBuffer;
};

#endif // ZBUFFER_H
