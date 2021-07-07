#include <stdio.h>

int process(int *pbeg, const int *pend)
{
    int *current_item, *another_item, count_diff_elem = 0;
    for (current_item = pbeg; current_item < pend; current_item++)
    {
        count_diff_elem++;
        for (another_item = current_item - 1; another_item >= pbeg; another_item--)
        {
            if (*current_item == *another_item)
            {
                count_diff_elem--;
                break;
            }
        }
    }

    return count_diff_elem;
}
