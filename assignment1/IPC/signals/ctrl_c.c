#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int myvar=10;


static void
ctrlC_signal_handler(int sig){
    printf("Ctrl-C pressed\n");
    printf("Bye Bye =%d \n", myvar);
    myvar++;
    // exit(0);
}

static void
abort_signal_handler(int sig){
    printf("process is aborted\n");
    printf("Bye Bye\n");
    exit(0);
}

int
main(int argc, char **argv){

    signal(SIGINT, ctrlC_signal_handler);
    signal(SIGABRT, abort_signal_handler);
    char ch;
    printf("Abort process (y/n) ?\n");
    scanf("%c", &ch);
    if(ch == 'y')
        abort();
    return 0;
}
