#include <stdio.h>
#define PRICE 45
#define COST 20

int main(void)
{
    int amount_of_money, count_of_bottle;
	
    printf("Enter amount of money: ");
    scanf("%d", &amount_of_money);

    count_of_bottle = (amount_of_money - COST) / (PRICE - COST);

    printf("Number of bottle: %d", count_of_bottle);
    return 0;
}
