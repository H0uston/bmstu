/*находит наибольшую длину монотонного фрагмента последовательности (то есть
такого фрагмента, где все элементы либо больше предыдущего, либо меньше)*/
#include <stdio.h>
#define OK 0
#define ERR_IO -1
#define ERR_DATA 1
#define ERR_CNT 2

int get_max(FILE *f, int *len)
{
    int prev_num, num, inc_seq = 1, dec_seq = 1;
    if (fscanf(f, "%d", &prev_num) == 1)
    {
        while (fscanf(f, "%d", &num) == 1)
        {
            if (prev_num < num)
            {
                if (dec_seq > *len)
                    *len = dec_seq;
                dec_seq = 1;
                inc_seq += 1;
            }
            else if (prev_num > num)
            {
                if (inc_seq > *len)
                    *len = inc_seq;
                inc_seq = 1;
                dec_seq += 1;
            }
            else
            {
                if (inc_seq > *len)
                    *len = inc_seq;
                else if (dec_seq > *len)
                    *len = dec_seq;
                inc_seq = 1;
                dec_seq = 1;
            }
            prev_num = num;
        }

        if (*len < inc_seq)
            *len = inc_seq;
        else if (*len < dec_seq)
            *len = dec_seq;

        if (*len == 1)
       	    return ERR_CNT;

        return OK;
    }

    return ERR_DATA;
}


int main(void)
{
    int len = 1;
    int rc = OK;

    printf("Enter numbers: ");
    rc = get_max(stdin, &len);
    if (rc == OK)
        fprintf(stdout, "max length is %d\n", len);
    else if (rc == ERR_DATA)
        fprintf(stdout, "There are not enough data.\n");
    else
    	fprintf(stdout, "Wrong data in file!\n");


    return rc;
}






