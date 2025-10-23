#!/usr/bin/env bash

# usage: ./tt.sh
# must be in the directory where you have your tt.c!
# permission denied or not executable, run: chmod u+x tt.sh

rm -fr tmptst

if [[ ! -e tt.c ]]; then
   echo "ERROR : Cannot find tt.c?"
   exit
fi

mkdir tmptst
cd tmptst
cp ../tt.c .

# copy Neill's original (unaltered) files here
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week5/TentsTrees/Makefile
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week5/TentsTrees/driver.c
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week5/TentsTrees/tentstrees.h

make tt6_d
if [[ ! -e tt6_d ]]; then
   echo "ERROR : Failed to make tt6_d with gcc?"
   exit
fi

make tt4_d
if [[ ! -e tt4_d ]]; then
   echo "ERROR : Failed to make tt4_d with gcc?"
   exit
fi

echo "SUCCESS: Made tt6_d and tt4_d with gcc okay"

# modify Makefile to try clang
sed -i '3s/^/#/' Makefile
sed -i '4s/^#//' Makefile

# rm first, so it actually recompiles with clang
make clean

make tt6_d
if [[ ! -e tt6_d ]]; then
   echo "ERROR : Failed to make tt6_d with clang?"
   exit
fi

make tt4_d
if [[ ! -e tt4_d ]]; then
   echo "ERROR : Failed to make tt4_d with clang?"
   exit
fi

echo "SUCCESS: Made tt6_d and tt4_d with clang okay"

./tt6_d > output.txt 2>&1
e=$?
if (( $e == 0 )); then
   echo "Ran tt6_d OK!"
else
   echo "ERROR : running tt6_d?"
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: tt6_d doesn't run silently?"
   exit
fi


./tt4_d > output.txt 2>&1
e=$?
if (( $e == 0 )); then
   echo "Ran tt4_d OK!"
else
   echo "ERROR : when running tt4_d?"
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: tt4_d doesn't run silently?"
   exit
fi

echo "SUCCESS: Ran tt6_d and tt4_d okay"

# example how to compile with different BSIZE (uncomment below - only compiles)

# gcc tt.c driver.c -DBSIZE=8 -o tt8_d -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -g3 -fsanitize=address -fsanitize=undefined
# if [[ ! -e tt8_d ]]; then
#    echo "ERROR : Failed to make tt8_d with gcc?"
#    exit
# fi

# example if you want to use your own Makefile (replace tt8_d with your Makefile command)

# if [[ ! -e ../Makefile ]]; then
#    echo "ERROR : Cannot find your Makefile?"
#    exit
# fi 
# rm Makefile
# cp ../Makefile .

# make tt8_d
# if [[ ! -e tt8_d ]]; then
#    echo "ERROR : Failed to make tt8_d with gcc?"
#    exit
# fi

# Clean up
cd ..
rm -fr tmptst