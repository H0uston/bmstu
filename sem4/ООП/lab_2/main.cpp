#include <iostream>

#include "set_imp.h"
#include "set_iterator.h"
using namespace std;


int main(void)
{
    try
    {
        Set<int> tmp;
        tmp.add(5);
        tmp.add(1);
        tmp.add(2);
        std::cout << tmp;
        std::cout << tmp.in(1) << std::endl;
        tmp.remove(4);
        tmp.remove(1);
        std::cout << tmp;
        std::cout << tmp.in(1) << std::endl;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        Set<char> tmp_2;
        tmp_2.add('h');
        tmp_2.add('a');
        tmp_2.add('n');
        tmp_2.add('a');
        std::cout << tmp_2;
        std::cout << tmp_2.in('g') << std::endl;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        Set<int> tmp_3;
        tmp_3.add(9);
        tmp_3.add(5);
        tmp_3.add(12);
        std::cout << tmp_3;

        Set<int> tmp_4;
        tmp_4.add(12);
        tmp_4.add(6);
        tmp_4.add(5);
        std::cout << tmp_4;
        tmp_3.symmetric_difference(tmp_4);
        std::cout << tmp_3;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        Set<int> tmp_5;
        tmp_5.add(45);
        tmp_5.add(12);

        Set<int> tmp_6;
        tmp_6.add(12);
        tmp_6.add(33);

        tmp_6 += tmp_5;
        std::cout << tmp_6;

    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try {
        Set<int> tmp_6(5, 1, 2, 3, 4, 5);
        std::cout << tmp_6;

        int arr[5] = {1, 16, 90, 25, 13};
        Set<int> tmp_7(arr, 5);
        std::cout << tmp_7;

        Set<int> tmp_8({20, 30, 40, 51, 80, 28});
        std::cout << tmp_8;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        std::cout << "8 Test:" << std::endl;
        Set<int> tmp_8({20, 30, 40, 51, 80, 28});
        std::cout << tmp_8;

        tmp_8 + 2;
        std::cout << tmp_8;

        tmp_8, 3;
        std::cout << tmp_8;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        Set<int> tmp_9;
        Set<int> tmp_10;
        tmp_9 -= tmp_10;
        cout << tmp_9;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        Set<int> tmp_9;
        tmp_9.remove(1);
        cout << tmp_9;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        Set<int> tmp_10 = {12, 14, 125};
        Set<int> tmp_11 = {1, 2, 3, 4, 5};
        tmp_10.append(tmp_11);
        std::cout << tmp_10;
        // tmp_10.clear();
        // std::cout << tmp_10;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    try
    {
        Set<int> tmp_12 = {12, 14, 125};
        auto i = tmp_12.inititalizeIterator();
        int j = 0;
        std::cout << *i << std::endl;
        for (; i.check(); i++)
           std::cout << *i << std::endl;
    }
    catch(base_exception &exception)
    {
        std::cout << exception.what();
    }
    std::cout << std::endl << std::endl;

    return 0;
}
