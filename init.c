#include "ucode.c"

int console;

int parent() {
    int pid, status;
    while(1) {
        printf("INIT waits for a zombie child\n");
        pid = wait(&status);
        if(pid == console) {
            printf("INIT Forks a new login process\n");
            console = fork();
            if(console)
                continue;
            else
                exec("login /dev/tty0");
        }
    printf("INIT just buried an orphan child proc");
    }
}

main() {
    int in, out;
    in = open("/dev/tty0", O_RDONLY);
    out = open("/dev/tty0", O_WRONLY);
    printf("Fork a login process on console\n");
    console = fork();
    if (console) {
        parent();
    } else {
        exec("login /dev/tty0");
    }
}
