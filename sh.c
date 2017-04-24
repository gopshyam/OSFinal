#include "ucode.c"
#include "shyamlib.c"

int do_command(char *str) {

    char *cmd = str;
    char file[64];
    char *tmp;
    int tmpfd;


            if (contains(cmd, ">")) {
                shyamtok(cmd, ">", 1, file);
                tmp = lstrip(file);
                if (contains(cmd, ">>")) {
                    tmpfd = open(tmp, O_WRONLY | O_APPEND);
                } else {
                    tmpfd = open(tmp, O_WRONLY | O_CREAT);
                }
                dup2(tmpfd, 1);
                shyamtok(cmd, ">", 0, cmd);
            }
            if (contains(cmd, "<")) {
                shyamtok(cmd, "<", 1, file);
                tmp = lstrip(file);
                close(0);
                tmpfd = open(tmp, O_RDONLY);
                shyamtok(cmd, "<", 0, cmd);
            }
            exec(cmd);
}

main(int argc, char *argv[]) {
    char cmd[64];
    char program[64];
    char args[64];
    char file[64];
    char head[64];
    char tail[64];
    char *tmp;
    int pid;
    int status;
    int tmpfd;
    int pd[2];
    int lpd[2];

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
            if (scan(cmd, head, tail)) {
                //cmd has pipe
                if(pipe(lpd)) {
                    printf("SUCCESS\n");
                }
                pid = fork();
                if (pid) {
                    //Parent child
                    //Reader
                    close(lpd[1]);
                    dup2(lpd[0], 0);
                    close(lpd[0]);
                    pid = wait(&status);
                    do_command(tail);
                } else {
                    close(lpd[0]);
                    dup2(lpd[1], 1);
                    close(lpd[1]);
                    do_command(head);
                }
            } else {
                do_command(cmd);
            }
        }

    }
}


int scan(char *cmdline, char *head, char *tail) {
    int l;

    if (!contains(cmdline, "|")) {
        return 0;
    }
    l = strlen(cmdline) - 1;
    while(l >= 0) {
        if(cmdline[l] == '|') {
            break;
        }
        l--;
    }
    strcpy(head, cmdline);
    head[l] = 0;
    strcpy(tail, cmdline + l + 1);
}
