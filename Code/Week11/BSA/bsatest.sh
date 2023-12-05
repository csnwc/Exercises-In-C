#!/usr/bin/bash
# This script file should be executable i.e. :    chmod u+x bsatest.sh
# then run it with: ./bsatest.sh
# This script should be in the same directory the Alloc directory
# If extension has been attempted, uncomment on lines 10, 41-55

rm -fr tmptst

# Create .zip file
zip -r bsa.zip Alloc # Extension

# Check there's a .zip file
if [[ -f bsa.zip ]]
then
   echo "PASS - found bsa.zip"
else
   echo "ERROR - can't find bsa.zip ???"
   exit 1
fi
mkdir tmptst
cp bsa.zip tmptst
cd tmptst

# unzip file and check it contains the correct files.
unzip bsa.zip 
if [[ -f Alloc/alloc.c ]]
then
   echo "PASS - found Alloc/alloc.c"
else
   echo "ERROR - can't find Alloc/alloc.c in the zip ???"
   exit 1
fi

if [[ -f Alloc/specific.h ]]
then
   echo "PASS - found Alloc/specific.h"
else
   echo "ERROR - can't find Alloc/specific.h in the zip ???"
   exit 1
fi

# if [[ -f Extension/extension.c ]]
# then
#    echo "PASS - found Extension/extension.c"
# else
#    echo "ERROR - can't find Extension/extension.c in the zip ???"
#    exit 1
# fi

# if [[ -f Extension/specific.h ]]
# then
#    echo "PASS - found Extension/specific.h"
# else
#    echo "ERROR - can't find Extension/specific.h in the zip ???"
#    exit 1
# fi

#wget Neill's version of other files
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/main/Code/Week11/BSA/Makefile
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/main/Code/Week11/BSA/bsa.h
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/main/Code/Week11/BSA/driver.c
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/main/Code/Week11/BSA/fibmemo.c
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/main/Code/Week11/BSA/isfactorial.c
wget https://raw.githubusercontent.com/csnwc/Exercises-In-C/main/Code/Week11/BSA/sieve.c

# Try and compile the code
make driverbsa_s
if [[ -f driverbsa_s ]]
then
   echo "PASS - managed to compile driverbsa_s"
else
   echo "ERROR - driverbsa_s doesn't compile ???"
   exit 1
fi

# Does it run ?
# $? is the exit value of the command
# timeout of 60 seconds in case of infinite loop
# output saved in out.txt
timeout 60 ./driverbsa_s >> out.txt
r=$?
case "$r" in
   0)
      echo "PASS - ran driverbsa_s okay"
      ;;
   1)
      echo "ERROR - running driverbsa_s leads to a sanitizer error ?"
      exit 1
      ;;
   124)
      echo "ERROR - running driverbsa_s leads to an infinite loop/timeout ?"
      exit 1
      ;;
   134)
      echo "ERROR - running driverbsa_s leads to an assert/abort ?"
      exit 1
      ;;
   *)
      echo "ERROR - running driverbsa_s returns a non-zero ($r) error ?"
      exit 1
      ;;
esac

# Check if out.txt is empty i.e. driverbsa_s runs silently
if [[ ! -s out.txt ]]
then
   echo "PASS - driverbsa_s runs silently"
else
   echo "ERROR - driverbsa_s does not run silently"
   exit 1
fi

# Checking for memory leaks with valgrind
# Any memory leaks will be reported in v_out.txt
gcc driver.c Alloc/alloc.c -o driverbsa_v -I./Alloc -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror -g3
valgrind --leak-check=full ./driverbsa_v >& v_out.txt
if [[ $? -eq 0 ]]
then
   echo "PASS - valgrind runs driverbsa_v without errors"
else
   echo "ERROR - driverbsa_v has memory leaks ???"
fi

# Try compiling fibmemo
make fibmemo
if [[ -f fibmemo ]]
then
   echo "PASS - managed to compile fibmemo"
else
   echo "ERROR - fibmemo doesn't compile ???"
   exit 1
fi

# Does fibmemo error?
./fibmemo >& out.txt
if [[ $? -eq 0 ]]
then
   echo "PASS - ran fibmemo okay"
else
   echo "ERROR - fibmemo leads to a non-zero ($?) error???"
fi

# Does fibmemo include the correct starting sequence (1, 1, 2)
n=`cat out.txt| tr '\n' '@'|egrep "1 => 1@2 => 1@3 => 2@"`
if [[ ! ${#n} -eq 0 ]]
then 
   echo "PASS - fibmemo outputs correct starting sequence"
else
   echo "ERROR - fibmemo doesn't print correct starting sequence"
fi

# Clean up
cd ..
rm -fr tmptst
