#!/bin/bash
g++ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl main.cpp shader.cpp glad.c stb.cpp -o a.out