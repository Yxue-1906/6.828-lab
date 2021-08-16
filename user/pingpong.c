#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int f[2],c[2];
    if(0!=pipe(f)||0!=pipe(c))
    {
        printf("Error occured opening pipe.\n");
        exit(0);
    }
    else{
        if(0==fork())
        {
            //child process
            close(f[0]);
            close(c[1]);
            char buf[5];
            while(!read(f[1],buf,sizeof(buf)));
            printf("%d: received ping\n",getpid());
            write(c[0],"c",1);
            exit(0);
        }
        else{
            close(f[1]);
            close(c[0]);
            write(f[0],"f",1);
            wait(0);
            char buf[5];
            while(!read(c[1],buf,sizeof(buf)));
            printf("%d: received pong\n",getpid());
            exit(0);
        }
    }
}
