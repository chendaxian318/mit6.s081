#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char buffer[1024];
int main(int argc,char* argv[]){
    
    if(argc<=1){
        write(1,"please input sleep seconds\n",strlen("please input sleep seconds\n"));
        exit(1);
    }
    else {
        int second = atoi(argv[1]);
        second *= 10;
        sleep(second);
    }
    exit(0);
}