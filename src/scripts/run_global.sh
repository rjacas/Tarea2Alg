#!/bin/bash

set -x 

if [ -e ./test_file ]; then
    rm ./test_file
fi

for exp_universe in 20 #16 24
do
    for exp_n in 9 # 19
    do
        for k in 1 #1 3 7
        do
            for m in {1..1}
            do
                ./make_test_file.sh $((3 * $k * (2 ** $exp_n) )) $exp_universe
                ./run_once_binary $exp_universe $k $exp_n test_file 1 1
                ./run_once_binomial $exp_universe $k $exp_n test_file 1 1
                ./run_once_fibonacci $exp_universe $k $exp_n test_file 1 1
                ./run_once_van_emde $exp_universe $k $exp_n test_file 1 1
                ./run_once_splay_tree $exp_universe $k $exp_n test_file 1 1
               #rm ./test_file
            done
        done
    done
done

