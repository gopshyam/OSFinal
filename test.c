#include "ucode.c"
#include "shyamlib.c"

main(int argc, char *argv[ ])
{
  int i;

    char tmpstr[64];
  printf("this is a test program\n");

  printf("argc=%d\n", argc);

  for (i=0; i<argc; i++){
    printf("argv[%d]=%s\n", i, argv[i]);
  }
read(0,tmpstr, 64);

  printf("the end: %s\n", tmpstr);
}

