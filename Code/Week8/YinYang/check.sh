#!/usr/bin/env bash

# usage: ./check.sh
# must be in the directory where you have your yy.zip!
# permission denied or not executable, run: chmod u+x check.sh

# to zip files without extension, run: zip yy.zip mydefs.h yy.c
# to zip files with extension, run: zip yy.zip mydefs.h yy.c ext_mydefs.h ext.c

rm -fr tmptst

if [[ ! -e yy.zip ]]; then
   echo "ERROR: Cannot find yy.zip?"
   exit
fi

# count files in the zip, excluding files ending in .yy
l=`unzip -Z1 yy.zip | grep -vc '\.yy$'`
if [[ $l == 2 ]]; then
   # expected mydefs.h and yy.c
   echo "SUCCESS: Found 2 files (excluding .yy files) in yy.zip as expected, with no extension"
   ext=0
elif [[ $l == 4 ]]; then
   # expected mydefs.h, yy.c, ext_mydefs.h, and ext.c
   echo "SUCCESS: Found 4 files (excluding .yy files) in yy.zip as expected, with extension"
   ext=1
else
   echo "ERROR: Expected 2 or 4 files (excluding .yy files) in yy.zip, found $l"
   exit
fi

mkdir tmptst
cd tmptst
cp ../yy.zip .

unzip -q yy.zip
if [[ ! -e mydefs.h ]]; then
   echo "ERROR: Cannot find mydefs.h in yy.zip?"
   exit
fi
if [[ ! -e yy.c ]]; then
   echo "ERROR: Cannot find yy.c in yy.zip?"
   exit
fi
if [[ $ext == 1 ]]; then
   if [[ ! -e ext_mydefs.h ]]; then
      echo "ERROR: Cannot find ext_mydefs.h in yy.zip?"
      exit
   fi
   if [[ ! -e ext.c ]]; then
      echo "ERROR: Cannot find ext.c in yy.zip?"
      exit
   fi
fi

# copy Neill's original (unaltered) files here
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/Makefile -o Makefile
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/driver.c -o driver.c
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/yy.h -o yy.h
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_2x2_nonunique.yy -o g1_2x2_nonunique.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_3x3.yy -o g1_3x3.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_4x4.yy -o g1_4x4.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_5x5.yy -o g1_5x5.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_6x6_nonunique.yy -o g1_6x6_nonunique.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_7x7.yy -o g1_7x7.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_8x8.yy -o g1_8x8.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g1_10x10.yy -o g1_10x10.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g2_3x3_bad.yy -o g2_3x3_bad.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g2_4x4_nonunique.yy -o g2_4x4_nonunique.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g2_6x6.yy -o g2_6x6.yy
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/YinYang/g2_7x7.yy -o g2_7x7.yy

# first try to make with gcc
make yy > output.txt 2>&1
if [[ ! -e yy ]]; then
   echo "ERROR: Failed to make yy with gcc? See output.txt for details."
   exit
fi
echo "SUCCESS: Made yy with gcc okay"
make yy_d > output.txt 2>&1
if [[ ! -e yy_d ]]; then
   echo "ERROR: Failed to make yy_d with gcc? See output.txt for details."
   exit
fi
echo "SUCCESS: Made yy_d with gcc okay"
if [[ $ext == 1 ]]; then
   make ext > output.txt 2>&1
   if [[ ! -e ext ]]; then
      echo "ERROR: Failed to make ext with gcc? See output.txt for details."
      exit
   fi
   echo "SUCCESS: Made ext with gcc okay"
fi

# modify Makefile "gcc" > "clang"
perl -i -pe 's/gcc/clang/g' Makefile
# rm first, so it actually recompiles with clang
make clean

# now try to make with clang
make yy > output.txt 2>&1
if [[ ! -e yy ]]; then
   echo "ERROR: Failed to make yy with clang? See output.txt for details."
   exit
fi
echo "SUCCESS: Made yy with clang okay"
make yy_d > output.txt 2>&1
if [[ ! -e yy_d ]]; then
   echo "ERROR: Failed to make yy_d with clang? See output.txt for details."
   exit
fi
echo "SUCCESS: Made yy_d with clang okay"
if [[ $ext == 1 ]]; then
   make ext > output.txt 2>&1
   if [[ ! -e ext ]]; then
      echo "ERROR: Failed to make ext with clang? See output.txt for details."
      exit
   fi
   echo "SUCCESS: Made ext with clang okay"
fi

# run executables, expect no errors and no output (silent)
./yy > output.txt 2>&1
e=$?
if [[ $e == 0 ]]; then
   echo "SUCCESS: Ran yy OK"
else
   echo "ERROR: Error running yy? See output.txt for details."
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: yy doesn't run silently? See output.txt for details."
   exit
fi
./yy_d > output.txt 2>&1
e=$?
if [[ $e == 0 ]]; then
   echo "SUCCESS: Ran yy_d OK"
else
   echo "ERROR: Error running yy_d? See output.txt for details."
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: yy_d doesn't run silently? See output.txt for details."
   exit
fi
echo "SUCCESS: Ran yy and yy_d with no errors and no output"

# run extension if applicable
if [[ $ext == 1 ]]; then
   # run ext, prints time taken
   /usr/bin/time -p ./ext 2>&1 | awk '/^user/ {print "EXTENSION TIME:", $2}'
   echo "NOTE: the time taken here is illustrative only, you will be marked based on the time taken to solve a series of complex boards."
fi

# clean up
cd ..
rm -fr tmptst