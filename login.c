#include "ucode.c"
#include "shyamlib.c"

int in, out, err;

main(int argc, char *argv[]){
    char str[64];
    char username[64];
    char password[64];
    char *pch;
    int fd, ttyfd;
/*
    printf("Username:");
    gets(username);
    printf("\nPassword:");
    gets(password);
*/

    printf("%d %s\n", getpid(), argv[1]);

        in = open(argv[1], 0);
        out = open(argv[1], 1);
        err = open(argv[1], 2);
        settty(argv[1]);
        fd = write(out, "USERNAME\n", 9);
        fd = ttygetline(in, out, username);

    printf("%d %s\n", fd, username);

    fd = open("/etc/passwd", O_RDONLY);
    readline(fd, str);
    printf("READ:%s\n", str);
    readline(fd, str);
    printf("READ:%s\n", str);

    close(fd);
    
    while(1);
}
