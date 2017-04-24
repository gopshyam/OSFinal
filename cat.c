#include "ucode.c"
#include "shyamlib.c"

main(int argc, char *argv[]) {

    int fd = 0;
    char line[64];

    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
    }

    while(readline(fd, 1, line) > 0);
}
