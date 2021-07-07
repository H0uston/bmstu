#if TYPE == 2
#include "set_list.h"
#else
#include "set_array.h"
#endif

#define N 10
#define M 3
#define K 5

void test_union(void)
{
    int error_count = 0;
    int i = 1;

    // 1-ый тест. Оба множества пустые
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        set_t set_c = set_union(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 2-ый тест. Первое множество пустое
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_union(set_a, set_b);
        set_t set_right = set_create();
        for (int j = M; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 3-ый тест. Второе множество пустое
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_a, j);
        set_t set_c = set_union(set_a, set_b);
        set_t set_right = set_create();
        for (int j = K; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 4-ый тест. Оба множества содержат элементы
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_union(set_a, set_b);
        set_t set_right = set_create();
        for (int j = 0; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 5-ый тест. Оба множества содержат элементы. Некоторые пересекаются
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_union(set_a, set_b);
        set_t set_right = set_create();
        for (int j = 0; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    printf("\nTEST %s - %s", __func__, error_count ? "FAIL" : "OK");
}

void test_intercection(void)
{
    int error_count = 0;
    int i = 1;

    // 1-ый тест. Оба множества пустые. Нет пересечения
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        set_t set_c = set_intercection(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 2-ый тест. Первое множество пустое. Нет пересечения
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_intercection(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 3-ый тест. Второе множество пустое. Нет пересечения
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_a, j);
        set_t set_c = set_intercection(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 4-ый тест. Оба множества содержат элементы. Нет пересечения
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_intercection(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 5-ый тест. Оба множества содержат элементы. Есть пересечение
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_intercection(set_a, set_b);
        set_t set_right = set_create();
        for (int j = M; j < K; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    printf("\nTEST %s - %s", __func__, error_count ? "FAIL" : "OK");
}

void test_difference(void)
{
    int error_count = 0;
    int i = 1;

    // 1-ый тест. Оба множества пустые
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        set_t set_c = set_difference(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 2-ый тест. Первое множество пустое
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_difference(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 3-ый тест. Второе множество пустое
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_a, j);
        set_t set_c = set_difference(set_a, set_b);
        set_t set_right = set_create();
        for (int j = K; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 4-ый тест. Оба множества содержат элементы
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_difference(set_a, set_b);
        set_t set_right = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 5-ый тест. Оба множества содержат элементы. Некоторые пересекаются
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_difference(set_a, set_b);
        set_t set_right = set_create();
        for (int j = 0; j < M; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    printf("\nTEST %s - %s", __func__, error_count ? "FAIL" : "OK");
}

void test_symmetric_difference(void)
{
    int error_count = 0;
    int i = 1;

    // 1-ый тест. Оба множества пустые
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        set_t set_c = set_symmetric_difference(set_a, set_b);
        set_t set_right = set_create();
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 2-ый тест. Первое множество пустое
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_symmetric_difference(set_a, set_b);
        set_t set_right = set_create();
        for (int j = M; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 3-ый тест. Второе множество пустое
    {
        set_t set_a = set_create();
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_a, j);
        set_t set_c = set_symmetric_difference(set_a, set_b);
        set_t set_right = set_create();
        for (int j = K; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 4-ый тест. Оба множества содержат элементы
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = K; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_symmetric_difference(set_a, set_b);
        set_t set_right = set_create();
        for (int j = 0; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    // 5-ый тест. Оба множества содержат элементы. Некоторые пересекаются
    {
        set_t set_a = set_create();
        for (int j = 0; j < K; j++)
            set_add(set_a, j);
        set_t set_b = set_create();
        for (int j = M; j < N; j++)
            set_add(set_b, j);
        set_t set_c = set_symmetric_difference(set_a, set_b);
        set_t set_right = set_create();
        for (int j = 0; j < M; j++)
            set_add(set_right, j);
        for (int j = K; j < N; j++)
            set_add(set_right, j);
        if (!(set_same(set_c, set_right)))
            error_count += 1;
        set_free(set_a);
        set_free(set_b);
        set_free(set_c);
        set_free(set_right);
    }
    if (error_count)
        printf("\nProblems with %d-th test", i);
    i++;

    printf("\nTEST %s - %s", __func__, error_count ? "FAIL" : "OK");
}


int main(void)
{
#if TYPE == 2
    printf("Test of list\n");
#else
    printf("Test of array\n");
#endif
    test_union();
    test_intercection();
    test_difference();
    test_symmetric_difference();
    return 0;
}

