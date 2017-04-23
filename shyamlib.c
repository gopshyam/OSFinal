char *shyamtok(char *str, char *delim, int index) {
    int i = 1;
    char *pch;

    pch = strtok(str, delim);
    while(i < index) {
        pch = strtok(0, delim);
        if (pch == 0) {
            return 0;
        }
        i++;
    }
    return pch;
}

char *readline(int fd, char *buf) {
    int i;
    read(fd, buf, 64);
    for(i = 0; i < 64; i++) {
        if(buf[i] == '\n') {
            buf[i] = 0;
        }
    }
}

int ttygetline(int in, int out, char *str) {
    char tmp;
    int i = 0;
    while(i < 64) {
        read(in, &tmp, 1);
        write(out, &tmp, 1);
        str[i++] = tmp;
        if(tmp == '\r' || tmp == '\n') {
            break;
        }
    }
    str[i-1] = 0;
    return i;
}
