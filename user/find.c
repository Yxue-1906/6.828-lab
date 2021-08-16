#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void search_dir(char *path, char *pattern) {
    char buf[512]={0};
    int dir;
    struct dirent de;
    struct stat st;
    char *p;

    if ((dir = open(path, 0)) < 0) {
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if(strlen(path)+1+DIRSIZ+1>sizeof(buf)){
        printf("ls: path too long\n");
        return;
    }
    strcpy(buf,path);
    p=buf+strlen(buf);
    *p++='/';
    while (read(dir, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
            continue;
        // printf("%s\n",de.name);
        memmove(p,de.name,DIRSIZ);
        // printf("buf: %s\n",buf);
        p[DIRSIZ]=0;
        if(stat(buf,&st)<0){
            printf("ls: cannot stat %s\n",buf);
            continue;
        }
        switch(st.type){
            case T_FILE:
                if(strcmp(de.name,pattern)==0){
                    printf("%s\n",buf);
                }
                break;
            case T_DIR:
                if(strcmp(de.name,".")==0||strcmp(de.name,"..")==0)
                    continue;
                search_dir(buf,pattern);
        }
    }
    close(dir);
    return;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(2, "Usage: find dir name\n");
        exit(0);
    }

    search_dir(argv[1],argv[2]);
    exit(0);
}
