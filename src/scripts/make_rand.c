#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 512

unsigned int buf[BUF_SIZE];

main(int argc, char **argv) {
    int i, universe;
    off_t ret, total, size;
    int fd;
    unsigned int mask;
    char *foo;
 
    if (argc < 4) {
        printf("Usage : make_rand size exp_universe filename\n");
        exit(1);
    }

           
    size = atoll(argv[1]);
    total = 0;
    
    universe = atoi(argv[2]); 

    fd = open(argv[3], O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);

    mask = ~((~0) << universe);

    srandom(time(NULL));

    foo = (char *) buf;

    while (total < size) {   
        for (i = 0; i < BUF_SIZE; i++) {
            buf[i] = random() & mask;
        }

        i = 0;

        while ((ret = write(fd, &(foo[i]), sizeof(unsigned int) * BUF_SIZE - i)) > 0 && (sizeof(unsigned int) * BUF_SIZE - i) > 0) i += ret;

        total++;
    }

    close(fd);
}
