#include "ucode.c"

main(int argc, char *argv[]) {
    int source;
    int dst;
    char buf[64];

    source = open(argv[1], O_RDONLY);
    dst = open(argv[2], O_WRONLY | O_CREAT);

    while(read(source, buf, 64) > 0) {
        write(dst, buf, strlen(buf));
    }

    close(source);
    close(dst);
}
