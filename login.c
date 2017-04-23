#include "ucode.c"
#include "shyamlib.c"

int in, out, err;

main(int argc, char *argv[]){
    char str[64];
    char username[64];
    char password[64];
    char actual_password[64];
    char gid[10];
    char uid[10];
    char user_dir[64];
    char user_program[64];
    int fd, ttyfd;


    in = open(argv[1], 0);
    out = open(argv[1], 1);
    err = open(argv[1], 2);
    settty(argv[1]);
    write(out, "Username:", 9);
    readline(in, out, username);
    write(out, "\nPassword:", 10);
    readline(in, out, password);

    printf("\n%s %s\n", username, password);

    fd = open("/etc/passwd", O_RDONLY);
    while(1) {
        if(readline(fd, 0, str) < 1) {
            break;
        }
        if (str == 0) {
            break;
        }
        if (strcmp(username, strtok(str, ":")) == 0) {
            printf("FOUND\n");
            shyamtok(str, ":", 1, actual_password);
            printf("%s\n", actual_password);
            if (strcmp(password, actual_password) != 0) {
                printf("WRONG PASSWORD\n");
                break;
            }
            //Valid account at this point
            close(fd);
            shyamtok(str, ":", 2, uid);
            shyamtok(str, ":", 3, gid);
            shyamtok(str, ":", 5, user_dir);
            shyamtok(str, ":", 6, user_program);

            chuid(*uid - '0',*gid - '0');
            chdir(user_dir);
            exec(user_program); 
            break;
        }
    }
    
    printf("INVALID ACCOUNT\n");
    close(fd);
    
    while(1);
}
