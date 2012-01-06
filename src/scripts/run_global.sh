#!/bin/bash

if [ -e ./test_file ]; then
    rm ./test_file
fi

exp_universe=16
exp_n=13
file=results/small_universe

echo "Small universe..."

for sorted in 0 1 2
do
    for k in 1 3 7
    do
        echo "Testing small universe, k=$k, run $m, sorted=$sorted" 
        echo "Testing small universe, k=$k, run $m, sorted=$sorted" >> $file
        for m in {1..10}
        do
            ./make_test_file.sh $((3 * k * (2 ** $exp_n))) $exp_universe

            echo "Binary Heap:" >> $file
            ./run_once_binary $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Binomial Heap:" >> $file
            ./run_once_binomial $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Fibonacci Heap:" >> $file
            ./run_once_fibonacci $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Fibonacci Heap:" >> $file
            ./run_once_fibonacci $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Fibonacci Heap:" >> $file
            ./run_once_fibonacci $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            rm ./test_file
        done
    done
done

exp_universe=24
exp_n=19
file=results/once_big

echo "Big universe"

for sorted in 0 1 2
do
    for k in 1 3 7
    do
        echo "Testing big universe, k=$k, run $m, sorted=$sorted" 
        echo "Testing big universe, k=$k, run $m, sorted=$sorted" >> $file
        for m in {1..10}
        do
            ./make_test_file.sh $((3 * k * (2 ** $exp_n))) $exp_universe

            echo "Binary Heap:" >> $file
            ./run_once_binary $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Binomial Heap:" >> $file
            ./run_once_binomial $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Fibonacci Heap:" >> $file
            ./run_once_fibonacci $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Fibonacci Heap:" >> $file
            ./run_once_fibonacci $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            echo "Fibonacci Heap:" >> $file
            ./run_once_fibonacci $exp_universe $k $exp_n test_file 3 $sorted >> $file
            echo >> $file

            rm ./test_file
        done
    done
done
