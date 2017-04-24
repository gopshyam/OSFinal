#include "ucode.c"
#include "shyamlib.c"

main(int argc, char *argv[]) {
    int page = 5;
    int i;
    int fd = 0;
    char c;
    char line[64];
    int outputredirected = 0;
    int rdfd = 0;

    struct stat st_tty;
    struct stat st1;

    //stat(gettty(), &st_tty);
    fstat(0, &st1);
    fstat(2, &st_tty);

    if(st_tty.st_dev != st1.st_dev || st_tty.st_ino != st1.st_ino) {
        outputredirected = 1;
    }

    if (outputredirected) {
        rdfd = open(gettty(), O_RDONLY);
    }
    if(argc > 1) {
        fd = open(argv[1], O_RDONLY);
    }

            i = 0;
            while(readline(fd, 0, line) && i < page) {
                write(1, line, strlen(line));
                write(1, "\n", 1);
                write(2, "\r", 1);
                i++;
            }

    if (i >= page-1) {

    while(1) {
        read(rdfd, &c, 1);
        if (c == 'q') {
            break;
        }
        if (c == ' ') {
            i = 0;
            while(readline(fd, 0, line) > 0 && i < page) {
                write(1, line, strlen(line));
                write(1, "\n", 1);
                write(2, "\r", 1);
                i++;
            }
            if (i < page-1) {
                break;
            }
        } else {
            if(readline(fd, 0, line) > 0) {
                write(1, line, strlen(line));
                write(1, "\n", 1);
                write(2, "\r", 1);
            } else {
                break;
            }
        }
        if (contains(line, "\04")) {
            break;
        }
    }
    }
printf("NULL\n");
close(rdfd);
}
