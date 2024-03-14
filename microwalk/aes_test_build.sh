#!/bin/bash
gcc aes_test.c -g -fno-inline -fno-split-stack -L ../ -lbotan-3 -I "../build/include" -o aes_test.o
