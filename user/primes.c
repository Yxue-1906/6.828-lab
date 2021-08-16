#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    close(2);
    int p[2];
    if(pipe(p)){
        printf("Error occured when opening pipe\n");
        exit(0);
    }
    int pid=fork();
    if(pid>0)
    {
        for(int i=2;i<=35;++i)
        {
            write(p[1],&i,sizeof(i));
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
    else if(pid==0){
        new:
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        int prime;
        if(!read(0,&prime,sizeof(prime))){
            exit(0);
        }
        else{
            printf("prime %d\n",prime);
        }
        if(pipe(p)){
            printf("Error when opening pipe\n");
            exit(0);
        }
        int pid=fork();
        if(pid>0){
            close(p[0]);
            int toJudge;
            while(read(0,&toJudge,sizeof(toJudge)))
            {
                if(toJudge%prime!=0){
                    while(!write(p[1],&toJudge,sizeof(toJudge)));
                }
            }
            close(p[1]);
            wait(0);
            exit(0);
        }
        else if(pid==0){
            goto new;
        }
        else{
            printf("Error occured when fork\n");
            exit(0);
        }
    }
    else{
        printf("Error when fork\n");
        exit(-1);
    }
}
