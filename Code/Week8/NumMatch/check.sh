#!/usr/bin/env bash

# usage: ./nm.sh
# must be in the directory where you have your nm.zip!
# permission denied or not executable, run: chmod u+x nm.sh

rm -fr tmptst

if [[ ! -e nm.zip ]]; then
   echo "ERROR: Cannot find nm.zip?"
   exit
fi

# count files in the zip (list files, count lines)
l=`unzip -l nm.zip | wc -l`
l=$(( l - 5 ))  # subtract 5 for non-file lines
if [[ $l == 2 ]]; then
   # expected mydefs.h and nm.c
   echo "SUCCESS: Found 2 files in nm.zip as expected, with no extension"
   ext=0
elif [[ $l == 4 ]]; then
   # expected mydefs.h, nm.c, ext_mydefs.h, and ext.c
   echo "SUCCESS: Found 4 files in nm.zip as expected, with extension"
   ext=1
else
   echo "ERROR: Expected 2 or 4 files in nm.zip, found $l"
   exit
fi

mkdir tmptst
cd tmptst
cp ../nm.zip .

unzip -q nm.zip
if [[ ! -e mydefs.h ]]; then
   echo "ERROR: Cannot find mydefs.h in nm.zip?"
   exit
fi
if [[ ! -e nm.c ]]; then
   echo "ERROR: Cannot find nm.c in nm.zip?"
   exit
fi
if [[ $ext == 1 ]]; then
   if [[ ! -e ext_mydefs.h ]]; then
      echo "ERROR: Cannot find ext_mydefs.h in nm.zip?"
      exit
   fi
   if [[ ! -e ext.c ]]; then
      echo "ERROR: Cannot find ext.c in nm.zip?"
      exit
   fi
fi

# copy Neill's original (unaltered) files here
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/NumMatch/Makefile -o Makefile
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/NumMatch/driver.c -o driver.c
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/NumMatch/nm.h -o nm.h
if [[ $ext == 1 ]]; then
   curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/NumMatch/ext_driver.c -o ext_driver.c
   curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week8/NumMatch/ext_nm.h -o ext_nm.h
fi

# first try to make with gcc
make nm > output.txt 2>&1
if [[ ! -e nm ]]; then
   echo "ERROR: Failed to make nm with gcc? See output.txt for details."
   exit
fi
make nm_d > output.txt 2>&1
if [[ ! -e nm_d ]]; then
   echo "ERROR: Failed to make nm_d with gcc? See output.txt for details."
   exit
fi
echo "SUCCESS: Made nm and nm_d with gcc okay"
if [[ $ext == 1 ]]; then
   make extension > output.txt 2>&1
   if [[ ! -e extension ]]; then
      echo "ERROR: Failed to make extension with gcc? See output.txt for details."
      exit
   fi
   echo "SUCCESS: Made extension with gcc okay"
fi

# modify Makefile "gcc" > "clang"
perl -i -pe 's/gcc/clang/g' Makefile
# rm first, so it actually recompiles with clang
make clean

# now try to make with clang
make nm > output.txt 2>&1
if [[ ! -e nm ]]; then
   echo "ERROR: Failed to make nm with clang? See output.txt for details."
   exit
fi
make nm_d > output.txt 2>&1
if [[ ! -e nm_d ]]; then
   echo "ERROR: Failed to make nm_d with clang? See output.txt for details."
   exit
fi
echo "SUCCESS: Made nm and nm_d with clang okay"
if [[ $ext == 1 ]]; then
   make extension > output.txt 2>&1
   if [[ ! -e extension ]]; then
      echo "ERROR: Failed to make extension with clang? See output.txt for details."
      exit
   fi
   echo "SUCCESS: Made extension with clang okay"
fi

# run executables, expect no errors and no output (silent)
./nm > output.txt 2>&1
e=$?
if [[ $e == 0 ]]; then
   echo "SUCCESS: Ran nm OK!"
else
   echo "ERROR: Error running nm? See output.txt for details."
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: nm doesn't run silently? See output.txt for details."
   exit
fi
./nm_d > output.txt 2>&1
e=$?
if [[ $e == 0 ]]; then
   echo "SUCCESS: Ran nm_d OK!"
else
   echo "ERROR: Error running nm_d? See output.txt for details."
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: nm_d doesn't run silently? See output.txt for details."
   exit
fi
echo "SUCCESS: Ran nm and nm_d okay"

# run extension if applicable
if [[ $ext == 1 ]]; then
   # run extension, prints time taken
   /usr/bin/time -p ./extension 2>&1 | awk '/^user/ {print "EXTENSION TIME:", $2}'
   echo "NOTE: the time taken here is illustrative only, you will be marked based on the time taken to solve a series of complex boards."
fi

# clean up
cd ..
rm -fr tmptst