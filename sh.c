#include "ucode.c"
#include "shyamlib.c"

main(int argc, char *argv[]) {
    char cmd[64];
    char program[64];
    char args[64];
    char file[64];
    char path[64];
    char *tmp;
    int pid;
    int status;
    int tmpfd;

    while(1) {
        write(1, "Shy:$ ", 7);
        readline(0,1,cmd);
        write(1, "\n", 1);
        shyamtok(cmd, " ", 0, program);
        shyamtok(cmd, " ", 1, args);

        //Default programs
        if (strcmp(program, "cd") == 0) {
            if (strlen(args)) {
                chdir(args);
            }
            pwd();
            continue;
        }
        if (strcmp(program, "logout") == 0) {
            break;
        }

        pid = fork();
        if (pid) {
            //Parent
            pid = wait(&status);
        } else {
            //Child
            //case 1: Redirect to file
            if (contains(cmd, ">")) {
                shyamtok(cmd, ">", 1, file);
                tmp = lstrip(file);
                tmpfd = open(tmp, O_WRONLY | O_CREAT);
                dup2(tmpfd, 1);
                shyamtok(cmd, ">", 0, cmd);
                //exec(program);
            }
            if (contains(cmd, "<")) {
                shyamtok(cmd, "<", 1, file);
                tmp = lstrip(file);
                close(0);
                tmpfd = open(tmp, O_RDONLY);
                //dup2(tmpfd, 0);
                shyamtok(cmd, "<", 0, cmd);
                //exec(program);
            }
            exec(cmd);
        }

    }
}
