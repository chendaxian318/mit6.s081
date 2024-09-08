#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
int main(int argc,char * argv[]){
    char *buf[20];
    char buf1[512];
    char *p=buf1;
    for(int i = 0;i+1 < argc;i++){
        buf[i] = argv[i+1];
    }
    
    int len=read(0,buf1,512);
    printf("%s",buf);
    buf1[len]='\n';
    buf1[len+1]='\0';
    //printf("buf1=%s\n",buf1);
    //for(int i = 0 ;i<=strlen(buf1);i++)printf("%c\n",buf1[i]);
    char temp[512]="";
    int len1=0;
    
    while(1){
        if(*p=='\n'){
            //printf("len1=%d %c",len1,*p);
            p++;
            //printf("test1\n");
            temp[len1]='\0';
            buf[argc-1]=temp;
            buf[argc]=0;
            len1=0;
            if(!fork()){
                //printf("test01\n");
                //printf("%d",p-buf1);
                printf("argv[1]=%s  buf[0]=%s  buf[1]=%s  buf[2]=%s buf[3]=%s\n",argv[1],buf[0],buf[1],buf[2],buf[3]);
                exec(argv[1],buf);

            }
            wait(0);
            if(*p=='\0') {
                exit(0);
            }            
            memcpy(temp,buf1,strlen(buf1)+1);
        }
        else {
            //printf("test2\n");
            temp[len1++]=*p;
            p++;
        }
    }
    //printf("%s\n",buf);
    
    exit(0);
}