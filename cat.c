#include "ucode.c"
#include "shyamlib.c"

main(int argc, char *argv[]) {

    int fd = 0;
    char line[64];
    int outputredirected = 0;

    struct stat st_tty;
    struct stat st1;

    //stat(gettty(), &st_tty);
    fstat(1, &st1);
    fstat(2, &st_tty);

    if(st_tty.st_dev != st1.st_dev || st_tty.st_ino != st1.st_ino) {
        outputredirected = 1;
    }

    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
    }

    while(readline(fd, 2, line) > 0) {
        if (!fd) {
        write(1, line, strlen(line));
        write(1, "\n", 1);
        }
        if(outputredirected) {
            write(2, "\n", 1);
        }
        write(2, "\r", 1);
        if (contains(line, "\04")) {
            break;
        }
    }
}
