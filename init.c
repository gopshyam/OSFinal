#include "ucode.c"

int console, s0, s1;

main(int argc, char *argv[]) {
    console = fork();
    if (console) {
        exec("sinit /dev/tty0");
    } else {
        s0 = fork();
        if (s0) {
            exec("sinit /dev/ttyS0");
        } else {
            exec("sinit /dev/ttyS1");
        }
    }
}
