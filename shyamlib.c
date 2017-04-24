int shyamtok(char *str, char *delim, int index, char *output) {
    int i = 0;
    char *pch;
    char *tmpstr = str;

    pch = strtok(tmpstr, delim);
    while(i < index) {
        tmpstr += strlen(pch) + 1;
        pch = strtok(tmpstr, delim);
        i++;
    }
    strcpy(output, pch);
}

int readline(int in, int out, char *str) {
    char tmp;
    int i = 0;
    int t;
    while(i < 64) {
        t = read(in, &tmp, 1);
        if (t < 1) {
            str[i] = 0;
            return -1;
        }
        if(tmp == '\r') {
            tmp == '\n';
        }
        if(out) {
            write(out, &tmp, 1);
        }
        str[i++] = tmp;
        if(tmp == '\r' || tmp == '\n') {
            break;
        }
    }
    str[i-1] = 0;
    return i;
}
