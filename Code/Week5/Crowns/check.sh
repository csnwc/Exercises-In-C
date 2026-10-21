#!/usr/bin/env bash

# usage: ./check.sh
# must be in the directory where you have your crowns.c!
# permission denied or not executable, run: chmod u+x check.sh

rm -fr tmptst

if [[ ! -e crowns.c ]]; then
   echo "ERROR : Cannot find crowns.c?"
   exit
fi

mkdir tmptst
cd tmptst
cp ../crowns.c .

# copy Neill's original (unaltered) files here
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week5/Crowns/Makefile -o Makefile
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week5/Crowns/driver.c -o driver.c
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week5/Crowns/crowns.h -o crowns.h
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week5/Crowns/lut.o -o lut.o
echo "SUCCESS: Copied original files okay"

make crowns_d > output.txt 2>&1
if [[ ! -e crowns_d ]]; then
   echo "ERROR : Failed to make crowns_d with gcc? See output.txt for details"
   exit
fi

echo "SUCCESS: Made crowns_d with gcc okay"

# modify Makefile to try clang
perl -pi -e 's/gcc/clang/g' Makefile

# rm first, so it actually recompiles with clang
make clean

make crowns_d > output.txt 2>&1
if [[ ! -e crowns_d ]]; then
   echo "ERROR : Failed to make crowns_d with clang? See output.txt for details"
   exit
fi

echo "SUCCESS: Made crowns_d with clang okay"

./crowns_d > output.txt 2>&1
e=$?
if [[ $e == 0 ]]; then
   echo "Ran crowns_d OK!"
else
   echo "ERROR : running crowns_d? See output.txt for details"
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: crowns_d doesn't run silently?"
   exit
fi

echo "SUCCESS: Ran crowns_d okay"

# Clean up
cd ..
rm -fr tmptst