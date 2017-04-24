#include "ucode.c"

int console, s0, s1;

int parent(char *cmd) {
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
                exec(cmd);
        }
    printf("INIT just buried an orphan child proc");
    }
}

main(int argc, char *argv[]) {
    int in, out;
    char cmd[64];
    in = open(argv[1], O_RDONLY);
    out = open(argv[1], O_WRONLY);
    printf("Fork a login process on console\n");
    strcpy(cmd, "login ");
    strcat(cmd, argv[1]);
    console = fork();
    if (console) {
        parent(cmd);
    } else {
        exec(cmd);
    }
}
