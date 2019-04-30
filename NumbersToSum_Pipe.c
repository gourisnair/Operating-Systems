#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
  int fd[2];
  int n[10], sum = 0, size;
  char temp[10];
  if(pipe(fd) == -1) {
    printf("Pipe failed");
  }

  if(fork() == 0) {
    printf("This is child process with ID %d\n", getpid());
    printf("My parent is %d\n", getppid());
    int i = 1;
    printf("Enter the numbers\n");
    while(1) {
      scanf("%s", &temp);
      if(isdigit(temp[0])) {
        n[i] = atoi(temp);
        i++;
      } else {
        n[0] = i;
        break;
      }
    }

    close(fd[0]);
    write(fd[1], n, sizeof(n));
    close(fd[1]);
  } else{
    wait(NULL);
    printf("Parent process with ID %d\n", getpid());
    close(fd[1]);
    read(fd[0], n, sizeof(n));
    for(int i = 1; i < n[0]; i++) {
      sum += n[i];
    }
    printf("Sum = %d\n", sum);
    close(fd[0]);
  }
}
