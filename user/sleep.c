#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Usage: sleep <sleep time in second>\n");
        exit(0);
    }
    else{
        int time=atoi(argv[1]);
        sleep(time);
        exit(0);
    }
}
