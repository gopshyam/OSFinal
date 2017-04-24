#include "ucode.c"
#include "shyamlib.c"

main(int argc, char *argv[]) {
    char cmd[64];
    char program[64];
    char args[64];
    int pid;
    int status;

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

        //Other shit
        //First no pipes
        //See if we can just get a child to execute cat
        pid = fork();
        if (pid) {
            //Parent
            pid = wait(&status);
        } else {
            exec(cmd);
        }

    }
}
