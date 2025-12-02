#!/usr/bin/env bash

# usage: ./check.sh
# must be in the directory where you have your csa.zip!
# permission denied or not executable, run: chmod u+x check.sh

rm -fr tmptst

if [[ ! -e csa.zip ]]; then
   echo "ERROR: Cannot find csa.zip?"
   exit
fi

# count files in the zip (list files, count lines)
num_files=`unzip -Z1 csa.zip | wc -l`
if [[ $num_files == 2 ]]; then
   # expected mydefs.h and csa.c
   echo "SUCCESS: Found 2 files in csa.zip as expected"
elif [[ $num_files == 3 ]]; then
   # expected mydefs.h, csa.c, and README.txt
   if [[ $(unzip -Z1 csa.zip | grep -qx "README.txt") == false ]]; then
      echo "ERROR: Found 3 files in csa.zip, but no README.txt?"
      exit
   fi
   echo "SUCCESS: Found 3 files in csa.zip as expected, with README.txt"
else
   echo "ERROR: Expected 2 or 3 files in csa.zip, found $num_files"
   exit
fi

mkdir tmptst
cd tmptst
cp ../csa.zip .

unzip -q csa.zip
if [[ ! -e mydefs.h ]]; then
   echo "ERROR: Cannot find mydefs.h in csa.zip?"
   exit
fi
if [[ ! -e csa.c ]]; then
   echo "ERROR: Cannot find csa.c in csa.zip?"
   exit
fi

# copy Neill's original (unaltered) files here
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week11/CSA/Makefile -o Makefile
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week11/CSA/csa.h -o csa.h
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week11/CSA/driver.c -o driver.c
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week11/CSA/fibmemo.c -o fibmemo.c
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week11/CSA/isfactorial.c -o isfactorial.c
curl -s https://raw.githubusercontent.com/csnwc/Exercises-In-C/refs/heads/main/Code/Week11/CSA/sieve.c -o sieve.c

# first try to make with gcc
make csa > output.txt 2>&1
if [[ ! -e csa ]]; then
   echo "ERROR: Failed to make csa with gcc? See output.txt for details."
   exit
fi
make csa_s > output.txt 2>&1
if [[ ! -e csa_s ]]; then
   echo "ERROR: Failed to make csa_s with gcc? See output.txt for details."
   exit
fi
make fibmemo > output.txt 2>&1
if [[ ! -e fibmemo ]]; then
   echo "ERROR: Failed to make fibmemo with gcc? See output.txt for details."
   exit
fi
echo "SUCCESS: Made csa, csa_s, fibmemo with gcc okay"

# modify Makefile "gcc" > "clang"
perl -i -pe 's/gcc/clang/g' Makefile
# rm first, so it actually recompiles with clang
make clean

# now try to make with clang
make csa > output.txt 2>&1
if [[ ! -e csa ]]; then
   echo "ERROR: Failed to make csa with clang? See output.txt for details."
   exit
fi
make csa_s > output.txt 2>&1
if [[ ! -e csa_s ]]; then
   echo "ERROR: Failed to make csa_s with clang? See output.txt for details."
   exit
fi
make fibmemo > output.txt 2>&1
if [[ ! -e fibmemo ]]; then
   echo "ERROR: Failed to make fibmemo with clang? See output.txt for details."
   exit
fi
echo "SUCCESS: Made csa, csa_s, fibmemo with clang okay"

# run executables, expect no errors and no output (silent)
./csa > output.txt 2>&1
if [[ $? == 0 ]]; then
   echo "SUCCESS: Ran csa OK!"
else
   echo "ERROR: Error running csa? See output.txt for details."
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: csa doesn't run silently? See output.txt for details."
   exit
fi
./csa_s > output.txt 2>&1
if [[ $? == 0 ]]; then
   echo "SUCCESS: Ran csa_s OK!"
else
   echo "ERROR: Error running csa_s? See output.txt for details."
   exit
fi
if [[ -s output.txt ]]; then
   echo "ERROR: csa_s doesn't run silently? See output.txt for details."
   exit
fi
./fibmemo > output.txt 2>&1
if [[ $? == 0 ]]; then
   echo "SUCCESS: Ran fibmemo OK!"
else
   echo "ERROR: Error running fibmemo? See output.txt for details."
   exit
fi
# create expected output for fibmemo
expected=$(for ((i=1,a=1,b=1; i<=40; i++)); do
    if (( i == 1 || i == 2 )); then
        fib=1
    else
        fib=$((a + b))
        a=$b
        b=$fib
    fi
    printf "%d => %d\n" "$i" "$fib"
done)
# check fibmemo output matches expected
if [[ "$expected" == "$(<output.txt)" ]]; then
   echo "SUCCESS: fibmemo output correct"
else
   echo "ERROR: fibmemo output incorrect"
   exit
fi

# now try extension executables
make factorials > output.txt 2>&1
if [[ ! -e factorials ]]; then
   echo "ERROR: Failed to make factorials with clang? See output.txt for details."
   exit
fi
make primes > output.txt 2>&1
if [[ ! -e primes ]]; then
   echo "ERROR: Failed to make primes with clang? See output.txt for details."
   exit
fi
make csa_ext > output.txt 2>&1
if [[ ! -e csa_ext ]]; then
   echo "ERROR: Failed to make csa_ext with clang? See output.txt for details."
   exit
fi
echo "SUCCESS: Made extension executables factorials, csa_ext, primes with clang okay"

# now try making extension executables with gcc too
perl -i -pe 's/clang/gcc/g' Makefile
make clean

make factorials > output.txt 2>&1
if [[ ! -e factorials ]]; then
   echo "ERROR: Failed to make factorials with gcc? See output.txt for details."
   exit
fi
make primes > output.txt 2>&1
if [[ ! -e primes ]]; then
   echo "ERROR: Failed to make primes with gcc? See output.txt for details."
   exit
fi
make csa_ext > output.txt 2>&1
if [[ ! -e csa_ext ]]; then
   echo "ERROR: Failed to make csa_ext with gcc? See output.txt for details."
   exit
fi
echo "SUCCESS: Made extension executables factorials, csa_ext, primes with gcc okay"

./factorials > output.txt 2>&1
if [[ $? == 0 ]]; then
   echo "SUCCESS: Ran factorials OK!"
else
   echo "ERROR: Error running factorials? See output.txt for details."
   exit
fi
./primes > output.txt 2>&1
if [[ $? == 0 ]]; then
   echo "SUCCESS: Ran primes OK!"
else
   echo "ERROR: Error running primes? See output.txt for details."
   exit
fi
./csa_ext > output.txt 2>&1
if [[ $? == 0 ]]; then
   echo "SUCCESS: Ran csa_ext OK!"
else
   echo "ERROR: Error running csa_ext? See output.txt for details."
   exit
fi

# clean up
cd ..
rm -fr tmptst