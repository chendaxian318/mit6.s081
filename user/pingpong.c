#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int pp[2],pc[2];
    pipe(pp),pipe(pc);
    char buffer[1024];
    // 父进程
    if(fork()){
        close(pp[0]);
        close(pc[1]);
        write(pp[1],"ping",strlen("ping"));
        read(pc[0],buffer,1024);
        printf("%d: received %s\n",getpid(),buffer);
    }else { //子进程
        close(pp[1]);
        close(pc[0]);
        read(pp[0],buffer,1024);
        printf("%d: received %s\n",getpid(),buffer);
        write(pc[1],"pong",strlen("pong"));
    }
    exit(0);
}