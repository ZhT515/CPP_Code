#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
    int ret = fork();                                                  
     while(1)
     {
       if(ret > 0)       //说明是父进程
       {
           printf("father : %d, ret : %d\n", getpid(), ret);
           sleep(3);
           exit(0);
       }
       else if(ret == 0) {
           printf("child : %d, ret : %d\n", getpid(), ret);
           sleep(5);
       }
        else 
        {
           printf("fork\n");
           return 1;
        }
     }
  return 0;
  }

