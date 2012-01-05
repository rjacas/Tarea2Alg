default: all

all: run_once_binary run_once_binomial run_once_fibonacci run_once_van_emde run_once_splay run_global run_merge_binary run_merge_binomial run_merge_fibonacci make_test_file run_global_merge
	rm bin/*.o

# ================== Scripts ================== 

# ======== Insertions / Deletions ======== 
run_global: src/scripts/run_global.sh
	cp src/scripts/run_global.sh bin/run_global.sh

run_once_binary: binary_heap src/scripts/run_once.c src/structures/priority_queue.h
	gcc -g bin/binary_heap.o src/scripts/run_once.c -lrt  -o bin/run_once_binary

run_once_binomial: binomial_heap src/scripts/run_once.c src/structures/priority_queue.h
	gcc -g bin/binomial_heap.o src/scripts/run_once.c -lm -lrt -o bin/run_once_binomial

run_once_fibonacci: fibonacci_heap src/scripts/run_once.c src/structures/priority_queue.h
	gcc -g bin/fibonacci_heap.o src/scripts/run_once.c  -lm -lrt -o bin/run_once_fibonacci

run_once_van_emde: van_emde src/scripts/run_once.c src/structures/priority_queue.h
	gcc -g bin/van_emde.o src/scripts/run_once.c -lm -lrt -o bin/run_once_van_emde

run_once_splay: splay_tree src/scripts/run_once.c src/structures/priority_queue.h
	gcc -g bin/splay_tree.o src/scripts/run_once.c  -lrt -o bin/run_once_splay


# ======== Merges ======== 

run_global_merge: src/scripts/run_global_merge.sh
	cp src/scripts/run_global_merge.sh bin/run_global_merge.sh

run_merge_binary: binary_heap src/scripts/run_merge.c src/structures/priority_queue.h
	gcc -g bin/binary_heap.o src/scripts/run_merge.c -lrt  -o bin/run_merge_binary

run_merge_binomial: binomial_heap src/scripts/run_merge.c src/structures/priority_queue.h
	gcc -g bin/binomial_heap.o src/scripts/run_merge.c -lm -lrt -o bin/run_merge_binomial

run_merge_fibonacci: fibonacci_heap src/scripts/run_merge.c src/structures/priority_queue.h
	gcc -g bin/fibonacci_heap.o src/scripts/run_merge.c  -lm -lrt -o bin/run_merge_fibonacci


# ================== Utils ================== 

make_test_file: src/scripts/make_test_file.sh src/scripts/make_test_file.sh
	gcc -g src/scripts/make_rand.c -o bin/make_rand
	cp src/scripts/make_test_file.sh bin/make_test_file.sh

# ================== Structures ================== 

binary_heap:  src/structures/priority_queue.h src/structures/binary_heap.c
	gcc -g -c src/structures/binary_heap.c -o bin/binary_heap.o

binomial_heap:  src/structures/priority_queue.h src/structures/binary_heap.c
	gcc -g -c src/structures/binomial_heap.c -o bin/binomial_heap.o

fibonacci_heap:  src/structures/priority_queue.h src/structures/fibonacci_heap.c
	gcc -g -c src/structures/fibonacci_heap.c -o bin/fibonacci_heap.o

van_emde:  src/structures/priority_queue.h src/structures/van_emde_boas.c
	gcc -g -c src/structures/van_emde_boas.c -o bin/van_emde.o

splay_tree:  src/structures/priority_queue.h src/structures/splay_tree.c
	gcc -g -c src/structures/splay_tree.c -o bin/splay_tree.o

# ================== Cleaning, etc ================== 

clean:
	rm -f `ls -1 bin/* | grep -v 'bin_README\|results'`
