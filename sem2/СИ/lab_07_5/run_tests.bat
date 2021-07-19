@echo off
cls
for %%i in (1 2) do call test_error.bat %%i
for %%i in (3 4 5) do call test_sort.bat %%i
for %%i in (6 7 8) do call test_filter.bat %%i