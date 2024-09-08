#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void check_primes(int cnt,int fp[][2]){
    // 关掉父进程的写端
    close(fp[cnt-1][1]);
    int p;
    // 正常读取到了数字，继续往下递归
    if(read(fp[cnt-1][0],(void *)&p,sizeof(int))){
        printf("prime %d\n",p);
        close(fp[cnt-1][1]);
        int temp;
        pipe(fp[cnt]);
        if(fork()){
            // 把当前进程的读端关掉
            close(fp[cnt][0]);
            // 一直都有读取到数字
            while(read(fp[cnt-1][0],&temp,sizeof(temp))){
                if(temp%p){
                    write(fp[cnt][1],&temp,sizeof(temp));
                }
            }
            // 把当前进程的写端给关掉
            close(fp[cnt][1]);
            wait(0);
        }else {
            check_primes(++cnt,fp);
            
        }
    }
    // 读取数字失败，可以直接返回了
    
}
int main(){
    int fp[37][2];
    int cnt=0;
    // fork前创建pipe管道
    pipe(fp[cnt]);
    if(fork()){
        // 对于父进程，关掉读端
        close(fp[cnt][0]);
        for(int i=2;i<=35;i++){
            write(fp[cnt][1],&i,sizeof(int));
        }
        // 数据发送完毕 关闭写端
        close(fp[cnt][1]);
        wait(0);
    }else {
        
        check_primes(++cnt,fp);
    }
    exit(0);
}