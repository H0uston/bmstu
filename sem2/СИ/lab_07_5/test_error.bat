@echo off
app.exe data\in_%1.txt > data\out.txt
FC data\out.txt data\out_%1.txt
pause