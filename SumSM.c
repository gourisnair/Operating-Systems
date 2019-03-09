#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>
#include<limits.h>
#include<stdlib.h>
int main()
{
  int shmid = shmget(IPC_PRIVATE, 1024, 0666|IPC_CREAT);
  int shmid1 = shmget(IPC_PRIVATE, 2*sizeof(int), 0666|IPC_CREAT);
  int shmid2 = shmget(IPC_PRIVATE, 2*sizeof(int), 0666|IPC_CREAT);
  int *num = (int*)shmat(shmid, 0, 0);
  char s[10];
  int i = 0;
  while(1) {
    scanf("%s", s);
    if(isdigit(s[0])) {
      int n = atoi(s);
      n = n*n;
      *(num+i) = n;
      i++;
    } else {
      num[0] = INT_MIN;
      break;
    }
  }
  pid_t pid1, pid2;
  pid1 = fork();
  if (pid1 == 0) {
    int sum = 0;
    i = 0;
    num = (int*)shmat(shmid, 0 ,0);
    while(num[i] != INT_MIN) {
      sum += num[i];
      i++;
    }
    int *s = (int*)shmat(shmid1, 0, 0);
    *s = sum;
    shmdt(s);
  } else {
    wait(NULL);
    pid2 = fork();

    if(pid2 == 0) {
      int i = 0;
      num = (int*)shmat(shmid, 0 ,0);
      while(num[i] != INT_MIN) {
        i++;
      }
      int *count = (int*)shmat(shmid2, 0, 0);
      *count = i;
      shmdt(i);
    } else {
      wait(NULL);
      int *s = (int*)shmat(shmid1, 0, 0);
      int *count = (int*)shmat(shmid2, 0, 0);
      printf("%d%d", *count, *s);
      float average = (float)*s/ *count;
      printf("Average = %0.2f\n",average);
    }
  }
  exit(0);
}
