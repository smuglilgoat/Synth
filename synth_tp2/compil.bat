@echo off
gcc .\secondary.c -lfreeglut -lfreeglut_static -lopengl32 -lglu32
.\a.exe
pause