#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path){
    static char buf[DIRSIZ+1];
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if(strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p)+1);
    return buf;
}
char paths[100][100];
int cnt=0;
void find(char path[],char filename[]){
    //printf("test06\n");
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if((fd = open(path, 0)) < 0){
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }
   

    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
    printf("ls: path too long\n");
    
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        char temp[1024];
        memcpy(temp,path,strlen(path)+1);
        temp[strlen(path)]='/';
        temp[1+strlen(path)]='\0';
        //printf("test01\n");
        memcpy(temp+strlen(temp),p,strlen(p)+1);
        //printf("test02\n");
        if(!strcmp(p,".")||!strcmp(p,"..")){
            //printf("test02\n");
            continue;
        }
        //printf("temp=%s filename=%s\n",temp,filename);
        int fd1;
        fd1= open(temp,0);
        fstat(fd1, &st);
        close(fd1);
        switch (st.type)
        {
        case T_DIR:
            memcpy(paths[cnt++],temp,strlen(temp)+1);
            break;
        case T_FILE:
            if(!strcmp(fmtname(temp),filename)){
                printf("%s\n",temp);
            }
            break;
        default:
            break;
        }
        
    }
    close(fd);
    
}

int main(int argc, char *argv[])
{
    char path[512],filename[512];
    if(argc < 2){
        printf("please input path filename");
    }
    else if(argc == 2){
        memcpy(path,".",strlen(".")+1);
        memcpy(filename,argv[1],strlen(argv[1])+1);
        find(path,filename);
    }
    else {
        memcpy(path,argv[1],strlen(argv[1])+1);
        memcpy(filename,argv[2],strlen(argv[2])+1);
        find(path,filename);
    }
    memcpy(paths[cnt++],path,strlen(path)+1);
    while(cnt>0){
        find(paths[--cnt],filename);
    }
    exit(0);
}
