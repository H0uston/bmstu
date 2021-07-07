Позитивные тесты
1. >> ./app.exe test.txt list

<<
Muchin
KIM
2001
23
Rusakov
Kristofer
2008
55
Galkin
Filimon
2001
23
Vorontsov
Kim
1988
12
Shahkov
Evgeniy
1997
9

2. >> ./app.exe test.txt find "kov"

<<
Rusakov
Kristofer
2008
55
Shahkov
Evgeniy
1997
9

3. >> ./app.exe test.txt sort

<<
Galkin
Filimon
2001
23
Muchin
KIM
2001
23
Rusakov
Kristofer
2008
55
Shahkov
Evgeniy
1997
9
Vorontsov
Kim
1988
12

Негативные тесты
1. >> ./app.exe in.txt
ERR CMD
2. >> ./app.exe
ERR CMD
3. >> ./app.exe sfesef.txt 
ERR FILE
4. >> ./app.exe test.txt out.txt file_name.txt 
ERR CMD

Проверка утечек памяти под valgrind'ом для модульных тестов:

parallels@parallels-Parallels-Virtual-Platform:~/Desktop/programming/iu7-cprog-labs-2018-ulasikevgeniy/RK_32_2$ make test.exegcc -std=c99 -Wall -g0 -c test.cgcc -std=c99 -Wall -g0 -c io.cgcc -std=c99 -Wall -g0 -c process.cgcc -o test.exe test.o io.o process.oparallels@parallels-Parallels-Virtual-Platform:~/Desktop/programming/iu7-cprog-labs-2018-ulasikevgeniy/RK_32_2$ valgrind ./test.exe ==12928== Memcheck, a memory error detector==12928== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.==12928== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info==12928== Command: ./test.exe==12928== TEST 'test_my_strstr' - 'OK'TEST 'test_sort' - 'OK'==12928== ==12928== HEAP SUMMARY:==12928==     in use at exit: 0 bytes in 0 blocks==12928==   total heap usage: 305 allocs, 305 frees, 109,296 bytes allocated==12928== ==12928== All heap blocks were freed -- no leaks are possible==12928== ==12928== For counts of detected and suppressed errors, rerun with: -v==12928== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Проверка функциональных тестов на утечки также прошла.
