#!/bin/bash

declare -a arr=("c90" "c89" "iso9899:1990" "iso9899:199x" "c11" "c1x" "iso9899:2011" "c17" "c18" "iso9899:2017" "iso9899:2018" "c2x" "gnu90" "gnu89" "gnu99" "gnu9x" "gnu11" "gnu1x" "gnu17" "gnu18" "gnu2x")

rm -f loops
echo gcc loops.c -o loops
gcc loops.c -o loops
./loops
echo "******************************************************************************"

## now loop through the above array
for i in "${arr[@]}"
do
   rm -f loops
   echo gcc -std="$i" loops.c -o loops
   gcc -std="$i" loops.c -o loops
   ./loops
   echo "******************************************************************************"
done
