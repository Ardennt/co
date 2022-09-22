#!/bin/bash

#cd lec05
gcc lec05/sleepy.c -o sleepy
gcc lec05/slow.c -o slow -lm

./sleepy 10
./slow
./sleepy 20
