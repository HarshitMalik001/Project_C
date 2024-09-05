#!/bin/bash

gcc -c src/Mylib.c -o src/MylibExec.o
gcc -c src/Game.c -o src/GameExec.o
ar rcs libMylib.a src/MylibExec.o src/GameExec.o
gcc main/game.c -L. libMylib.a -o main/mygame.out

