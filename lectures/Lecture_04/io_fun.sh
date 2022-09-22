#!/bin/bash

# input redirection from file
./a.out < io_input

# output redirection
./a.out < io_input > io_output

# note: using '>' will create a new file/overwrite one if one exists
./a.out < io_input > io_output

# using '>>' will append to an existing file, or create if it doesn't exist
./a.out < io_input >> io_output
./a.out < io_input >> io_output2

# by default, '>' only redirects standard output
# we can use '&>' to redirect standard error as well
./a.out < io_input &> io_output

# we can use 2> to redirect standard error
./a.out < io_input > io_output 2> error_output

# input from piping
cat io_input | ./a.out
ls | ./a.out

# getting wild
cat io_input | ./a.out | cat
cat io_input | ./a.out | ./a.out | ./a.out | ./a.out 
