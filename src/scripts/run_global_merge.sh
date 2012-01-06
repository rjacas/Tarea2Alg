#!/bin/bash

if [ -e ./test_file ]; then
    rm ./test_file
fi

exp_universe=16
exp_n=13
file=results/merge_small

echo "Small universe..."
echo "Test: k=$k" >> $file

for percent in 10 20 30 40 50
do
for m in {1..10}
do
    echo "Testing small universe, k=$k, run $m, percentage=$percent" 
    ./make_test_file.sh $((2 ** $exp_n)) $exp_universe

    echo "Binary Heap:" >> $file
    ./run_merge_binary $exp_universe $exp_n $percent test_file 10 0 >> $file
    echo >> $file
    
    echo "Binomial Heap:" >> $file
    ./run_merge_binomial $exp_universe $exp_n $percent test_file 10 0 >> $file
    echo >> $file

    echo "Fibonacci Heap:" >> $file
    ./run_merge_fibonacci $exp_universe $exp_n $percent test_file 10 0 >> $file
    echo >> $file

    rm ./test_file
done
done

exp_universe=24
exp_n=21
file=results/merge_big

echo "Big universe"

for percent in 10 20 30 40 50
do
for m in {1..10}
do
    echo "Testing big universe, run $m, percentage=$percent" 
    ./make_test_file.sh $((2 ** $exp_n)) $exp_universe

    echo "Binary Heap:" >> $file
    ./run_merge_binary $exp_universe $exp_n $percent test_file 10 0 >> $file
    echo >> $file
    
    echo "Binomial Heap:" >> $file
    ./run_merge_binomial $exp_universe $exp_n $percent test_file 10 0 >> $file
    echo >> $file

    echo "Fibonacci Heap:" >> $file
    ./run_merge_fibonacci $exp_universe $exp_n $percent test_file 10 0 >> $file
    echo >> $file

    rm ./test_file
done
done

