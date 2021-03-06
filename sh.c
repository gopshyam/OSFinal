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
            } else if (contains(cmd, "<")) {
                shyamtok(cmd, "<", 1, file);
                tmp = lstrip(file);
//                close(0);
                tmpfd = open(tmp, O_RDONLY);
                dup2(tmpfd, 0);
//                close(tmpfd);
                shyamtok(cmd, "<", 0, cmd);
                strcat(cmd, file);
            }
            exec(cmd);
}

int do_pipe(char *cmdline, int *pd) {
    char cmd[64];
    char head[64];
    char tail[64];
    int lpd[2];
    int status;
    int pid;

    strcpy(cmd, cmdline);
    
            if(pd) {
                close(pd[0]);
                dup2(pd[1], 1);
                close(pd[1]);
            }

            if (scan(cmd, head, tail)) {
                //cmd has pipe
                pipe(lpd); 
                pid = fork();
                if (pid) {
                    //Parent child
                    //Reader
                    close(lpd[1]);
                    dup2(lpd[0], 0);
                    close(lpd[0]);
//                    pid = wait(&status);
                    do_command(tail);
                } else {
                    do_pipe(head, lpd);
                }
            } else {
                do_command(cmd);
            }
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
            do_pipe(cmd, 0); 
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
