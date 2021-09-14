#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
    int ret = fork();

    while(1)
    {
      if(ret > 0)       //说明是父进程
      {
          printf("father : %d, ret : %d\n", getpid(), ret);
      }
      else if(ret == 0)
      {
          printf("child : %d, ret : %d\n", getpid(), ret);
      }
      else 
      {
          printf("fork\n");
      }

      sleep(1);
    }

    return 0;
}
