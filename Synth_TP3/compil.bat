@echo off
gcc .\main.c -lfreeglut -lfreeglut_static -lopengl32 -lglu32 -lglew32s
.\a.exe