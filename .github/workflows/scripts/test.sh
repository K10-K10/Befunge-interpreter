#!/bin/bash
cd .github/workflows/scripts/tests

bin=../../../../bef

for file in *.in; do
    filename=${file%.in}
    echo "Testing $filename"
    $bin $file > $filename.out.swap
    flag=0
    if diff $filename.out.swap $filename.out > /dev/null; then
        echo "Test $filename passed"
    else
        echo "Test $filename failed"
        flag=1
    fi
    rm $filename.out.swap
    if [ $flag -eq 1 ]; then
        exit 1
    fi
done