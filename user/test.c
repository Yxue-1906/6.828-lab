#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[])
{
    int read_from_open=-100;
    printf("%d\n",read_from_open);
    char buf[5];
    read_from_open=read(0,buf,sizeof(buf));
    printf("%d\n",read_from_open);
    close(0);
    read_from_open=read(0,buf,sizeof(buf));
    printf("%d\n",read_from_open);
    exit(0);
}
