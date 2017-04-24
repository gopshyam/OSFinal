int shyamtok(char *str, char *delim, int index, char *output) {
    int i = 0;
    char *pch;
    char *tmpstr;
    char cpstr[64];

    strcpy(cpstr, str);

    tmpstr = cpstr;

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

int contains(char *str, char *substr) {
    int l1;
    int l2;
    int i;
    int j;
    int flag;
    l1 = strlen(str);
    l2 = strlen(substr);

    for(i = 0; i <= l1 - l2; i++) {
            flag = 1;
            for(j = 0; j < l2; j++) {
                if (str[i + j] != substr[j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                return 1;
            }
    }
    return 0;
}

char *lstrip(char *s) {
    while(*s == ' ') {
        s++;
    }
    return s;
} 
