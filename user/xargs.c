#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    if(argc<1){
        printf("Usage: command | xargs command\n");
        exit(0);
    }
    if(argc>MAXARG){
        fprintf(2,"Too many args!\n");
        exit(-1);
    }

    char buf[512]={0};
    char *p=buf;
    while(read(0,p,1)){
        if(*p=='\n')
        {
            *p=0;
            int pid=fork();
            if(pid<0){
                fprintf(2,"Fork error!\n");
                exit(-1);
            }
            else if(pid==0){
                //child process
                char *args[MAXARG];
                int i=0;
                for( i=1;i<=MAXARG&&i<argc;++i)
                {
                    args[i-1]=argv[i];
                }
                p=buf;
                while(*p!=0){
                    args[i++-1]=p;
                    while(*p!=' ')
                        p++;
                    *p++=0;
                }
                args[i]=0;
                exec(args[0],args);
            }
            else{
                wait(0);
                memset(buf,0,sizeof(buf));
                p=buf;
            }
        }
        else{
            p++;
        }
    }
    exit(0);
}
